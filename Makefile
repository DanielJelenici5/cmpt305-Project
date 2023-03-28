CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCS = project_solution.cpp Instruction.cpp File.cpp Pipeline.cpp
OBJS = $(SRCS:.cpp=.o)
HEADER = Instruction.h File.h Pipeline.h SimException.h
EXECUTABLE = proj

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXECUTABLE)

project_solution.o: project_solution.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c project_solution.cpp

Instruction.o: Instruction.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c Instruction.cpp 

File.o: File.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c File.cpp 

Pipeline.o: Pipeline.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c Pipeline.cpp 

clean:
	rm -f $(OBJS) $(EXECUTABLE)