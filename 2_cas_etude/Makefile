CASES := allocator/allocator_naive allocator/allocator_safe allocator/allocator_aliased \
         parser/parser_naive parser/parser_safe parser/parser_aliased \
         liste/linked_list_naive liste/linked_list_safe liste/linked_list_ambiguous
INC := -cpp-extra-args="-I../1_prise_en_main"
TP_OPTS  := -eva -eva-precision 0 $(INC)
STD_OPTS := -eva -eva-precision 2 -eva-domains equality,symbolic-locations $(INC)
MAX_OPTS := -eva -eva-precision 5 -eva-domains equality,symbolic-locations,octagon,gauges $(INC)

.PHONY: all tp std max bench clean
bench: tp std max
	@bash bench.sh
tp:
	@mkdir -p logs/tp
	@for c in $(CASES); do n=$$(basename $$c); echo "[tp] $$n"; frama-c $$c.c $(TP_OPTS) > logs/tp/$$n.log 2>&1 || true; done
std:
	@mkdir -p logs/std
	@for c in $(CASES); do n=$$(basename $$c); echo "[std] $$n"; frama-c $$c.c $(STD_OPTS) > logs/std/$$n.log 2>&1 || true; done
max:
	@mkdir -p logs/max
	@for c in $(CASES); do n=$$(basename $$c); echo "[max] $$n"; frama-c $$c.c $(MAX_OPTS) > logs/max/$$n.log 2>&1 || true; done
clean:
	@rm -rf logs *.session* bench_results*.md
