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


#include "Pipeline.h"

using namespace std;

void PrintReport(Pipeline& pipeline, int cycles){
	int sum = pipeline.getAllSumStats();

	printf("Simulation clock: %d\n\n", cycles);

	printf("The total execution time (in cycles) at the end of simulation: %d\n\n", cycles);

	printf("Histogram containing the breakdown of retired instructions by instruction type: \n");
	printf("%.2f%% are integer instructions\n", ((float)(pipeline.getStat(Integer_Instruction))/sum) * 100);
	printf("%.2f%% are floating point instructions\n", ((float)(pipeline.getStat(Floating_Point_Instruction))/sum) * 100);
	printf("%.2f%% are branch instructions\n", ((float)(pipeline.getStat(Branch))/sum) * 100);
	printf("%.2f%% are load instructions\n", ((float)(pipeline.getStat(Load))/sum) * 100);
	printf("%.2f%% are store instructions\n", ((float)(pipeline.getStat(Store))/sum)* 100);
}

void Simulation(Pipeline& pipeline){

	int cycle = 0;
		while(pipeline.getEndSim() == false){
			pipeline.Process_IF();
			pipeline.Proccess_ID();
			pipeline.Process_EX();
			pipeline.Process_MEM();
			pipeline.Process_WB();

			pipeline.flushInterQueuesAndResetLocks();
			cycle++;
		}
	PrintReport(pipeline, cycle);
}


int main(int argc, char* argv[]){
	if(argc >= 5){
		string file_path = argv[1];
		int start_inst = atoi(argv[2]);
		int run_inst = atoi(argv[3]);
		int pipeline_width = atoi(argv[4]);
   
		//TODO: Add error checks

		Pipeline pipeline(start_inst,run_inst, pipeline_width);
		File file(file_path, start_inst);
		pipeline.FindCompletedInstructions();

		Simulation(pipeline);

	}
	else printf("Insufficient number of arguments provided!\n");
   
	return 0;
}