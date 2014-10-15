#include "linear.h"
#include <iostream>
using namespace std;

void DefaultSvmParam(struct parameter *param);
void SwitchForSvmParma(struct parameter *param, char ch, char *strNum, int nr_fold, int cross_validation);
void SetSvmParam(struct parameter *param, char *str, int cross_validation, int nr_fold);
//void SvmTraining(char *option);
