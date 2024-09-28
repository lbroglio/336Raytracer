CC= g++ --std=c++17
APPNAME= raytrace336
SOURCES= file-io/imageOut.cpp \
		 file-io/modelReaders.cpp \
		 raycast/raycast.cpp\
		 world/vectors.cpp \
		 world/worldObjects.cpp \
		 raytrace336.cpp
GPU_DEBUG_SOURCES = file-io/modelReaders.cpp \
					world/vectors.cpp  \
					gpu-render/gpuRender.cpp \
					world/worldObjects.cpp 
GLAD_SRC = include/glad/glad.c	
BINDIR= bin
OBJECTS = $(SOURCES:%.cpp=$(BINDIR)/%.o)
GPU_DEBUG_OBJECTS = $(GPU_DEBUG_SOURCES:%.cpp=$(BINDIR)/%.o)
TARGET= $(BINDIR)/$(APPNAME)
GPU_DEBUG_TARGET=$(BINDIR)/GPU-DEBUG-$(APPNAME)
CCFLAGS= -Wall -Werror

.PHONY: clean all

all: $(TARGET)

gpuDebug: $(GPU_DEBUG_TARGET)

$(TARGET): bin $(OBJECTS) 
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(TARGET)

$(GPU_DEBUG_TARGET): bin $(GPU_DEBUG_OBJECTS) $(GLAD_SRC)
	$(CC) $(CCFLAGS) $(GPU_DEBUG_OBJECTS) bin/glad/glad.o -o $(GPU_DEBUG_TARGET) -lglfw -lGL

bin/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

$(GLAD_SRC): bin
	$(CC) $(CCFLAGS) -c $(GLAD_SRC) -o bin/glad/glad.o

# Create a bin directory which mirrors the source directory
bin: 
	mkdir bin 
	for dir in src/*; do \
		if [ -d $${dir} ]; then \
			mkdir bin/$${dir##*/}; \
		fi \
	done
	mkdir bin/glad


clean:
	rm -rf bin
