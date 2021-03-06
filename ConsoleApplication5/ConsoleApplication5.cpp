﻿// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include "fann.h"



//final version

int main()
{
	int ret = 0;
	int i;

	printf("Creating network.\n");

	struct fann *ann = fann_create_standard(3,3,30,2);


	if (!ann)
	{
		printf("Error creating ann --- ABORTING.\n");
		return -1;
	}

	fann_print_connections(ann);
	fann_print_parameters(ann);

	printf("Testing network.\n");

	/*
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_learning_momentum(ann, 0.5);
	fann_set_bit_fail_limit(ann,100);
	fann_save(ann, "weather_float.net");*/



	//nn name, data file, number of epochs, epoch between reports, desired error rate
	fann_train_on_file(ann, "finaldata.data", 2000, 500, 0.0005);

	

	fann_type *calc_out;
	fann_type input[3];

	printf("Testing network for  20-30 December\n");
	printf("(Day:354 = 20 December) \n");
	
	
	float inputday[5] = {3.62,3.63,3.64,3.65,0.01};
	float realtemp[5] = {0.19,0.22,0.20,0.17,0.16};
	float realprec[5] = {0,0,0,0.05,0.04};



	for (i=0;i<5;i++)
	{ 
		input[0] = inputday[i]; 
		input[1] = realprec[i];
		input[2] = realtemp[i];
		calc_out = fann_run(ann, input);

		printf("Day: %f  Precipation %f  Max. Temp: %f\n", input[0]*100, calc_out[0]*100, calc_out[1]*100);
	}

	fann_type *calc_out2;
	fann_type input2[3];
	input2[0] = 0.02;
	input2[1] = 0.01;
	input2[2] = 0.17;

	calc_out2 = fann_run(ann, input2);

	printf("Day: %f  Precipation %f  Max. Temp: %f\n", input2[0] * 100, calc_out2[0] * 100, calc_out2[1] * 100);

	fann_destroy(ann);
	system("pause");
	return ret;
}










// old version
/*
int main()
{
	int ret = 0;
	int i;

	printf("Creating network.\n");

	struct fann *ann = fann_create_standard(3,1,29,2);


	if (!ann)
	{
		printf("Error creating ann --- ABORTING.\n");
		return -1;
	}

	fann_print_connections(ann);
	fann_print_parameters(ann);

	printf("Testing network.\n");





	//nn name, data file, number of epochs, epoch between reports, desired error rate
	fann_train_on_file(ann, "shufd2.data", 2000, 500, 0.0005);

	

	fann_type *calc_out;
	fann_type input[1];

	printf("Testing network for  20-30 December\n");
	printf("(Day:354 = 20 December) \n");


	for (i=0;i<11;i++)
	{ 
		input[0] = (354+i)/100.0; //December 20th
		calc_out = fann_run(ann, input);

		printf("Day: %f  Precipation %f  Max. Temp: %f\n", input[0]*100, calc_out[0]*100, calc_out[1]*100);
	}

	fann_destroy(ann);
	system("pause");
	return ret;
}
*/
