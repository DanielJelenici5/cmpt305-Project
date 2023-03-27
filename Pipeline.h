#include <stdio.h>
#include <vector>
#include <map>

#include "File.h"

class Pipeline{
    private:
        map<int, vector <int>> *PCtoDependenciesMap;
        int width;
        int start_instruction;
        int instructions_to_run;
        int instrucitons_ran;
        bool branch_lock;

    public: 
        Pipeline(int start_instruction,int instructions_to_run, int width);
        ~Pipeline();
        void addToInstructions(const Instruction& instr);
        const vector<int>& getAllDependeciesForPC(int pc);
        void GetCompletedInstructions();
        void printAllInstructionsDependecies();
        void Process_IF();
};