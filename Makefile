test: test.cpp world-objects/worldObjects.hpp world-objects/worldObjects.cpp
	g++ -Wall -Werror -ggdb test.cpp world-objects/worldObjects.cpp -o bin/test

clean:
	rm bin/*