/*
 * This program reads student information from a specified text file.
 * Each student has an associated first and last name, four homework
 * scores, and one test score. The program computes the weighted
 * average score for each student, and sorts the data based on names.
 * The updated information is written to a specified text file.
 * Written by: Carl Sable
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM_HW 4

struct student
{
  char lastName[30];  /* last name */
  char firstName[30]; /* first name */
  int homeworks[NUM_HW];  /* scores on homeworks */
  int test;  /* score on test */
  float final;  /* final average */
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

/* Read all student data from a specified text file */
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

  /* First line of input file contains number of students */
  fscanf(fpInput, "%d", pNumStudents);

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
    for (y = 0; y < NUM_HW; y++) /* Read homework scores */
      fscanf(fpInput, "%d", &pStudents[x].homeworks[y]);
    fscanf(fpInput, "%d", &pStudents[x].test); /* Read test score */
  }

  fclose(fpInput);

  return pStudents;
}

/*
 * Computes final average for each student.
 * Assumes homework is worth 60% (in total) and test is worth 40%.
 */
void compute_averages(STUDENT arrS[], int numStudents)
{
  int x, y;
  int h_tot;

  for (x = 0; x < numStudents; x++)
  {
    h_tot = 0;
    for (y = 0; y < NUM_HW; y++)
      h_tot = h_tot + arrS[x].homeworks[y];
		
    arrS[x].final = (0.6 * h_tot / NUM_HW + 0.4 * arrS[x].test);
  }

  return;
}

/* Use selection sort to sort students according to names. */
void sort_students(STUDENT arrS[], int numStudents)
{
  int index1, index2, indexS;

  /* Outder loop loops through all slots */
  for (index1 = 0; index1 < numStudents - 1; index1++)
  {
    indexS = index1;
    /* Inner loop finds the smallest element starting at index1 */
    for (index2 = index1 + 1; index2 < numStudents; index2++)
      if ((strcmp(arrS[indexS].lastName, arrS[index2].lastName) > 0) ||
	  ((strcmp(arrS[indexS].lastName, arrS[index2].lastName) == 0) &&
	   (strcmp(arrS[indexS].firstName, arrS[index2].firstName) > 0)))
	indexS = index2;

    /* Swap the smallest element with the one at index1 if necessary */
    if (indexS != index1)
      swap_students(&arrS[index1], &arrS[indexS]);
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

  printf("Enter name of output file: ");
  scanf("%s", filenameOutput);

  fpOutput = fopen(filenameOutput, "w");
  if (fpOutput == NULL)
  {
    fprintf(stderr, "Error: Could not open output file!\n");
    exit(1);
  }

  /* Loop through all students */
  for (x = 0; x < numStudents; x++)
    fprintf(fpOutput, "%s, %s %.1f\n",
	    arrS[x].lastName, /* In output, dispay last name first */
	    arrS[x].firstName,
	    arrS[x].final);

  fclose(fpOutput);

  return;
}
