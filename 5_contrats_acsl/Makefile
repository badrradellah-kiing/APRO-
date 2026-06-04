PROGS := acsl_00_no_contract acsl_01_requires acsl_02_requires_ensures \
         acsl_03_loop_invariant acsl_04_assigns
INC := -cpp-extra-args="-I../1_prise_en_main"
STD_OPTS := -eva -eva-precision 2 -eva-domains equality,symbolic-locations $(INC)

.PHONY: bench clean
bench:
	@mkdir -p logs
	@for p in $(PROGS); do echo "[*] $$p"; frama-c $$p.c $(STD_OPTS) > logs/$$p.log 2>&1 || true; done
	@bash bench_3_4.sh
clean:
	@rm -rf logs *.session* bench_3_4_results.md
