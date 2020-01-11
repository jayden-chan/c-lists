build:
	gcc src/*.c -I inc -o main -O3 -Wall -Wshadow -Wno-unused-result

build-debug:
	gcc src/*.c -I inc -o main -ggdb -DFULLDEBUG -Wshadow -Wall -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

cachegrind:
	-valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out ./main

callgrind:
	-valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./main


clean:
	-rm ./main
	-rm callgrind.out
	-rm cachegrind.out

profile: clean build-debug cachegrind callgrind

run:
	./main

default: build

.PHONY: build build-debug cachegrind callgrind profile clean run
