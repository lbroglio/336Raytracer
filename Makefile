test: test.cpp world/worldObjects.hpp world/worldObjects.cpp
	g++ -Wall -Werror -ggdb test.cpp world/worldObjects.cpp -o bin/test

clean:
	rm bin/*