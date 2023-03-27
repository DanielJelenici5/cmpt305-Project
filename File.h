#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Instruction.h"


using namespace std;


class File{

    private:
        static ifstream *file;
        int start_instruction;

    public:
        File(string filePath, int start_instruction);
        ~File();
        static Instruction ReadLine();
};