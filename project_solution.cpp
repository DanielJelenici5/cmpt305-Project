#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<float.h>
#include <string.h>

#include <cmath>
#include <random>
#include <iostream>
#include <vector>
#include <array>
#include <string>


#include "File.h"

using namespace std;


int main(int argc, char* argv[]){
	if(argc >= 5){
		string file_path = argv[1];
		int start_inst = atoi(argv[2]);
		int run_inst = atoi(argv[3]);
		int pipeline_width = atoi(argv[4]);
   
		//TODO: Add error checks

		Pipeline pipeline(pipeline_width);
		File file(file_path, start_inst, pipeline);
		file.GetCompletedInstructions();
		pipeline.printAllInstructionsDependecies();
	}
	else printf("Insufficient number of arguments provided!\n");
   
	return 0;
}