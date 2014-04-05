 CC = g++
 COMPILE_FLAGS = -std=c++11
 LINK_FLAGS =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
   LINK_FLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif
ifeq ($(UNAME_S),Linux)
   COMPILE_FLAGS += `pkg-config --cflags glfw3`
   LINK_FLAGS += `pkg-config --libs glfw3`
endif

EXECUTABLE = Restoration
SOURCES = $(wildcard *.cpp **/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

BUILD = $(SOURCES) $(EXECUTABLE)

all: $(BUILD)

debug: LINK_FLAGS += -g
debug: COMPILE_FLAGS += -g
debug: $(BUILD)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LINK_FLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) -c $< -o $@ $(COMPILE_FLAGS)

clean:
	find . -name '*.o' -type f -delete
	rm $(EXECUTABLE)