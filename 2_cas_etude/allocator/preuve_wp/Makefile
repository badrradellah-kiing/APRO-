# Complement WP : prouver l'alignement que EVA ne fait que constater.
# Necessite le greffon WP et un prouveur (Alt-Ergo via why3).

.PHONY: align allocator clean

align:
	frama-c align_wp.c -wp -wp-rte -wp-prover alt-ergo

allocator:
	frama-c allocator_wp.c -wp -wp-rte -wp-prover alt-ergo

clean:
	rm -rf .frama-c *.session
