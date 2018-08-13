#/*
#2018 Maximilian Wittmer
#wittmaxi@linux.pizza
#
#https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE
#
#*/

all: test

build:
	-mkdir ./build
	g++ -c ./library/*.cpp -o ./build/zeneural.o
	ar rcs ./build/zeneural.a ./build/zeneural.o 

install: build
	sudo cp ./build/zeneural.a /usr/local/lib
	sudo mkdir /usr/local/lib/zeneural
	sudo cp -r ./library/header/* /usr/local/lib/zeneural/

uninstall:
	@-sudo rm -r /usr/local/lib/zeneural
	@-sudo rm /usr/local/lib/zeneural.a

clean:
	@-rm -r ./build
	@-rm ./test

test: 
	make -C ./library/tests #make the unit tests

debug:
	g++ ./library/*.cpp -o test -g
	gdb ./test
