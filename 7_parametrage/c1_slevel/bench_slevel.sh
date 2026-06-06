#!/usr/bin/env bash
# Balaye -eva-slevel : precision (a/v/u) ET temps. timeout = cout intractable.
set -u
INC="-cpp-extra-args=-I../../1_prise_en_main"
PROGS="paths cost_branches"
SLEVELS="0 1 100 1000 5000 20000"
TIMEOUT=25
OUT="bench_slevel_results.md"

avu() {
  local f=$1 a v u
  a=$(grep -oE '[0-9]+ alarms? generated' "$f" | grep -oE '^[0-9]+'); a=${a:-0}
  v=$(grep -oE 'Assertions[ ]+[0-9]+ valid' "$f" | grep -oE '[0-9]+ valid' | grep -oE '^[0-9]+'); v=${v:-0}
  u=$(grep -oE '[0-9]+ unknown' "$f" | grep -oE '^[0-9]+' | head -1); u=${u:-0}
  echo "$a/$v/$u"
}

mkdir -p logs
{
  echo "# C.1 - Impact du slevel"
  echo
  echo "Precision (alarmes/valid/unknown) et temps (s). 'timeout' = intractable a ce budget."
  for p in $PROGS; do
    echo; echo "## $p"; echo
    echo "| slevel | a/v/u | temps (s) |"
    echo "|--------|-------|-----------|"
    for sl in $SLEVELS; do
      s=$(date +%s%N)
      timeout $TIMEOUT frama-c $p.c -eva -eva-slevel $sl $INC > logs/${p}_$sl.log 2>&1
      rc=$?; e=$(date +%s%N)
      if [ $rc -eq 124 ]; then echo "| $sl | -- | timeout |"
      else t=$(awk "BEGIN{printf \"%.2f\",($e-$s)/1e9}"); echo "| $sl | $(avu logs/${p}_$sl.log) | $t |"; fi
    done
  done
} > "$OUT"
echo "-> $OUT"
