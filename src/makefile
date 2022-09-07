TARGET = main

SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))

CXX_FLAGS = -std=c++14 -Wall
OPENGL_FLAGS = -lGL -lglfw3 -lX11 -lGLEW

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	g++ $^ $(OPENGL_FLAGS) -o $@

%.o: %.cpp
	g++ $(CXX_FLAGS) -c $< -o $@

.PHONY: clean all

clean:
	rm -rf $(OBJ_FILES) $(TARGET)