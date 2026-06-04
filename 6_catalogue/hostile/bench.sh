#!/usr/bin/env bash
set -u

PROGS=(01_garbled_mix 02_malloc_loop 03_recursive_sum 04_function_pointer
       05_unbounded_offset 06_use_after_free 07_double_free 08_pointer_chain
       09_int_overflow 10_unbounded_loop 11_symbolic_write 12_dispatch_table)

metrics() {
    [ ! -f "$1" ] && echo "n/a|0|0|0|no" && return
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
                (valid != "" ? valid : "0"),
                (unknown != "" ? unknown : "0"),
                (invalid != "" ? invalid : "0"),
                (garbled ? "oui" : "non")
        }
    ' "$1"
}

OUT="results.md"
{
    echo "# Cas limites — resultats"
    echo
    echo "Attendu : alarmes et/ou Unknown, meme avec la config MAX."
    echo
    echo "| Programme | Alarmes | Valid | Unknown | Invalid | Garbled mix |"
    echo "|-----------|---------|-------|---------|---------|-------------|"
    for p in "${PROGS[@]}"; do
        m=$(metrics "logs/$p.log")
        IFS='|' read -r a v u i g <<< "$m"
        echo "| $p | $a | $v | $u | $i | $g |"
    done
} > "$OUT"

cat "$OUT"
