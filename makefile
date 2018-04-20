make:
	-mkdir ./build
	g++ -c ./library/Perceptron.cpp -o ./build/perceptron.o
	ar rcs ./build/zeneural.a ./build/perceptron.o 

install: make
	sudo cp ./build/zeneural.a /usr/local/lib
	sudo cp -r ./library/header /usr/local/lib

uninstall:
	-sudo rm -r /usr/local/lib/header
	-sudo rm /usr/local/lib/zeneural.a

clean:
	-rm -r ./build
	-rm ./test

test:
	g++ ./library/*.cpp -o test
	./test
