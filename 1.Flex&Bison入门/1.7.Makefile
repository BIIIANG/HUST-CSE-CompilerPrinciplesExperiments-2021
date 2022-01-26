calc:1.7.FlexInfixNotationCalc.l 1.7.Bison-InfixNotationCalc.y
	bison -d 1.7.Bison-InfixNotationCalc.y
	flex -o 1.7.FlexInfixNotationCalc.yy.c 1.7.FlexInfixNotationCalc.l
	gcc -o 1.7.InfixNotationCalc 1.7.FlexInfixNotationCalc.yy.c 1.7.Bison-InfixNotationCalc.tab.c -lfl -lm