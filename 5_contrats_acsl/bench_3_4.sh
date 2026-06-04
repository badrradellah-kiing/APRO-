#!/usr/bin/env bash
# Phase 3.4 - apport progressif des contrats ACSL
set -u

PROGS=(acsl_00_no_contract acsl_01_requires acsl_02_requires_ensures
       acsl_03_loop_invariant acsl_04_assigns)

extract_metrics() {
    local logfile="$1"
    if [ ! -f "$logfile" ]; then echo "n/a/n/a/n/a/n/a"; return; fi
    awk '
        /^\[eva:alarm\]/ { alarms++ }
        /Assertions[[:space:]]+[0-9]+ valid/ {
            for (k=1; k<=NF; k++) {
                if ($k == "valid")   { valid   = $(k-1) }
                if ($k == "unknown") { unknown = $(k-1) }
                if ($k == "invalid") { invalid = $(k-1) }
            }
        }
        END {
            printf "%d/%s/%s/%s\n",
                (alarms ? alarms : 0),
                (valid   != "" ? valid   : "0"),
                (unknown != "" ? unknown : "0"),
                (invalid != "" ? invalid : "0")
        }
    ' "$logfile"
}

OUT="bench_3_4_results.md"
{
    echo "# Phase 3.4 - Apport progressif des contrats ACSL"
    echo
    echo "Format : \`alarmes / valid / unknown / invalid\`"
    echo
    echo "| Programme | Resultat | Type de contrat ajoute |"
    echo "|-----------|----------|------------------------|"
    LABELS=(
        "BASELINE : aucun contrat"
        "+ requires (preconditions)"
        "+ ensures (postcondition)"
        "+ loop invariant"
        "+ assigns (frame)"
    )
    i=0
    for prog in "${PROGS[@]}"; do
        m=$(extract_metrics "logs/$prog.log")
        echo "| $prog | $m | ${LABELS[$i]} |"
        i=$((i+1))
    done
    echo
    echo "## Lecture"
    echo
    echo "On s'attend a voir une **chute progressive** des Unknown a mesure"
    echo "qu'on ajoute des contrats. Chaque etape doit etre justifiable :"
    echo
    echo "- \`requires\` : restreint le domaine d'entree"
    echo "- \`ensures\` : permet a l'appelant de tirer des conclusions sans"
    echo "  re-analyser la fonction"
    echo "- \`loop invariant\` : empeche le widening de detruire l'information"
    echo "- \`assigns\` : limite les effets de bord, preserve les variables non touchees"
} > "$OUT"

cat "$OUT"
echo "→ $OUT"
