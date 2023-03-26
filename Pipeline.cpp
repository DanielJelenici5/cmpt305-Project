#include <stdio.h>
#include <vector>
#include <iostream>

#include "Pipeline.h"


Pipeline::Pipeline(int width){
    this->PCtoDependenciesMap = new map<int, vector <int>>;
    this->width = width;
}

Pipeline::~Pipeline(){
    //causing problems probs due to the value vector<int> being already freed in the instructions destructor
    //delete this->instrucitons;
}

void Pipeline::addToInstructions(const Instruction& instr){
    vector <int> *vec = instr.getDependencies();
    pair<int, vector <int>> instrPair(instr.getProgramCounter(), *vec);
    this->PCtoDependenciesMap->insert(instrPair);
}

vector<int> Pipeline::getAllDependeciesForPC(int pc){
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