#include <stdio.h>
#include <vector>
#include <map>
#include <queue>

#include "File.h"

using namespace std;


class Pipeline{
    private:
        map<int, vector <int>> *completedInstructions;
        map<int, vector <int>> *ongoingInstructions;
        int width;
        int start_instruction;
        int instructions_to_run;
        int instrucitons_ran;

        bool end_sim;

        //queues
        queue<Instruction> ID_Q;
        queue<Instruction> EX_Q;
        queue<Instruction> MEM_Q;
        queue<Instruction> WB_Q;
        // intermediate Q -> are used to update queues mid cycle and flushed to normal queues above at end of cycle
        queue<Instruction> ID_Q_inter;
        queue<Instruction> EX_Q_inter;;
        queue<Instruction> MEM_Q_inter;
        queue<Instruction> WB_Q_inter;

        //locks 
        bool branch_lock;
        bool int_EX_lock;
        bool float_EX_lock;
        bool store_MEM_lock;
        bool load_MEM_lock;

        //stats
        map<InstructionType, int> stats;

        bool DependenciesCompletedCheck(const Instruction& instr);

    public: 
        Pipeline(int start_instruction,int instructions_to_run, int width);
        ~Pipeline();
        void addToInstructions(const Instruction& instr, bool ongoing);
        const vector<int>& getAllDependeciesForPC(int pc);
        bool getEndSim() const;
        void FindCompletedInstructions();
        void printInstructionsDependecies(bool completed);
        void Process_IF();
        void Proccess_ID();
        void Process_EX();
        void Process_MEM();
        void Process_WB();
        void flushInterQueuesAndResetLocks();
        int getStat(InstructionType type);
        int getAllSumStats();
};