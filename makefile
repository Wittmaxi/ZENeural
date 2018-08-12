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
	g++ -O0 ./library/*.cpp -o test -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
	#./test

debug:
	g++ ./library/*.cpp -o test -g
	gdb ./test
