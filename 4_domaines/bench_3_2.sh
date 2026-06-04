#!/usr/bin/env bash
# Phase 3.2 - matrice programmes x domaines
set -u

PROGS=(eq_01_pointer_equality sl_01_array_symbolic oct_01_relational
       ga_01_loop_relations bw_01_bitops)
DOMAINS=(none equality symbolic-locations octagon gauges bitwise)

extract_metrics() {
    local logfile="$1"
    if [ ! -f "$logfile" ]; then echo "n/a"; return; fi
    awk '
        /^\[eva:alarm\]/ { alarms++ }
        /Assertions[[:space:]]+[0-9]+ valid/ {
            for (k=1; k<=NF; k++) {
                if ($k == "valid")   { valid   = $(k-1) }
                if ($k == "unknown") { unknown = $(k-1) }
            }
        }
        END {
            printf "%d/%s/%s\n",
                (alarms ? alarms : 0),
                (valid   != "" ? valid   : "0"),
                (unknown != "" ? unknown : "0")
        }
    ' "$logfile"
}

OUT="bench_3_2_results.md"
{
    echo "# Phase 3.2 - Comparaison fine des domaines"
    echo
    echo "Format des cellules : \`alarmes/valid/unknown\`"
    echo
    echo "**Methodologie** : chaque programme est analyse avec UN domaine actif a la"
    echo "fois (cvalue est toujours present comme baseline). On identifie ainsi"
    echo "quel domaine debloque quelle propriete."
    echo
    echo "| Programme | none | equality | sym-loc | octagon | gauges | bitwise |"
    echo "|-----------|------|----------|---------|---------|--------|---------|"
    for prog in "${PROGS[@]}"; do
        row="| $prog"
        for d in "${DOMAINS[@]}"; do
            m=$(extract_metrics "logs/$d/$prog.log")
            row+=" | $m"
        done
        echo "$row |"
    done
    echo
    echo "## Lecture"
    echo
    echo "- Le programme \`eq_01\` doit voir ses unknown reduits avec **equality**."
    echo "- Le programme \`sl_01\` doit voir ses unknown reduits avec **symbolic-locations**."
    echo "- Le programme \`oct_01\` doit voir ses unknown reduits avec **octagon**."
    echo "- Le programme \`ga_01\` doit voir ses unknown reduits avec **gauges**."
    echo "- Le programme \`bw_01\` doit voir ses unknown reduits avec **bitwise**."
    echo
    echo "Si un domaine debloque un programme qui ne lui est PAS destine,"
    echo "c'est un finding interessant (effet de bord positif)."
} > "$OUT"

cat "$OUT"
echo "→ $OUT"
