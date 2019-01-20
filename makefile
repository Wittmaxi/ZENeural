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
	echo "#ifndef zeneural_included_" > ./build/zeneural.hpp
	echo "#define zeneural_inlcuded_" >> ./build/zeneural.hpp
	cat ./library/header/includes.hpp >> ./build/zeneural.hpp
	cat ./library/header/internals/util/assert.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/internals/util/ThreadScheduler.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/internals/util/numbers.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/internals/util/normalization.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/internals/Neuron.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/internals/Layer.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/NeuralNetwork.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/VanillaRecurrentNetwork.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/Perceptron.hpp | grep -v "^#" >> ./build/zeneural.hpp
	cat ./library/header/internals/typedefs.hpp | grep -v "^#" >> ./build/zeneural.hpp
	echo "#endif" >> ./build/zeneural.hpp

install: compile_header
	sudo cp ./build/zeneural.hpp /usr/include/zeneural.hpp

test: 
	make -C ./library/tests  #make the unit tests

full_test:
	make valgrind -C ./library/tests
	make test_cov -C ./library/tests
	make test -C ./library/tests

debug:
	g++ ./library/*.cpp -o test -g
	gdb ./test
