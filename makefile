CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc/include
SRC = src/main.cpp
BIN_DIR = bin
TARGET = $(BIN_DIR)

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(BIN_DIR)

rebuild: clean all
