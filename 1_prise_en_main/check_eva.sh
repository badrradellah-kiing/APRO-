#!/usr/bin/env bash
# Verification de l'installation Frama-C et des domaines EVA

OK="\033[0;32m✓\033[0m"
KO="\033[0;31m✗\033[0m"

echo "Verification environnement Frama-C / EVA"
echo "----------------------------------------"

# Frama-C present ?
if ! command -v frama-c &>/dev/null; then
    echo -e "  $KO frama-c introuvable"
    echo "    Installer avec : sudo apt install frama-c"
    exit 1
fi
echo -e "  $OK frama-c $(frama-c -version)"

# Plugin EVA charge ?
if frama-c -plugins 2>/dev/null | grep -qiE "eva|value"; then
    echo -e "  $OK plugin EVA OK"
else
    echo -e "  $KO EVA non detecte"
    exit 1
fi

# Domaines disponibles ? On teste en lancant une mini-analyse.
PROBE=$(mktemp --suffix=.c)
echo "int main(void){return 0;}" > "$PROBE"
for d in equality symbolic-locations gauges octagon bitwise; do
    out=$(frama-c "$PROBE" -eva -eva-domains "$d" 2>&1 || true)
    if echo "$out" | grep -qiE "invalid|unknown domain|not registered"; then
        echo -e "  $KO domaine $d indisponible"
    else
        echo -e "  $OK domaine $d disponible"
    fi
done
rm -f "$PROBE"

# Mini-analyse de bout en bout
TMP=$(mktemp --suffix=.c)
cat > "$TMP" <<'EOF'
int main(void) {
    int x = 42;
    int *p = &x;
    return *p;
}
EOF
if frama-c "$TMP" -eva 2>&1 | grep -qiE "Values at end"; then
    echo -e "  $OK analyse minimale OK"
else
    echo -e "  $KO analyse minimale en echec"
fi
rm -f "$TMP"

echo "----------------------------------------"
echo "Environnement pret."
