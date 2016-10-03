/* Name: Joe Wong
Pawprint jlwxz8
assign:	Prelab6 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define NAMELENGTH 20
#define DIGITMAX 20
enum data_t{NAME, HOMEWORK, QUIZ, TEST};

typedef struct student{
	char* name;
	double* homework;
	double* quiz;
	double* test;
	double wAverage;
	}student;

int scan_info(student* fred, enum data_t student_data, int length);
double average(double* array, int length);
double weighted_average(double hw, double quiz, double test);
int get_int(void);
double get_double(void);
void free_student(student* array, int length);

int scan_info(student* fred, enum data_t student_data, int length){
	int i;
	double *ptr;
	switch (student_data){ //Split the function into 4 cases and scan data accordingly
		case NAME:
			fred->name = malloc(sizeof(char)*NAMELENGTH);
			if (fred->name == NULL) return -1;
			printf("Please enter student's name: ");
			scanf("%s", fred->name);
			getchar();
			break;
		case HOMEWORK:
			fred->homework = malloc(sizeof(double)*length);
			if (fred->homework == NULL) return -1;
			ptr = fred->homework;
			for (i=0; i<length; i++){
				printf("Please enter %s's homework grade %d ",fred->name,i+1);
				*ptr = get_double();
				ptr++;
			}
			break;
		case QUIZ:	
			fred->quiz = malloc(sizeof(double)*length);
			if (fred->quiz == NULL) return -1;
			ptr = fred->quiz;
			for (i=0; i<length; i++){
				printf("Please enter %s's quiz grade %d ",fred->name,i+1);
				*ptr = get_double();
				ptr++;
			}
			break;
		case TEST:	
			fred->test = malloc(sizeof(double)*length);
			if (fred->test == NULL) return -1;
			ptr = fred->test;
			for (i=0; i<length; i++){
				printf("Please enter %s's test grade %d ",fred->name,i+1);
				*ptr = get_double();
				ptr++;
			}
			break;
	}
return i;
}

double average(double* array, int length){
	int i;
	double avg=0;
	for (i=0; i<length; i++){
		avg += array[i];
	}
	return avg/length;
}

double weighted_average(double hw, double quiz, double test){
	return (hw * .1 + quiz * .3 + test * .6);
	
}

int get_int(void){
	int number = 0, i = 0, check_error = 0;
	char temp[DIGITMAX]= "";
	
	fgets(temp, sizeof(temp), stdin);// scan in the input line to temp array
	for (i=0 ; *(temp+i)!='\n' ; i++){
		if (!isdigit(*(temp +i))) check_error--;// de-bump flag if char is not digit
	}
	if (*temp == '-') check_error++;// bump flag if first char is a minus sign
	if (check_error == 0)
	check_error = sscanf(temp, "%d", &number);//if the input is ok scan the int into number
	
	if (check_error < 1 || number < -1)// if input is not ok return negative
		return -2;
return number;	
}//end get_int

double get_double(void){

	double number = 0;
	int  i = 0, check_error = 0, check_period=0;
	char temp[DIGITMAX]= "";
	
	fgets(temp, sizeof(temp), stdin);// scan in the input line to temp array
	for (i=0 ; *(temp+i)!='\n' ; i++){
		if (!isdigit(*(temp +i))) check_error--;// de-bump flag if char is not digit
		if (*(temp+i)== '.' && check_period == 0){ //check for period, if found bump flag
			check_error++;
			check_period++;
		}
	}
	if (*temp == '-') check_error++;// bump flag if first char is a minus sign
	if (check_error == 0)
	check_error = sscanf(temp, "%lf", &number);//if the input is ok scan the int into number
	
	if (check_error < 1 || number < -1)// if input is not ok return negative
		return -2;
return number;	
}

void free_student(student* studptr, int length){
	int i;
	student* temp = studptr;
	for (i=0; i<length; i++){
		free(studptr->name);
		free(studptr->homework);
		free(studptr->quiz);
		free(studptr->test);
		free(temp);
	}
}

int main(void){
	int num_quiz=0, num_test=0, num_homework=0;
	double avg_quiz=0, avg_test=0, avg_homework=0;

	student* stud_ptr = malloc(sizeof(student));
	scan_info(stud_ptr,NAME,1);
	
	do{
		printf("Please enter number of homework grades. ");
		num_homework = get_int();
	}while(num_homework <= 0);

	do{
		printf("Please enter number of quiz grades. ");
		num_quiz = get_int();
	}while(num_quiz <= 0);	

	do{
		printf("Please enter number of test grades. ");
		num_test = get_int();
	}while(num_test <= 0);

	scan_info(stud_ptr,HOMEWORK,num_homework);
	scan_info(stud_ptr,QUIZ,num_quiz);
	scan_info(stud_ptr,TEST,num_test);
	
	avg_homework = average(stud_ptr->homework,num_homework);
	avg_quiz = average(stud_ptr->quiz,num_quiz);
	avg_test = average(stud_ptr->test,num_test);
	stud_ptr->wAverage = weighted_average(avg_homework,avg_quiz,avg_test);

	printf("%s's homework average is %lf\n",stud_ptr->name,avg_homework);	
	printf("%s's quiz average is %lf\n",stud_ptr->name,avg_quiz);
	printf("%s's test average is %lf\n",stud_ptr->name,avg_test);
	
	printf("%s's weighted average is %lf\n",stud_ptr->name,stud_ptr->wAverage);

	free_student(stud_ptr,1);
return 0;
}

