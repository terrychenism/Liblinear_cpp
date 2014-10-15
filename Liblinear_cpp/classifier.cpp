#include "classifier.h"

double **m;
int num_features;
int test_set_size,train_set_size;
const char* model_file_name = "model.txt";




void DefaultSvmParam(struct parameter *param){
	param->solver_type = L2R_L2LOSS_SVC_DUAL;
	
	param->C = 1;
	
	param->p = 0.1;
	param->nr_weight = 0;
	param->weight_label = NULL;
	param->weight = NULL;

	switch(param->solver_type)
	{
	case L2R_LR: 
	case L2R_L2LOSS_SVC:
		param->eps = 0.01;
		break;
	case L2R_L2LOSS_SVR:
		param->eps = 0.001;
		break;
	case L2R_L2LOSS_SVC_DUAL: 
	case L2R_L1LOSS_SVC_DUAL: 
	case MCSVM_CS: 
	case L2R_LR_DUAL: 
		param->eps = 0.1;
		break;
	case L1R_L2LOSS_SVC: 
	case L1R_LR:
		param->eps = 0.01;
		break;
	case L2R_L1LOSS_SVR_DUAL:
	case L2R_L2LOSS_SVR_DUAL:
		param->eps = 0.1;
		break;
	}

}

void SwitchForSvmParma(struct parameter *param, char ch, char *strNum, int nr_fold, int cross_validation){
	
	switch(ch)
	{
	case 's':
		{
			param->solver_type = atoi(strNum);
			break;
		}
	case 'c':
		{
			param->C = atoi(strNum);
			break;
		}
	
	case 'q':
		{
			break;
		}
	case 'v':
		{
			cross_validation = 1;
			nr_fold = atoi(strNum);
			if (nr_fold < 2)		{
				cout<<"nr_fold should > 2!!! file: "<<__FILE__<<" function: ";
				cout<<__FUNCTION__<<" line: "<<__LINE__<<endl;
			}
			break;
		}
	case 'w':
		{
			++param->nr_weight;
			param->weight_label = (int *)realloc(param->weight_label,sizeof(int)*param->nr_weight);
			param->weight = (double *)realloc(param->weight,sizeof(double)*param->nr_weight);
			param->weight_label[param->nr_weight-1] = atoi(strNum);			 
			param->weight[param->nr_weight-1] = atof(strNum);
			break;
		}
	default:
		{
			break;
		}

	}

}


void SetSvmParam(struct parameter *param, char *str, int cross_validation, int nr_fold){
	DefaultSvmParam(param);
	cross_validation = 0;
	char ch = ' ';
	int strSize = strlen(str);
	for (int i=0; i<strSize; i++){
		if (str[i] == '-'){
			ch = str[i+1];
			int length = 0;
			for (int j=i+3; j<strSize; j++)	{
				if (isdigit(str[j]))
					length++;
				else
					break;
			}

			char *strNum = new char[length+1];
			int index = 0;
			for (int j=i+3; j<i+3+length; j++){
				strNum[index] = str[j];
				index++;
			}
			strNum[length] = '/0';
			SwitchForSvmParma(param, ch, strNum, nr_fold, cross_validation);
			delete strNum;
		}
	}
}


//void SvmTraining(char *option){
//	struct parameter param;
//	struct problem prob;
//	struct model *models;
//	struct feature_node *x_space;
//	int cross_validation = 0;
//	int nr_fold = 0;
//	/*int sampleCount = train_set_size;
//	int featureDim = num_features;*/
//	int sampleCount = 10;
//
//	int featureDim = 12;
//
//	prob.l =  sampleCount;
//	prob.y = new double[sampleCount];
//	prob.x = new struct feature_node*[sampleCount];
//	prob.n = 0;
//	prob.bias = -1;
//	x_space = new struct feature_node[(featureDim+1)*sampleCount];
//
//	// SetSvmParam(&param, option, cross_validation, nr_fold);
//	DefaultSvmParam(&param);
//
//	/*for (int i=0; i< sampleCount; i++)
//	prob.y[i] = m[i][0];
//
//
//	int j = 0;
//
//	for (int i=0; i<sampleCount; i++){
//	prob.x[i] = &x_space[j];
//	for (int k=1; k<=featureDim; k++){
//	x_space[i*featureDim+k].index = k;
//	x_space[i*featureDim+k].value = m[i][k];
//	}
//	x_space[(i+1)*featureDim].index = -1;
//	j = (i+1)*featureDim + 1; 
//	}*/
//	for (int i=0; i<sampleCount; i++)
//
//	{
//
//		prob.y[i] = inputArr[i][0];
//
//	}
//
//
//
//	int j = 0;
//
//	for (int i=0; i<sampleCount; i++)
//
//	{
//
//		prob.x[i] = &x_space[j];
//
//		for (int k=1; k<=featureDim; k++)
//
//		{
//
//			x_space[i*featureDim+k].index = k;
//
//			x_space[i*featureDim+k].value = inputArr[i][k];
//
//		}
//
//		x_space[(i+1)*featureDim].index = -1;
//
//		j = (i+1)*featureDim + 1; 
//
//	}
//	models = train(&prob, &param);	
//	save_model(model_file_name, models);
//	free_model_content(models);
//	destroy_param(&param);
//	delete[] prob.y;
//	delete[] prob.x;
//	delete[] x_space; 
//
//}