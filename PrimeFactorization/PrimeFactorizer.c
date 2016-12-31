/*
 * Name        : PrimeFactorizer.c
 * Author      : Krishnan Thiyagarajan
 * Description : This program takes an input number
 *	 	 	   	 and outputs that number's prime
 *	 	 	   	 factorization.
 */

#include<stdio.h>
#include<math.h>
#define UPPER_LIMIT 1000000 /*declares upper limit for the possible inputs by user*/

int main(void){

	int userNum, count,x=0;	/*declares an integer userNum(inputed value from the user) and count for a for loop */

	for(x=0; x<10; x++){ /*starts a loop for the user until the user closes the window or stops the program */

		userNum = count=0; /*initializes userNum and count to 0*/

		/*
		 * The following do...while loop prompts the user repeatedly
		 * for an integer between 1 and the constant LASTNUM, inclusive,
		 * until the user inputs a proper integer
		 */

		do{
			printf("Enter a positive integer from 1 to %d: ",UPPER_LIMIT);
			scanf("%d", &userNum);
		}while(userNum <1 || userNum >UPPER_LIMIT);

		/*
		 * The following if statement checks whether the value
		 * the user entered is a "1" and if so, it prints "1"
		 * and if not it prints out the appropriate factorization
		 */

		if(userNum  == 1)
			printf("%d \n\n", 1);
		else{

			/*
			 * The following while loop repeatedly takes the number and checks whether it is an even number
			 * It prints the number of 2s that can divide userNum
			 */

			while(userNum % 2 ==0){
				if(userNum == 2){ /*checks whether count has reached the modified userNum to see if last factor as been reached*/
					userNum = userNum/ 2; /* uses integer division to reduce for loops limit and userNum */
					printf("%d \n\n", 2); /*prints the last factor and makes two new lines*/
				}
				else{
					userNum = userNum / 2; /* uses integer division to reduce for loops limit and userNum */
					printf("%d * ", 2); /*prints the number and the "*" sign if it is not the last factor*/
				}
			}

			/*
			 * This algorithm takes the given odd number and repeatedly modifies it
			 * in order to find the rest of the prime factorization.
			 * The for loop only needs to check until the square root of the modified number
			 * since prime factors repeat after the square root of a given number.
			 */


			for(count = 3; count<=userNum; count+=2){

				while(userNum % count  == 0){ /*checks whether the modified*/

					if(userNum == count){ /*checks whether count has reached the modified userNum to see if last factor as been reached*/
						userNum = userNum/ count;  /*uses integer division to reduce for loops limit and userNum*/
						printf("%d \n\n", count); /*prints the last factor and makes two new lines*/
					}
					else{
						userNum = userNum / count;  /*uses integer division to reduce for loops limit and userNum*/
						printf("%d * ", count); /*prints the number and the "*" sign if it is not the last factor*/
					}

				}

			}

		}
	}

	return 0; /*returns 0 to end the program(a.k.a. the main function) */
}