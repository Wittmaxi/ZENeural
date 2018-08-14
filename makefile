#/*
#2018 Maximilian Wittmer
#wittmaxi@linux.pizza
#
#https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE
#
#*/

all: test

test: 
	make -C ./library/tests #make the unit tests

debug:
	g++ ./library/*.cpp -o test -g
	gdb ./test
