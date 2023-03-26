#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "Pipeline.h"

class File{

    private:
        ifstream *file;
        int start_instruction;
        Pipeline pipeline;

    public:
        File(string filePath, int start_instruction, const Pipeline& pl);
        ~File();
        void GetCompletedInstructions();
};