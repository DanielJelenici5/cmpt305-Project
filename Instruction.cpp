#include <stdio.h>
#include <vector>

#include "Instruction.h"
using namespace std;


Instruction::Instruction(int program_counter, int it){
    this->program_counter = program_counter;
    this->instruciton_type = static_cast<InstructionType>(it);
}

Instruction::~Instruction(){
}

int Instruction::getProgramCounter() const{
    return this->program_counter;
}

InstructionType Instruction::getInstructionType() const{
    return this->instruciton_type;
}

const vector<int>& Instruction::getDependencies() const{
    return this->dependencies;
}

void Instruction::addDependency(int depen){
    this->dependencies.push_back(depen);
}

