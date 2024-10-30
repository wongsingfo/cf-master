set -e
make a.out
g++ std.cpp -o std -O2
while : ; do
echo -n .
python gen.py >in.txt
./a.out <in.txt >out.txt
./std <in.txt >ans.txt
diff out.txt ans.txt
done
