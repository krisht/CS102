/*
 * Name			:	Palindromer.c
 * Author		:	Krishnan Thiyagarajan
 * Description	:	This program asks a user for an input and output file
 * 					and finds if the specified strings in the file after
 * 					the first line are palindromes. It displays the strings
 * 					in the original file and whether the string is a palindrome
 *					or not for each string in the output file.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Declares global file pointers to Output and Input */
FILE *fpOutput;
FILE *fpInput;

/*
 * Asks user for input of file with
 * test data set and sets it equal
 * to the fpInput pointer & asks
 * user for output file and sets
 * it equal to fpOutput pointer.
 *
 * @param void
 * @returns void
 */
void takeFiles(void){

	char inputFile[50];
	char outputFile[50];

	printf("Enter name of input file: ");
	scanf("%s", (char *)inputFile); /* reads entered text into the inputFile variable */

	if ((fpInput = fopen(inputFile, "r"))== NULL){/* opens the inputFile if available for reading */
		fprintf(stderr, "Error: Could not open input file!\n");
		exit(1);
	}

	printf("Enter name of the output file: ");
	scanf("%s", (char *)outputFile); /* reads entered text into the outFile variable */

	if ((fpOutput = fopen(outputFile, "w"))== NULL){/* opens outputFile for writing; if not available, function creates one */
		fprintf(stderr, "Error: Could not open output file!\n");
		exit(1);
	}

}


/*
 * Function that checks if a given
 * string is a palindrome or not.
 *
 * @param: char inputString[] -> a String
 * @return: int (0 for Not Palindrome & 1 for Palindrome)
 */
int checkPalindrome(char inputString[]){

	int fromLeft=0, fromRight=strlen(inputString)-1; /* finds the end of the string and assigns it to fromRight */

	for(fromLeft =0, fromRight=strlen(inputString)-1; fromLeft < fromRight;){ /* 2 part loop which runs from the left and right */

		while(isalpha(inputString[fromLeft])==0)/* if an element in the string is not an alaphabet, checking process continues from left to right */
			fromLeft++;

		while(isalpha(inputString[fromRight])==0) /* if an element in the string is not an alaphabet, checking process continues from right to left */
			fromRight--;

		if(tolower(inputString[fromLeft]) == tolower(inputString[fromRight])){ /* if letters matches, the checking process continues to the right from left and vice versa */
			fromLeft++;
			fromRight--;
		}
		else return 0; /* since letters do not match, returns 0 to indicate NOT A PALINDROME */

	}

	return 1; /* returns 1 to indicate that the string is a palindrome */

}

/*
 * Reads data and determines how many
 * lines to read. Starts from next line
 * and reads string into tempString
 * and uses checkPalindrome() function
 * to determine if tempString is a Palindrome.
 * Displays output on Standard Output.
 *
 * @param void
 * @returns void
 */
void readCheckPrint(void){

	int numLines, count;
	char tempString[50];

	fgets(tempString, sizeof(tempString), fpInput); /*reads first line indicating number of lines as a string */

	numLines = atoi(tempString); /*converts that string to a number*/

	for(count =0; count <numLines; count++){/*loops through all lines of the textfile one by one */

		fgets(tempString, sizeof(tempString), fpInput); /* reads each line */

		fprintf(fpOutput, "%s", tempString); /*prints out original line */

		if(checkPalindrome(tempString)==1) /* checks and displays whether above line is a palindrome or not */
			fprintf(fpOutput,"PALINDROME\n");
		else fprintf(fpOutput,"NOT A PALINDROME\n");

	}

}

/*
 * Runs program using above mentioned functions and *.h files
 *
 * @param void
 * @returns int indicating end of program
 */
int main(void){

	takeFiles();
	readCheckPrint();

	return 0;
}