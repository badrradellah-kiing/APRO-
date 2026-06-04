#!/usr/bin/env bash
# Phase 3.1 - bench avec detection explicite du garbled mix
set -u

PROGS=(01_cast_trivial 02_cast_plus_const 03_cast_plus_nondet
       04_cast_xor 05_cast_mask 06_two_pointers
       07_pointer_arith_nondet 08_union_pointer)
CONFIGS=(tp std max)

extract_metrics() {
    local logfile="$1"
    if [ ! -f "$logfile" ]; then echo "n/a|n/a|n/a|n/a|n/a"; return; fi
    awk '
        /^\[eva:alarm\]/ { alarms++ }
        /garbled mix/    { garbled = 1 }
        /Assertions[[:space:]]+[0-9]+ valid/ {
            for (k=1; k<=NF; k++) {
                if ($k == "valid")   { valid   = $(k-1) }
                if ($k == "unknown") { unknown = $(k-1) }
                if ($k == "invalid") { invalid = $(k-1) }
            }
        }
        END {
            printf "%d|%s|%s|%s|%s\n",
                (alarms ? alarms : 0),
                (valid   != "" ? valid   : "0"),
                (unknown != "" ? unknown : "0"),
                (invalid != "" ? invalid : "0"),
                (garbled ? "YES" : "no")
        }
    ' "$logfile"
}

OUT="bench_3_1_results.md"
{
    echo "# Phase 3.1 - Caracterisation du garbled mix"
    echo
    echo "Format : \`alarmes / valid / unknown / invalid / garbled-mix?\`"
    echo
    echo "| Programme | TP | STD | MAX |"
    echo "|-----------|----|----|----|"
    for prog in "${PROGS[@]}"; do
        row="| $prog"
        for cfg in "${CONFIGS[@]}"; do
            m=$(extract_metrics "logs/$cfg/$prog.log")
            IFS='|' read -r a v u i g <<< "$m"
            row+=" | ${a}/${v}/${u}/${i}/${g}"
        done
        echo "$row |"
    done
    echo
    echo "## Hypotheses scientifiques"
    echo
    echo "| # | Pattern | Attendu |"
    echo "|---|---------|---------|"
    echo "| 01 | cast trivial roundtrip | base preservee, 0 alarme |"
    echo "| 02 | cast +k -k | depend de la finesse |"
    echo "| 03 | cast + nondet | garbled mix garanti |"
    echo "| 04 | xor k xor k | garbled mix probable |"
    echo "| 05 | masque AND | garbled mix probable |"
    echo "| 06 | difference de pointeurs | garbled mix immediat |"
    echo "| 07 | arith pointeur sans cast | OOB sans garbled mix |"
    echo "| 08 | union | base preservee |"
} > "$OUT"

cat "$OUT"
echo "→ $OUT"
