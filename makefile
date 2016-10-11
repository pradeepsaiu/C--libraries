all:	MAP.hpp 
	g++ test1.cpp -Wall -Wextra -pedantic -ldl -std=c++11 -o out
	./out
gdb:	
	g++ -g test1.cpp -Wall -Wextra -pedantic -ldl -std=c++11 -o out
	gdb ./out

