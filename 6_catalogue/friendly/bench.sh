#!/usr/bin/env bash
set -u

PROGS=(01_static_array 02_aliasing_strong 03_full_contract 04_safe_divide
       05_bounded_list 06_nested_struct 07_pointer_arith 08_max_function
       09_swap 10_octagon_relation 11_bitwise_mask 12_array_init)

metrics() {
    [ ! -f "$1" ] && echo "n/a|0|0|0" && return
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
            printf "%d|%s|%s|%s\n",
                (alarms ? alarms : 0),
                (valid != "" ? valid : "0"),
                (unknown != "" ? unknown : "0"),
                (invalid != "" ? invalid : "0")
        }
    ' "$1"
}

OUT="results.md"
{
    echo "# Cas qui marchent — resultats"
    echo
    echo "Attendu : 0 alarme, toutes les assertions Valid."
    echo
    echo "| Programme | Alarmes | Valid | Unknown | Invalid |"
    echo "|-----------|---------|-------|---------|---------|"
    for p in "${PROGS[@]}"; do
        m=$(metrics "logs/$p.log")
        IFS='|' read -r a v u i <<< "$m"
        echo "| $p | $a | $v | $u | $i |"
    done
} > "$OUT"

cat "$OUT"
