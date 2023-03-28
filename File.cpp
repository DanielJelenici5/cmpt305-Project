#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "File.h"
#include "SimException.h"

using namespace std;

// Initialize static variable
ifstream* File::file = nullptr;
int File::currentLineNumber = -1;

File::File(string filePath, int start_instruction){
    this->file = new ifstream(filePath);
    this->start_instruction = start_instruction;
    this->currentLineNumber=1;
}

File::~File() {
    if(file != nullptr && file->is_open()) {
        file->close();
    }
    delete file;  // delete the dynamically allocated ifstream object
}

Instruction File::ReadLine() {
    if (file->is_open()) {
        string line;
        if(!getline(*file, line)){
            throw SimException("End of file");
        }
        if(line.length() < 1){
            //TODO:throw exception
        }

        vector<std::string> row;  // vector to hold the row data
        istringstream tokenStream(line);  // create a stringstream from the line
        string token;
        // Split the line on the comma delimiter
        while (getline(tokenStream, token, ',')) {
            row.push_back(token);  // add the token to the row vector
        }

        Instruction instr( stoul(row.at(0), nullptr, 16), stoi(row.at(1)), File::currentLineNumber);
        for(long unsigned int i = 2; i < row.size(); i++){
            instr.addDependency(stoul(row.at(i), nullptr, 16));
        }
        File::currentLineNumber++;
        return instr;
    }
    //TODO:throw exception
}