PROGS := 01_static_array 02_aliasing_strong 03_full_contract 04_safe_divide \
         05_bounded_list 06_nested_struct 07_pointer_arith 08_max_function \
         09_swap 10_octagon_relation 11_bitwise_mask 12_array_init
INC := -cpp-extra-args="-I../../1_prise_en_main"
OPTS := -eva -eva-precision 2 -eva-domains equality,symbolic-locations,octagon,gauges,bitwise $(INC)

.PHONY: all clean
all:
	@mkdir -p logs
	@for p in $(PROGS); do echo "> $$p"; frama-c $$p.c $(OPTS) > logs/$$p.log 2>&1 || true; done
	@bash bench.sh
clean:
	@rm -rf logs *.session* results.md
