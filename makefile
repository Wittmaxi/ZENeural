
gatesmake: 
	g++ ./library/*.cpp -o test 
	./test

clean: 
	rm test
