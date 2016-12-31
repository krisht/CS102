/*
 * Name: 			StudentGrader.c
 * Written by:		Carl Sable
 * Modified by: 	Krishnan Thiyagarajan
 *
 * Description: 	This program reads student information from a specified text file.
 * 					Each student has a first and last name, @NumHW number of homework scores
 * 					and one test score. The following program computes the weighted average
 * 					for each student and sorts the data based on the users preference, either
 * 					by average score or by last name. The program computes the weighted average.
 * 					The user has to enter a weighting between 0 and 1
 * 					This program reads student information from a specified text file.
 * 					Each student has an associated first and last name, NumHW number of homework
 * 					scores, and one test score. The program computes the weighted
 * 					average score for each student, and sorts the data based on names or grades
 * 					depending on user input.  The updated information is written to a specified
 * 					text file.
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int NumHW; /* declares a global variable to store Number of HWs for that class (Used in multiple functions)*/

struct student
{
	char lastName[30];  /* last name */
	char firstName[30]; /* first name */
	int *homeworks;  /* scores on homeworks */
	int test;  /* score on test */
	float final;  /* final average */
	char letterGrade; /* letter grade i.e. A, B C, D or F */
};



typedef struct student STUDENT;

STUDENT *input_students(int *);
void compute_averages(STUDENT [], int);
void sort_students(STUDENT [], int);
void swap_students(STUDENT *, STUDENT *);
void display_students(STUDENT [], int);

int main(void)
{
	STUDENT *pStudents;
	int numStudents;

	pStudents = input_students(&numStudents);
	compute_averages(pStudents, numStudents);
	sort_students(pStudents, numStudents);
	display_students(pStudents, numStudents);

	free(pStudents);

	return 0;
}

/* Read all student data(including # of students and homework for each student) from a specified text file */
STUDENT *input_students(int *pNumStudents)
{
	int x, y;
	char filenameInput[30];
	FILE *fpInput;
	STUDENT *pStudents;

	printf("Enter name of input file: ");
	scanf("%s", filenameInput);

	fpInput = fopen(filenameInput, "r");
	if (fpInput == NULL)
	{
		fprintf(stderr, "Error: Could not open input file!\n");
		exit(1);
	}

	/* First line of input file contains number of students and the number of homeworks*/
	fscanf(fpInput, "%d %d", pNumStudents, &NumHW);


	/* Allocate necessary memory to store student info */
	pStudents = (STUDENT *)malloc(sizeof(STUDENT) * *pNumStudents);

	if (pStudents == NULL)
	{
		fprintf(stderr, "Error: Out of memory!\n");
		exit(1);
	}

	/* Read information about students */
	for (x = 0; x < *pNumStudents; x++)
	{
		/* Input file lists names as first name followed by last name */
		fscanf(fpInput, "%s %s",
				pStudents[x].firstName,
				pStudents[x].lastName);

		/* Allocate necessary memory to store homework info for each student in each struct declaration*/
		pStudents[x].homeworks = malloc(sizeof(int)* NumHW);

		for (y = 0; y < NumHW; y++) /* Read homework scores */
			fscanf(fpInput, "%d", &pStudents[x].homeworks[y]);
		fscanf(fpInput, "%d", &pStudents[x].test); /* Read test score */

	}

	fclose(fpInput);

	return pStudents;
}

/*
 * Computes final average for each student.
 * Takes in input from user specifying the weight of the test grade(weightTest)
 * Calculates the average using (1-weightTest) for the homework
 * and weightTest for the test and sums up both values to find average
 */
void compute_averages(STUDENT arrS[], int numStudents)
{
	int x, y;
	int h_tot;
	float weightTest;


	do{
		printf("Enter the weight of the final test: ");
		scanf("%f", &weightTest);
	}while(weightTest>=1 || weightTest <=0);

	while ( getchar() != '\n' ); /*clears input buffer */

	for (x = 0; x < numStudents; x++)
	{
		h_tot = 0;
		for (y = 0; y < NumHW; y++)
			h_tot = h_tot + arrS[x].homeworks[y];

		arrS[x].final = ((1-weightTest) * h_tot / NumHW + weightTest * arrS[x].test); /* Calculates average using inputted weighting*/

		/* Following nested if-statement assigns letterGrade to each student depending on student's final grades*/
		if(arrS[x].final>= 90.0){
			arrS[x].letterGrade = 'A';
		}
		else{

			if(arrS[x].final>= 80.0 && arrS[x].final <90.0){
				arrS[x].letterGrade = 'B';
			}
			else{

				if(arrS[x].final>= 70.0 && arrS[x].final <80.0){
					arrS[x].letterGrade = 'C';
				}
				else{

					if(arrS[x].final>=60.0 && arrS[x].final <70.0){
						arrS[x].letterGrade ='D';
					}
					else{
						arrS[x].letterGrade ='F';
					}

				}

			}

		}

	}

	return;
}

