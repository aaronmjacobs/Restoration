CC = g++
COMPILE_FLAGS = -std=c++11
LINK_FLAGS = -lassimp
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = Restoration

ifdef DEBUG
LINK_FLAGS += -g
COMPILE_FLAGS += -g
BUILD_DIR = build_debug
EXECUTABLE = Restoration_debug
endif

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(subst $(SRC_DIR),$(BUILD_DIR),$(SOURCES:.cpp=.o))
BUILD_FOLDERS = $(subst $(SRC_DIR),$(BUILD_DIR), $(shell find src -type d))
BUILD = $(OBJECTS) $(EXECUTABLE)

ifeq ($(OS),Windows_NT)
   COMPILE_FLAGS += -DGL_GLEXT_PROTOTYPES
   LINK_FLAGS += -lglfw3 -lopengl32
else
   UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Darwin)
      LINK_FLAGS += -lfmod -lglfw3 -ljson_linux-gcc-4.2.1_libmt -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
   endif
   ifeq ($(UNAME_S),Linux)
      COMPILE_FLAGS += `pkg-config --cflags glfw3`
      LINK_FLAGS += `pkg-config --libs glfw3`
   endif
endif

all: build_folders
all: $(BUILD)

build_folders:
	mkdir -p $(BUILD_FOLDERS)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LINK_FLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $(subst $(SRC_DIR),$(BUILD_DIR),$@) $(COMPILE_FLAGS)

clean:
	cd $(BUILD_DIR) && find . -name '*.o' -type f -delete
	rm $(EXECUTABLE)