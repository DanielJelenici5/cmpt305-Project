#include <stdio.h>
#include <vector>

#include "Instruction.h"
using namespace std;


Instruction::Instruction(int program_counter, InstructionType it){
    this->program_counter = program_counter;
    this->instruciton_type = it;
    this->dependencies = new vector<int>;
}

Instruction::~Instruction(){
    delete this->dependencies;
}

int Instruction::getProgramCounter() const{
    return this->program_counter;
}

InstructionType Instruction::getInstructionType() const{
    return this->instruciton_type;
}

vector<int> *Instruction::getDependencies() const{
    return this->dependencies;
}

void Instruction::addDependency(int depen){
    this->dependencies->push_back(depen);
}

