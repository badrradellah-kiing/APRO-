#!/usr/bin/env bash
# Relance tous les benchmarks et regroupe les resultats dans RESULTS.md.
set -u
ROOT=$(cd "$(dirname "$0")" && pwd)
RESULTS="$ROOT/RESULTS.md"

run() { echo; echo "==> $1"; cd "$ROOT/$2"; chmod +x ./*.sh 2>/dev/null; make clean >/dev/null 2>&1; eval "$3" >/dev/null 2>&1; echo "  ok"; }

echo "==> Verification de l'environnement"
cd "$ROOT/1_prise_en_main"; chmod +x check_eva.sh; ./check_eva.sh

run "1 - programmes de stress"   "1_prise_en_main"        "make bench"
run "2 - cas d'etude"            "2_cas_etude"            "make bench"
run "3 - garbled mix"            "3_garbled_mix"          "make bench"
run "4 - domaines"               "4_domaines"            "make bench"
run "5 - contrats ACSL"          "5_contrats_acsl"        "make bench"
run "6 - catalogue (friendly)"   "6_catalogue/friendly"   "make all"
run "6 - catalogue (hostile)"    "6_catalogue/hostile"    "make all"

cd "$ROOT"
{
  echo "# Resultats globaux"
  echo; echo "Format : alarmes / valid / unknown / invalid."
  for f in \
    "1_prise_en_main/bench_results.md:1 - Programmes de stress" \
    "2_cas_etude/bench_results_phase2.md:2 - Cas d'etude" \
    "3_garbled_mix/bench_3_1_results.md:3 - Garbled mix" \
    "4_domaines/bench_3_2_results.md:4 - Domaines" \
    "5_contrats_acsl/bench_3_4_results.md:5 - Contrats ACSL" \
    "6_catalogue/friendly/results.md:6 - Catalogue (friendly)" \
    "6_catalogue/hostile/results.md:6 - Catalogue (hostile)"; do
      path="${f%%:*}"; title="${f##*:}"
      echo; echo "## $title"; echo
      [ -f "$path" ] && tail -n +3 "$path"
  done
} > "$RESULTS"
echo; echo "=> RESULTS.md ecrit."
