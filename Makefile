.PHONY: test clean template testpy

test: a.out
	@echo "Input:\n======"
	@cat in.txt
	@echo "\nStderr:\n======="
	@{ ./a.out <in.txt >out.txt; } 2>&1 | \
		awk '/AddressSanitizer/{p=1}!p||/a.cpp/||!/^\s/'
	@echo "\nExpected:\n========="
	@cat ans.txt
	@echo "\nOutput:\n======="
	@cat out.txt
	@echo "\n======="
	@diff out.txt ans.txt >/dev/null
	@echo "ok!"

template:
	bash ./template.sh
	make test

gdb: a.out
	gdb -nx -ex 'set args <in.txt' a.out

# micromamba install clangxx compiler-rt
a.out: a.cpp debug.h
	g++ a.cpp -DDBG -g -Wall -Werror -Wextra -std=c++20 \
		-fsanitize=address \
		-Wno-unused-but-set-variable -Wno-unused-variable \
		-Wno-unused-local-typedefs \
		-o a.out

clean:
	rm a.out
