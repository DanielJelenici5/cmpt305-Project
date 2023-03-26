#include <stdio.h>
#include <vector>
#include <map>

#include "Instruction.h"

class Pipeline{
    private:
        map<int, vector <int>> *PCtoDependenciesMap;
        int width;

    public: 
        Pipeline(int width);
        ~Pipeline();
        void addToInstructions(const Instruction& instr);
        vector<int> getAllDependeciesForPC(int pc);
        void printAllInstructionsDependecies();
};