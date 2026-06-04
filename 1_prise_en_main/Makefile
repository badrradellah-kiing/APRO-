PROGS := 02_nondeterministic 03_array_symbolic 04_linked_list \
         05_dynamic_alloc 06_pointer_cast 07_may_alias
TP_OPTS  := -eva -eva-precision 0
STD_OPTS := -eva -eva-precision 2 -eva-domains equality,symbolic-locations
MAX_OPTS := -eva -eva-precision 5 -eva-domains equality,symbolic-locations,octagon,gauges

.PHONY: check tp std max bench clean
check:
	@bash check_eva.sh
tp:
	@mkdir -p logs/tp
	@for p in $(PROGS); do echo "[tp] $$p"; frama-c $$p.c $(TP_OPTS) > logs/tp/$$p.log 2>&1 || true; done
std:
	@mkdir -p logs/std
	@for p in $(PROGS); do echo "[std] $$p"; frama-c $$p.c $(STD_OPTS) > logs/std/$$p.log 2>&1 || true; done
max:
	@mkdir -p logs/max
	@for p in $(PROGS); do echo "[max] $$p"; frama-c $$p.c $(MAX_OPTS) > logs/max/$$p.log 2>&1 || true; done
bench: tp std max
	@bash bench.sh
clean:
	@rm -rf logs *.session* bench_results.md *.log
