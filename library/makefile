libmake:
		g++ CLayer.cpp Neural.cpp CNode.cpp main.cpp -o zeneural.o
		ar rvs zeneural.a zeneural.o
		sudo mv ./zeneural.a /usr/local/lib
		rm zeneural.o

test:
	g++ test.cpp CLayer.cpp CNode.cpp Neural.cpp -o test
	./test

clean:
	rm ./test
	sudo rm /usr/local/lib/zeneural.a
