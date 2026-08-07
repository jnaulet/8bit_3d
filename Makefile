X86_PROGS := gen_8bit_luts

SRC := vec8.c
OBJ := $(SRC:%.c=%.o)

all: $(X86_PROGS)

gen_8bit_luts: gen_8bit_luts.c
	$(CC) $< -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

indent:
	indent -kr -l100 -nut $(SRC)

clean:
	rm -f $(X86_PROGS)

.phony: indent clean
