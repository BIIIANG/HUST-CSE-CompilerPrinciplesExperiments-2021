#!/bin/sh

inputFile=$1
extension=${inputFile##*.}

if [ $extension = "l" ];then   # ./c.sh test.l
    name=${inputFile%.*}
    command `flex -o "${name}.yy.c" "${name}.l"`
    command `gcc -o  "${name}" "${name}.yy.c" -lfl`
else    # ./c.sh test
    command `flex -o "${1}.yy.c" "${1}.l"`
    command `gcc -o  "${1}" "${1}.yy.c" -lfl`
fi

echo "Done"