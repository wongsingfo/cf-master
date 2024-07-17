test: a.out
	@echo "Input:"
	@cat in.txt
	@echo "\nStderr:"
	@./a.out <in.txt >out.txt
	@echo "\nExpected:"
	@cat ans.txt
	@echo "\nOutput:"
	@cat out.txt
	@echo
	diff out.txt ans.txt >/dev/null

testpy:
	@echo "Input:"
	@cat in.txt
	@echo "\nExpected:"
	@cat ans.txt
	@echo "\nOutput:"
	@python a.py <in.txt | tee out.txt
	@echo
	diff out.txt ans.txt >/dev/null

gdb: a.out
	# gdb -ex 'set args -path /home/user/work < input.txt' myprogram
	gdb -ex 'set args <in.txt' a.out

a.out: a.cpp
	g++ a.cpp -DDBG -g -Wall -Werror -Wextra -std=c++17 \
		-fsanitize=address \
		-Wno-unused-but-set-variable -Wno-unused-variable \
		-Wno-unused-local-typedefs \
		-o a.out

