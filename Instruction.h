#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

typedef enum {
    Integer_Instruction = 1,
    Floating_Point_Instruction = 2,
    Branch = 3,
    Load = 4,
    Store = 5,
}InstructionType;

class Instruction{
    private:
        int program_counter;
        InstructionType instruciton_type;
        vector<int> *dependencies;

    public:
        Instruction(int program_counter, InstructionType it);
        ~Instruction();
        int getProgramCounter() const;
        InstructionType getInstructionType() const;
        vector<int> * getDependencies() const;
        void addDependency(int depen);

        friend std::ostream& operator<<(std::ostream& os, const Instruction& instr) {
            os << "Instruction: Program Counter=" << hex << instr.program_counter
            << ", Type=" << instr.instruciton_type
            << ", Dependencies=[ ";
            for (auto dep : *(instr.dependencies)) {
                os << hex << dep << " ";
            }
            os << "]";
        return os;
    }
};