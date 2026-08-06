X86_PROGS := gen_8bit_luts

all: $(X86_PROGS)

gen_8bit_luts: gen_8bit_luts.c
	$(CC) $< -o $@ -lm

clean:
	rm -f $(X86_PROGS)
