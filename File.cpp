#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "File.h"

using namespace std;

// Initialize static variable
ifstream* File::file = nullptr;

File::File(string filePath, int start_instruction){
    this->file = new ifstream(filePath);
    this->start_instruction = start_instruction;
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
            //TODO:throw exception
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

        Instruction instr( stoul(row.at(0), nullptr, 16), stoi(row.at(1)));
        for(long unsigned int i = 2; i < row.size(); i++){
            instr.addDependency(stoul(row.at(i), nullptr, 16));
        }
        return instr;
    }
    //TODO:throw exception
}