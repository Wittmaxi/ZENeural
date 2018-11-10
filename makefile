#/*
#2018 Maximilian Wittmer
#wittmaxi@linux.pizza
#
#https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE
#
#*/
all: test


compile_header:
	-mkdir ./build
	echo "" > ./build/zeneural.hpp
	cat ./library/header/includes.h > ./build/zeneural.hpp
	echo "" >> ./build/zeneural.hpp
	echo "#ifndef zeneural_included_" >> ./build/zeneural.hpp
	echo "#define zeneural_inlcuded_" >> ./build/zeneural.hpp
	cat ./library/header/util/assert.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/normalization.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/Layer.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/NeuralNetwork.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./librar/header/VanillaRecurrentNetwork.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/Perceptron.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/typedefs.hpp | grep -v "^#" >> ./build/zeneural.hpp
	echo "#endif" >> ./build/zeneural.hpp

install: compile_header
	sudo cp ./build/zeneural.hpp /usr/include/zeneural.hpp

test: 
	make -C ./library/tests #make the unit tests

full_test:
	make valgrind -C ./library/tests

debug:
	g++ ./library/*.cpp -o test -g
	gdb ./test
