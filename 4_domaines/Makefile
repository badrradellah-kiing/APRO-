PROGS := eq_01_pointer_equality sl_01_array_symbolic oct_01_relational \
         ga_01_loop_relations bw_01_bitops
INC := -cpp-extra-args="-I../1_prise_en_main"
BASE_OPTS := -eva -eva-precision 2 $(INC)
DOMAINS := none equality symbolic-locations octagon gauges bitwise

.PHONY: bench clean
bench:
	@mkdir -p logs
	@for d in $(DOMAINS); do mkdir -p logs/$$d; \
	  for p in $(PROGS); do \
	    if [ "$$d" = "none" ]; then extra=""; else extra="-eva-domains $$d"; fi; \
	    echo "[$$d] $$p"; frama-c $$p.c $(BASE_OPTS) $$extra > logs/$$d/$$p.log 2>&1 || true; \
	  done; done
	@bash bench_3_2.sh
clean:
	@rm -rf logs *.session* bench_3_2_results.md
