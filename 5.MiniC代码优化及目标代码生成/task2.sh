opt -mem2reg test.txt -S > test.ll
llc test.ll -o test.s
clang test.s -o test