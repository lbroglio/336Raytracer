## How to Build and run the program
1. The program can be built by running the make command in the terminal
2. To run the resulting bin enter ./raytrace336 followed by any arguments
3. The program has 2 required and one optional argument 
    a. The first argument is the path to the .obj file for the raytracer to render
    b. The second argument is the path to the .mtl used to give the materials applied to the faces in the .obj
    c. The third argument is optional and is the path to a .config used to control the raytracer. Example .config files can be found at
    test-models/RecommendedConfigs.

### Examples to run
./bin/raytrace336 test-models/FloatingCube.obj test-models/FloatingCube.mtl test-models/RecommendedConfigs/FloatingCube.config

./bin/raytrace336 test-models/CubeReflection.obj test-models/CubeReflection.mtl test-models/RecommendedConfigs/CubeReflection.config

./bin/raytrace336 test-models/ReflectionNoView.obj test-models/ReflectionNoView.mtl test-models/RecommendedConfigs/ReflectionNoView.config