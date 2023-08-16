CFLAGS = -O3
CPPFLAGS = -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2
GDBFLAGS = -O0 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2

.PHONY: c asm run gen test valgrind all clean diff

%: ~/.hash/%.cpp.md5
	g++ -o $@ $@.cpp ${CFLAGS}

c:
	gcc -o c c.c ${CFLAGS}
	./c < mem.in > mem.ans

asm:
	../sim/assembler source.s -o source.bin

run:
	../sim/simulator source.bin --mem mem.in > mem.out

gen:
	python3 gen.py > mem.in

test:
	bash test.sh

diff:
	diff mem.out mem.ans

all:
	make gen
	make c
	make asm
	make run

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./data < data.in

clean:
	rm c mem.in mem.out mem.ans source.bin