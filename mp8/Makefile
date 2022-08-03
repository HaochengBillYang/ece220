student: shape.hpp main.cpp
	g++ main.cpp shape.hpp -o mp8 -Wall -Werror

verify:  shape.hpp check.hpp gshape.hpp main.cpp
	g++ -g -c check.cpp -o check.o
	g++ -g -c verify.cpp -o verify.o
	g++ -g verify.o shape.hpp gshape.o check.o -o verify_mp8

clean:
	@rm mp8 || echo "no mp8 to remove >:("
	@rm  check.o verify.o verify_mp8 || echo "no verify_mp8 to remove >:("
