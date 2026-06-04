#!/usr/bin/env bash
set -u

NAMES=(allocator_naive allocator_safe allocator_aliased
       parser_naive parser_safe parser_aliased
       linked_list_naive linked_list_safe linked_list_ambiguous)
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

OUT="bench_results_phase2.md"
{
    echo "# Phase 2 — cas d'etude"
    echo
    echo "Format : \`alarmes / valid / unknown / invalid\`"
    echo
    for group in "allocator" "parser" "linked_list"; do
        echo "## $group"
        echo
        echo "| Version | TP | STD | MAX |"
        echo "|---------|----|----|----|"
        for n in "${NAMES[@]}"; do
            case "$n" in
                ${group}*)
                    row="| $n"
                    for c in "${CONFIGS[@]}"; do
                        m=$(metrics "logs/$c/$n.log")
                        IFS='|' read -r a v u i <<< "$m"
                        row+=" | ${a}/${v}/${u}/${i}"
                    done
                    echo "$row |"
                    ;;
            esac
        done
        echo
    done
} > "$OUT"

cat "$OUT"
