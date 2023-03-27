#include <stdio.h>
#include <vector>
#include <iostream>

#include "Pipeline.h"


Pipeline::Pipeline(int start_instruction, int instructions_to_run, int width){
    this->PCtoDependenciesMap = new map<int, vector <int>>;
    this->width = width;
    this->start_instruction = start_instruction;
    this->branch_lock = false;
    this->instructions_to_run = instructions_to_run;
    this->instrucitons_ran = 0;
}

Pipeline::~Pipeline(){
    //causing problems probs due to the value vector<int> being already freed in the instructions destructor
    //delete this->instrucitons;
}

void Pipeline::addToInstructions(const Instruction& instr){
    vector <int> vec = instr.getDependencies();
    pair<int, vector <int>> instrPair(instr.getProgramCounter(), vec);
    this->PCtoDependenciesMap->insert(instrPair);
}

void Pipeline::GetCompletedInstructions(){
    for(int i = 0 ; i < this->start_instruction; i++){
        Instruction instr = File::ReadLine();
        addToInstructions(instr);
        
    }
}

const vector<int>& Pipeline::getAllDependeciesForPC(int pc){
    return this->PCtoDependenciesMap->at(pc);
}

void Pipeline::printAllInstructionsDependecies(){
    for (auto it = this->PCtoDependenciesMap->begin(); it != this->PCtoDependenciesMap->end(); it++) {
        cout << "pc: " << hex << it->first << ", Dependencies=[ ";
            for (auto dep : (it->second)) {
                cout << hex << dep << " ";
            }
            cout << "]" << endl;
    }
}

void Pipeline::Process_IF(){
    for (int i = 0; i < this->width; i ++){
        if (branch_lock){
            //if locked, do nothing
            return;
        }

        Instruction instr = File::ReadLine();
        this->instrucitons_ran++;

        if(instr.getInstructionType() == Branch){
            this->branch_lock = true;
        }

        // check if this is the last Instruction
		if (this->instrucitons_ran == this->instructions_to_run){
			//TODO:
		}

        

    }
}