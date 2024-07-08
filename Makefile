run: a.out
	@echo "Input:"
	@cat in.txt
	@echo "\nExpected:"
	@cat ans.txt
	@echo "\nOutput:"
	./a.out <in.txt

test: a.out
	./a.out <in.txt | tee out.txt && diff out.txt ans.txt

testpy:
	python a.py <in.txt | tee out.txt && diff out.txt ans.txt

a.out: a.cpp
	g++ a.cpp -DDBG

