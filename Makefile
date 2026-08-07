X86_PROGS := gen_8bit_luts
X86_DEMO  := demo

SRC := vec8.c main.c
OBJ := $(SRC:%.c=%.o)

all: $(X86_PROGS) $(X86_DEMO)

gen_8bit_luts: gen_8bit_luts.c
	$(CC) $< -o $@ -lm

demo: vec8.o main.o
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

indent:
	indent -kr -l100 -nut $(SRC)

clean:
	rm -f $(X86_PROGS)

.phony: indent clean