/*
 * Use selection sort to sort students according to names
 * or grades depending on user's choice.
 */
void sort_students(STUDENT arrS[], int numStudents)
{
	int index1, index2, indexS;
	char preference;

	/*asks user preference for sort(name or grade)*/
	do{
		printf("Sort by last name(n) or grade(g): ");
		scanf("%c", &preference);
	}while(preference != 'g' && preference !='n');

	while ( getchar() != '\n' );/*clears input buffer*/

	if(preference == 'n'){
		/* Outder loop loops through all slots */
		for (index1 = 0; index1 < numStudents - 1; index1++)
		{
			indexS = index1;
			/* Inner loop finds the smallest element(name) starting at index1 */
			for (index2 = index1 + 1; index2 < numStudents; index2++)
				if ((strcmp(arrS[indexS].lastName, arrS[index2].lastName) > 0) ||
						((strcmp(arrS[indexS].lastName, arrS[index2].lastName) == 0) &&
								(strcmp(arrS[indexS].firstName, arrS[index2].firstName) > 0)))
					indexS = index2;

			/* Swap the smallest element(name) with the one at index1 if necessary */
			if (indexS != index1)
				swap_students(&arrS[index1], &arrS[indexS]);
		}

	}
	else{

		/* Outder loop loops through all slots */
		for (index1 = 0; index1 < numStudents - 1; index1++)
		{
			indexS = index1;
			/* Inner loop finds the largest element(grade) starting at index1 */
			for (index2 = index1 + 1; index2 < numStudents; index2++)
				if ((arrS[indexS].final < arrS[index2].final) ||
						((arrS[indexS].final == arrS[index2].final)
								&& (strcmp(arrS[indexS].lastName, arrS[index2].lastName) > 0)))
					indexS = index2;

			/* Swap the largest element(grade) with the one at index1 if necessary */
			if (indexS != index1)
				swap_students(&arrS[index1], &arrS[indexS]);
		}


	}
	return;
}

/* Exchanges the values of two students. */
void swap_students(STUDENT *pstud1, STUDENT *pstud2)
{
	STUDENT tmp;

	tmp = *pstud1;
	*pstud1 = *pstud2;
	*pstud2 = tmp;

	return;
}

/* Displays name and final average of each student. */
void display_students(STUDENT arrS[], int numStudents)
{
	int x;
	char filenameOutput[30];
	FILE *fpOutput;
	char grades[5]={0}; /* creates and initializes array with count of letterGrades to 0*/

	/* takes in the output file name*/
	printf("Enter name of output file: ");
	scanf("%s", filenameOutput);

	fpOutput = fopen(filenameOutput, "w");
	if (fpOutput == NULL)
	{
		fprintf(stderr, "Error: Could not open output file!\n");
		exit(1);
	}

	/* Loop through all students */
	for (x = 0; x < numStudents; x++){
		fprintf(fpOutput, "%s, %s %.1f %c\n",
				arrS[x].lastName, /* In output, dispay last name, first name, final grade and lettergrade for each student */
				arrS[x].firstName,
				arrS[x].final, arrS[x].letterGrade);

		/*switch statement that updates the counts in the array counting the letter grades */
		switch(arrS[x].letterGrade){

		case 'A': grades[0]++;
					break;
		case 'B': grades[1]++;
					break;
		case 'C': grades[2]++;
					break;
		case 'D': grades[3]++;
					break;
		case 'F': grades[4]++;
					break;
		default : printf("Error: Unknown letter grade");
					break;
		}

	}

	fprintf(fpOutput, "\n");


	/* prints out the count of letter grades on the output textfile */
	for(x =0; x<5; x++){
		if(x==4)
			fprintf(fpOutput,"Count of %c: %d\n", 'A'+x+1, grades[x]);
		else fprintf(fpOutput,"Count of %c: %d\n", 'A'+x, grades[x]);
	}

	fclose(fpOutput);

	return;
}
