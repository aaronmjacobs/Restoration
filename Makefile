CC = g++
COMPILE_FLAGS = -std=c++11
LINK_FLAGS =
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = Restoration

SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
OBJECTS = $(subst $(SRC_DIR),$(BUILD_DIR),$(SOURCES:.cpp=.o))
BUILD_FOLDERS = $(subst $(SRC_DIR),$(BUILD_DIR), $(shell find src -type d))
BUILD = $(BUILD_OBJECTS) $(EXECUTABLE)

ifeq ($(OS),Windows_NT)
   COMPILE_FLAGS += -DGL_GLEXT_PROTOTYPES
   LINK_FLAGS += -lglfw3 -lopengl32
else
   UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Darwin)
      LINK_FLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
   endif
   ifeq ($(UNAME_S),Linux)
      COMPILE_FLAGS += `pkg-config --cflags glfw3`
      LINK_FLAGS += `pkg-config --libs glfw3`
   endif
endif

all: build_folders
all: $(BUILD)

debug: LINK_FLAGS += -g
debug: COMPILE_FLAGS += -g
debug: all

build_folders:
	mkdir -p $(BUILD_FOLDERS)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LINK_FLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $(subst $(SRC_DIR),$(BUILD_DIR),$@) $(COMPILE_FLAGS)

clean:
	find . -name '*.o' -type f -delete
	rm $(EXECUTABLE)