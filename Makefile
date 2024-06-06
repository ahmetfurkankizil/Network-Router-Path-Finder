# Author : Ahmet Furkan KIZIL
# ID: 22203112
# Section : 3
# Homework : 4
# Description : Graphs

pathFinder : Router.cpp Router.h
	g++ Router.cpp Router.h -o pathFinder

run : pathFinder
	./pathFinder input1.txt 0 6 > output1.txt
	./pathFinder input2.txt 7 31 > output2.txt
	./pathFinder input3.txt 514 716 > output3.txt
	./pathFinder input4.txt 14 77 > output4.txt
	./pathFinder input5.txt 14 77 > output5.txt

delete :
	rm -f pathFinder output*.txt