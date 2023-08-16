THIS_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
CFLAGS = -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2
GDBFLAGS = -O0 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2

.PHONY: all gen test gdb runtime atcoder clean

%: ~/.hash/%.cpp.md5
	g++ -o $@ $@.cpp ${CFLAGS}

hash:
	updatemd5 ${THIS_DIR}*.cpp

all: data brute
	updatemd5 ${THIS_DIR}data.cpp
	updatemd5 ${THIS_DIR}brute.cpp
	make data
	make brute

gen:
	python3 gen.py > data.in

test:
	bash test.sh

gdb:
	g++ -o data data.cpp ${GDBFLAGS}
	expect -c 'spawn gdb data; expect "(gdb)"; send "run < data.in\r"; send "bt\r"; send "exit\r"; send "y\r"; expect eof'

runtime:
	g++ -pg -o data data.cpp -std=c++20
	./data < big.in > big.out
	gprof data gmon.out > analysis.txt

atcoder:
	bash atcoder.sh

clean:
	rm data brute