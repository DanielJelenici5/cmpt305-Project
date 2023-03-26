#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "File.h"

using namespace std;

File::File(string filePath, int start_instruction, const Pipeline& pl) : pipeline(pl){
    this->file = new ifstream(filePath);
    this->start_instruction = start_instruction;
}

File::~File(){
    if(this->file->is_open()){
        this->file->close();
    }
    //delete this->file;
}

void File::GetCompletedInstructions(){
        if (file->is_open()) {
        string line;
        // Read the file line by line
        while (getline(*file, line)) {
            vector<std::string> row;  // vector to hold the row data
            istringstream tokenStream(line);  // create a stringstream from the line
            string token;
            // Split the line on the comma delimiter
            while (getline(tokenStream, token, ',')) {
                row.push_back(token);  // add the token to the row vector
            }

            Instruction instr( stoul(row.at(0), nullptr, 16), static_cast<InstructionType>(stoi(row.at(1))));
            for(long unsigned int i = 2; i < row.size(); i++){
                instr.addDependency(stoul(row.at(i), nullptr, 16));
            }
            pipeline.addToInstructions(instr);
        }
    }

}