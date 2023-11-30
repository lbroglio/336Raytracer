raytrace336: raytrace336.o vectors.o worldObjects.o modelReaders.o 
	g++ -Wall -Werror -ggdb bin/raytrace336.o bin/worldObjects.o bin/modelReaders.o bin/vectors.o -o bin/raytrace336

raytrace336.o: raytrace336.cpp bin
	g++ -Wall -Werror -ggdb -c raytrace336.cpp -o bin/raytrace336.o

vectors.o: world/vectors.cpp world/vectors.hpp bin
	g++ -Wall -Werror -ggdb -c  world/vectors.cpp -o bin/vectors.o

worldObjects.o: world/worldObjects.cpp world/worldObjects.hpp bin
	g++ -Wall -Werror -ggdb -c  world/worldObjects.cpp -o bin/worldObjects.o

modelReaders.o: file-io/modelReaders.cpp file-io/modelReaders.hpp bin
	g++ -Wall -Werror -ggdb -c  file-io/modelReaders.cpp -o bin/modelReaders.o

bin:
	if  ! [[ -d "./bin" ]]; then mkdir bin; fi

clean:
	rm bin/*