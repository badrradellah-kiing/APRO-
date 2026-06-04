#!/usr/bin/env bash
set -u

PROGS=(02_nondeterministic 03_array_symbolic 04_linked_list
       05_dynamic_alloc 06_pointer_cast 07_may_alias)
CONFIGS=(tp std max)

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

OUT="bench_results.md"
{
    echo "# Phase 1.3 — programmes de stress"
    echo
    echo "Format : \`alarmes / valid / unknown / invalid\`"
    echo
    echo "| Programme | TP | STD | MAX |"
    echo "|-----------|----|----|----|"
    for p in "${PROGS[@]}"; do
        row="| $p"
        for c in "${CONFIGS[@]}"; do
            m=$(metrics "logs/$c/$p.log")
            IFS='|' read -r a v u i <<< "$m"
            row+=" | ${a}/${v}/${u}/${i}"
        done
        echo "$row |"
    done
} > "$OUT"

cat "$OUT"
