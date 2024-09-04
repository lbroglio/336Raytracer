CC= g++
APPNAME= raytrace336
SOURCES= file-io/imageOut.cpp \
		 file-io/modelReaders.cpp \
		 raycast/raycast.cpp\
		 world/vectors.cpp \
		 world/worldObjects.cpp \
		 raytrace336.cpp
BINDIR= bin
OBJECTS = $(SOURCES:%.cpp=$(BINDIR)/%.o)
TARGET= $(BINDIR)/$(APPNAME)
CCFLAGS= -Wall -Werror

.PHONY: clean all

all: $(TARGET)

$(TARGET): bin $(OBJECTS) 
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(TARGET)

bin/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# Create a bin directory which mirrors the source directory
bin: 
	mkdir bin 
	for dir in src/*; do \
		if [ -d $${dir} ]; then \
			mkdir bin/$${dir##*/}; \
		fi \
	done

	
clean:
	rm -rf bin
