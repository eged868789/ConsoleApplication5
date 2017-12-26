// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include "fann.h"

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

	/*
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_learning_momentum(ann, 0.5);
	fann_set_bit_fail_limit(ann,100);
	fann_save(ann, "weather_float.net");*/



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

