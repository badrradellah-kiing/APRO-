PROGS := 01_garbled_mix 02_malloc_loop 03_recursive_sum 04_function_pointer \
         05_unbounded_offset 06_use_after_free 07_double_free 08_pointer_chain \
         09_int_overflow 10_unbounded_loop 11_symbolic_write 12_dispatch_table
INC := -cpp-extra-args="-I../../1_prise_en_main"
OPTS := -eva -eva-precision 5 -eva-domains equality,symbolic-locations,octagon,gauges,bitwise $(INC)

.PHONY: all clean
all:
	@mkdir -p logs
	@for p in $(PROGS); do echo "> $$p"; frama-c $$p.c $(OPTS) > logs/$$p.log 2>&1 || true; done
	@bash bench.sh
clean:
	@rm -rf logs *.session* results.md
