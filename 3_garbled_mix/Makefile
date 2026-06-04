PROGS := 01_cast_trivial 02_cast_plus_const 03_cast_plus_nondet \
         04_cast_xor 05_cast_mask 06_two_pointers \
         07_pointer_arith_nondet 08_union_pointer
INC := -cpp-extra-args="-I../1_prise_en_main"
TP_OPTS  := -eva -eva-precision 0 $(INC)
STD_OPTS := -eva -eva-precision 2 -eva-domains equality,symbolic-locations $(INC)
MAX_OPTS := -eva -eva-precision 5 -eva-domains equality,symbolic-locations,octagon,gauges,bitwise $(INC)

.PHONY: all tp std max bench clean
all: tp std max
tp:
	@mkdir -p logs/tp
	@for p in $(PROGS); do echo "[tp] $$p"; frama-c $$p.c $(TP_OPTS) > logs/tp/$$p.log 2>&1 || true; done
std:
	@mkdir -p logs/std
	@for p in $(PROGS); do echo "[std] $$p"; frama-c $$p.c $(STD_OPTS) > logs/std/$$p.log 2>&1 || true; done
max:
	@mkdir -p logs/max
	@for p in $(PROGS); do echo "[max] $$p"; frama-c $$p.c $(MAX_OPTS) > logs/max/$$p.log 2>&1 || true; done
bench: all
	@bash bench_3_1.sh
clean:
	@rm -rf logs *.session* bench_3_1_results.md
