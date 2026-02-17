CXX = g++

WX_CXXFLAGS = `wx-config --cxxflags`
WX_LIBS     = `wx-config --libs`

CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc/include $(WX_CXXFLAGS)

SRC = \
	src/allqueendirec.cpp \
	src/inputfile.cpp \
	src/outputarr.cpp \
	src/wx_ui.cpp

BIN = bin/app

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(WX_LIBS)

clean:
	rm -rf bin/*

rebuild: clean all
