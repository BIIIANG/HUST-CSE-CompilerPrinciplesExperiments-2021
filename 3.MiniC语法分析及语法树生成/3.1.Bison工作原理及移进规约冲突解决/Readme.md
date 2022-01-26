生成普通output文件：bison -v foo.y
更名为output1
生成包含解决信息的output文件：bison -r solved foo.y
更名为output2
查看两个文件不同的信息：diff foo.output1 foo.output2