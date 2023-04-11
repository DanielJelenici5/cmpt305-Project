#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "Pipeline.h"
#include "SimException.h"

using namespace std;

//----------------------------------------------------------PRIVATE----------------------------------------------------------//

bool Pipeline::DependenciesCompletedCheck(const Instruction& instr){
    vector <unsigned long int> dependencies = instr.getDependencies();
    for(int dependency : dependencies){
        auto it = this->completedInstructions.find(dependency);
        if(it == this->completedInstructions.end()){
            //dependency not completed
            return false;
        }
    }

    return true;
}

void Pipeline::printSet(unordered_set<int> mySet){
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

//----------------------------------------------------------PUBLIC----------------------------------------------------------//

Pipeline::Pipeline(int start_instruction, int instructions_to_run, int width){
    this->width = width;
    this->start_instruction = start_instruction;
    this->branch_lock = false;
    this->instructions_to_run = instructions_to_run;
    this->instrucitons_ran = 0;
    this->int_EX_lock = false;
    this->float_EX_lock = false;
    this->store_MEM_lock = false;
    this->load_MEM_lock = false;
    this->end_sim = false;

    //init stats
    this->stats.emplace(Integer_Instruction, 0);
    this->stats.emplace(Floating_Point_Instruction, 0);
    this->stats.emplace(Branch, 0);
    this->stats.emplace(Load, 0);
    this->stats.emplace(Store, 0);
}

Pipeline::~Pipeline(){
    //causing problems probs due to the value vector<int> being already freed in the instructions destructor
    //delete this->instrucitons;
}

bool Pipeline::getEndSim() const{
    return this->end_sim;
}

void Pipeline::addToInstructions(const Instruction& instr, bool ongoing){
    vector <unsigned long int> vec = instr.getDependencies();
    int PC = instr.getProgramCounter();

    if(ongoing == false){
        this->completedInstructions.insert(PC);
    }
    else{ //instruction is ongoing
        this->ongoingInstructions.insert(PC);
    }
 
}

void Pipeline::FindCompletedInstructions(){
    for(int i = 1 ; i < this->start_instruction; i++){
        Instruction instr = File::ReadLine();
        addToInstructions(instr, false);
        
    }
}

void Pipeline::Process_IF(){
    for (int i = 0; i < this->width; i++){
        if (branch_lock){
            //if locked, do nothing -> we have to wait for branch to pass EX
            return;
        }
        if(this->instrucitons_ran > instructions_to_run){
            return;
        }

        Instruction instr;
        try{
            instr = File::ReadLine();
            this->instrucitons_ran++;
        } catch (SimException& ex){
            //end of file
            this->end_sim = true;
            return;
        }      

        addToInstructions(instr, true);

        if(instr.getInstructionType() == Branch){
            this->branch_lock = true;
        }

        // check if this is the last Instruction
		if (this->instrucitons_ran == this->instructions_to_run){
            instr.setLastInstruction();
		}

        this->ID_Q_inter.push(instr);
    }
}

void Pipeline::Proccess_ID(){
    for (int i = 0; i < this->width; i++){
        if(this->ID_Q.empty()){
            return;
        }

        Instruction instr = this->ID_Q.front();
        ID_Q.pop();
        this->EX_Q_inter.push(instr);
    }
}

void Pipeline::Process_EX(){
    for (int i = 0; i < this->width; i++){
        if(this->EX_Q.empty()){
            return;
        }

        Instruction instr = this->EX_Q.front();


        if(DependenciesCompletedCheck(instr) == false){
            // dependecy not satisifed -> in-order execution, instructions cannot proceed to a pipeline stage before an earlier instructions has done so
            return;
        }

        if(instr.getInstructionType() == Integer_Instruction){
            if(this->int_EX_lock){
                //An integer instruction cannot execute in the same cycle as another integer instruction
                return;
            }
            this->int_EX_lock = true;
        }

        if(instr.getInstructionType() == Floating_Point_Instruction){
            if(this->float_EX_lock){
                //A floating point instruction cannot execute in the same cycle as another floating point instruction
                return;
            }
            this->float_EX_lock = true;
        }

        if(instr.getInstructionType() == Branch){
            this->branch_lock = false;
        }

        this->EX_Q.pop();

        if(instr.getInstructionType() == Integer_Instruction || instr.getInstructionType() == Floating_Point_Instruction || instr.getInstructionType() == Branch){
                     
            addToInstructions(instr, false);
            
        }

        this->MEM_Q_inter.push(instr);
    }
}

void Pipeline::Process_MEM(){
    for (int i = 0; i < this->width; i++){
        if(this->MEM_Q.empty()){
            return;
        }

        Instruction instr = this->MEM_Q.front();

        if(instr.getInstructionType() == Load){
            if(this->load_MEM_lock){
                //A load instruction cannot go to the MEM stage in the same cycle as another load instruction.
                return;
            }
            this->load_MEM_lock = true;
        }

        if(instr.getInstructionType() == Store){
            if(this->store_MEM_lock){
                //A store instruction cannot go to the MEM stage in the same cycle as another store instruction.
                return;
            }
            this->store_MEM_lock = true;
        }

        this->MEM_Q.pop();

        if(instr.getInstructionType() == Load || instr.getInstructionType() == Store){
            addToInstructions(instr, false);
        }

        this->WB_Q_inter.push(instr);
    }
}

void Pipeline::Process_WB(){
    for (int i = 0; i < this->width; i++){
        if(this->WB_Q.empty()){
            return;
        }

        Instruction instr = this->WB_Q.front();

        switch (instr.getInstructionType()){
            case Integer_Instruction:
                this->stats[Integer_Instruction]++;
                break;
            case Floating_Point_Instruction:
                this->stats[Floating_Point_Instruction]++;
                break;
            case Branch:
                this->stats[Branch]++;
                break;
            case Load:
                this->stats[Load]++;
                break;
            case Store:
                this->stats[Store]++;
                break;
        }

        if(instr.isLastInstruction()){
            this->end_sim = true;
        }

        this->WB_Q.pop();
    }
}

void Pipeline::flushInterQueuesAndResetLocks(){
	while(!ID_Q_inter.empty()){
		ID_Q.push(ID_Q_inter.front());
		ID_Q_inter.pop();
	}

	while(!EX_Q_inter.empty()){
		EX_Q.push(EX_Q_inter.front());
		EX_Q_inter.pop();
	}

	while(!MEM_Q_inter.empty()){
		MEM_Q.push(MEM_Q_inter.front());
		MEM_Q_inter.pop();
	}

	while(!WB_Q_inter.empty()){
		WB_Q.push(WB_Q_inter.front());
		WB_Q_inter.pop();
	}


    this->int_EX_lock = false;
	this->float_EX_lock = false;
	this->load_MEM_lock = false;
	this->store_MEM_lock = false;
}

int Pipeline::getStat(InstructionType type){
    return this->stats[type];
}

int Pipeline::getAllSumStats(){
    return this->stats[Integer_Instruction] + this->stats[Floating_Point_Instruction] + this->stats[Branch] + this->stats[Load] + this->stats[Store];
}
