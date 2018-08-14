#/*
#2018 Maximilian Wittmer
#wittmaxi@linux.pizza
#
#https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE
#
#*/
all: compile_header


compile_header:
	-mkdir ./build
	echo "" > ./build/zeneural.hpp
	cat ./library/header/includes.h > ./build/zeneural.hpp
	echo "" >> ./build/zeneural.hpp
	cat ./library/header/util/assert.h | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/normalization.h | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/Layer.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/NeuralNetwork.hpp | grep -v "^#" >> ./build/zeneural.hpp

install: compile_header
	sudo cp ./build/zeneural.hpp /usr/include/zeneural.hpp

test: 
	make -C ./library/tests #make the unit tests

debug:
	g++ ./library/*.cpp -o test -g
	gdb ./test
