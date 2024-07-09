test: a.out
	@echo "Input:"
	@cat in.txt
	@echo "\nExpected:"
	@cat ans.txt
	@echo "\nOutput:"
	@stdbuf -oL ./a.out <in.txt | tee out.txt
	@echo
	diff out.txt ans.txt

testpy:
	python a.py <in.txt | tee out.txt && diff out.txt ans.txt

gdb: a.out
	# gdb -ex 'set args -path /home/user/work < input.txt' myprogram
	gdb -ex 'set args <in.txt' a.out

a.out: a.cpp
	g++ a.cpp -DDBG -g

