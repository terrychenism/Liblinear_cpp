#include <iostream>
#include <fstream>
#include "linear.h"
#include "classifier.h"
#include "svmutil.h"


using namespace std;

extern int max_nr_attr;
extern int num_features;
extern int test_set_size,train_set_size;
extern double **m; // data matrix

extern struct feature_node *x;
extern struct model* model_;
extern struct problem prob;
extern struct parameter param;
extern struct feature_node *x_space;


char *option = "-s 1 -q";
double train_set_ratio = 0.5; 



int main(int argc, char* argv[]){
	
	read_problem("ffff.train");
	DefaultSvmParam(&param);
	model_ = train(&prob, &param);

	FILE *input = fopen("ffff.train","r");
	FILE *output = fopen("result.txt","w");
	do_predict(input,output);	

	destroy_param(&param);
	free(prob.y);
	free(prob.x);
	free(x);
	free(x_space);	
	fclose(output);
	fclose(input);
	free_and_destroy_model(&model_);
	system("pause");

	return 0;
}