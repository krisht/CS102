/* Name        : GradesBook.c
 * Author      : Krishnan Thiyagarajan
 * Description : This program takes in a number of "grades"(Integers)
 *			     and outputs the class averages for each student
 *               the depending on the defined constant NUM_STUDENTS
 *				 and NUM_GRADES.
 */
#include<stdio.h>		/* adds functions from stdio.h to this program*/
#define NUM_STUDENTS 15 /*defines the number of students per class*/
#define NUM_GRADES  5 /*defines the number of grades per student*/

int gradeBook[NUM_STUDENTS][NUM_GRADES]; /*declares a 2D array to store grades. Columns: individual assignments; Rows: Individual students*/

/*
 * Reads in values from standard input into the
 * global 2D array.
 *
 * @param void : This function does not take in any parameters
 * @reurns void: This function returns nothing. It only changes the global array, gradeBook
 */

void readValues(void){

	int countRows, countCols; /* declares counter variables for rows and colums */

 	/*
 	 * for-loop for rows 0 to (NUM_STUDENTS-1) and columns 0 to (NUM_GRADES-1)
 	 * since NUM_STUDENTS is the # of rows and NUM_GRADES is the # of columns
 	 * to read in grades using the standard input and output function scanf
 	 */

	for(countRows = 0; countRows<NUM_STUDENTS; countRows++){
			for( countCols=0; countCols<NUM_GRADES; countCols++){
				scanf("%d",&gradeBook[countRows][countCols]);
			}
	}

}

/*
 * Writes out table headers for each column using printf() from stdio.h
 * Declares variables countRows, countCols, array of double containing
 * the weighting for each assignment, and a double, average, initialized
 * to zero. It continues to print the headers for each column. Then it
 * continues to go through the global array and prints out (1) the student
 * number, (2) the student's assignment grades and (3) the computed weighted
 * average using the assignment grades of the student and the weightOfGrades
 * grade weighting. All are displayed with a formatted width of 8, and the
 * average has a precision of 2.
 *
 * @param void : This function does not take in any parameters
 * @reurns void: This function returns nothing. Computes averages for students
 * 				 and displays table of values including STUD #, grades for
 *				 programs and exam, and student's average in the class.
 */
void dispGradeBook(void){

	int countRows, countCols;/* declares counter to loop through each Row of the array */
	float weightOfGrades[] = {.10, .15, .15, .20, .40};/*declares the weight of grades of each assignment in an array*/
	double average =0.0;

	printf("%8s%8s%8s%8s%8s%8s%8s\n", "STUD #","PROG #1", "PROG #2",
				"PROG #3", "PROG #4","EXAM", "AVERAGE"); /* prints out the headers for each column */

	for(countRows=0; countRows<NUM_STUDENTS; countRows++){/* loops through values from 0 to 14(i.e. final index of array) */

		average = 0; /* initializes the integer variable to zero in order to start to calculate the average from zero*/
		printf("%8d",countRows+1); /* prints formatted student number for each row */

		for(countCols=0; countCols<NUM_GRADES; countCols++){

			printf("%8d", gradeBook[countRows][countCols]); /* prints out grade for the current assignment for the "countRow"th student in the array */

			average+=(weightOfGrades[countCols]* gradeBook[countRows][countCols]); /* computes the current assignments part of the average grade
																					  using weighting from the array weightOfGrades */

		}

		printf("%8.2f\n", average); /* prints out the average for each row formatted to two decimal places and a width of 8 */

	}

}

/*
 * Runs the entire program in using the above mentioned functions
 *
 *@param void: The main function doesn't take in any parameters
 *@returns int: The main function returns an integer to indicate whether the program ran smoothly
 */
int main(void){

	readValues(); /* Calls function readValues from above */

	dispGradeBook(); /* Calls function dispGradeBook from above */

	return 0; /* returns 0 to indicate that program ran smoothly and has ended */
}









