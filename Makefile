raytrace336: raytrace336.o vectors.o worldObjects.o modelReaders.o raycast.o imageOut.o configuration/configurator.hpp bin
	g++ -Wall -Werror -ggdb bin/raytrace336.o bin/worldObjects.o bin/modelReaders.o bin/vectors.o bin/raycast.o bin/imageOut.o -o bin/raytrace336

raytrace336.o: raytrace336.cpp bin configuration/configurator.hpp
	g++ -Wall -Werror -ggdb -c raytrace336.cpp -o bin/raytrace336.o

vectors.o: world/vectors.cpp world/vectors.hpp bin
	g++ -Wall -Werror -ggdb -c  world/vectors.cpp -o bin/vectors.o

worldObjects.o: world/worldObjects.cpp world/worldObjects.hpp bin
	g++ -Wall -Werror -ggdb -c  world/worldObjects.cpp -o bin/worldObjects.o

modelReaders.o: file-io/modelReaders.cpp file-io/modelReaders.hpp configuration/configurator.hpp bin
	g++ -Wall -Werror -ggdb -c  file-io/modelReaders.cpp -o bin/modelReaders.o

raycast.o: raycast/raycast.hpp raycast/raycast.cpp configuration/configurator.hpp bin
	g++ -Wall -Werror -ggdb -c  raycast/raycast.cpp -o bin/raycast.o

imageOut.o: file-io/imageOut.cpp file-io/imageOut.hpp bin
	g++ -Wall -Werror -ggdb -c  file-io/imageOut.cpp -o bin/imageOut.o

bin:
	if  ! [[ -d "./bin" ]]; then mkdir bin; fi

clean:
	rm bin/*