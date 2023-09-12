CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

EXECUTABLE = fileserver

SRC_FILES = src/fileserver.cpp hashMaterials/hashmap.h hashMaterials/linkedlist.h hashMaterials/llnode.h

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) src/fileserver.cpp

clean:
	rm -f $(EXECUTABLE)