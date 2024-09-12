.PHONY: test clean template testpy

test: a.out
	@echo -e "Input:\n======"
	@cat in.txt
	@echo -e "\nStderr:\n======="
	@{ ./a.out <in.txt >out.txt; } 2>&1 | \
		awk '/AddressSanitizer/{p=1}!p||/a.cpp/||!/^\s/'
	@echo -e "\nExpected:\n========="
	@cat ans.txt
	@echo -e "\nOutput:\n======="
	@cat out.txt
	@echo -e "\n======="
	@diff --ignore-trailing-space out.txt ans.txt >/dev/null
	@echo "ok!"

template:
	bash ./template.sh
	make test

gdb: a.out
	gdb -nx -ex 'set args <in.txt' \
		-ex 'set environment ASAN_OPTIONS=detect_leaks=0' \
		a.out

# micromamba install clangxx compiler-rt
a.out: a.cpp debug.h
	g++ a.cpp -DDBG -g -Wall -Werror -Wextra -std=c++20 \
		-fsanitize=address \
		-Wno-unused-but-set-variable -Wno-unused-variable \
		-Wno-unused-local-typedefs \
		-o a.out

clean:
	rm a.out
