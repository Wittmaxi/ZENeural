all: libmake test

libmake:
				g++ CLayer.cpp -c -o CLayer.o
				g++ CNode.cpp -c -o CNode.o
				g++ Neural.cpp -c -o CNeural.o
				ar rcs libzeneural.a CLayer.o CNode.o CNeural.o

install: libmake
				sudo mv ./libzeneural.a /usr/local/lib
				sudo mkdir -p /usr/local/include/zeneural/
				sudo cp zeneural/*.h /usr/local/include/zeneural/

uninstall:
				sudo rm /usr/local/lib/libzeneural.a
				sudo rm -rf /usr/local/include/zeneural/

test:
				g++ *.cpp -Wall -o test
				./test

clean:
				rm ./test
				rm *.o
