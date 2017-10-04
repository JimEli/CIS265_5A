/*************************************************************************
* Title: (CIS265_5A) 5x5 Array Row & Column Adder.
* File: main.c
* Author: James Eli
* Date: 9/2/2017
*
* Write a program that reads a 5 x 5 array of integers and the prints the 
* row sums and the column sums:
*   Enter row 1: 8 3 9 0 10
*   Enter row 2: 3 5 17 1 1
*   Enter row 3: 2 8 6 23 1
*   Enter row 4: 15 7 3 2 9
*   Enter row 5: 6 14 2 6 0 
*   Row totals: 30 27 40 36 28
*   Column totals: 34 37 37 32 21
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*  (2) Row entry numbers are delimited by the non-digit characters.
*  (3) No attempt is made to validate the integer input.
*  (4) MS version uses secure strtok_s.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/02/2017: Initial release. JME
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ROWS    3    // 5 works but 3 is used for a simple demonstration.
#define COLUMNS ROWS // Must be a square 2D array.
#define TOTAL   (ROWS*COLUMNS)

// Recursive sum of row values.
int sumRow(const int *a, int i) {
	return (i -= 1) ? sumRow(a, i) + *(a + i) : *(a + i);
}

// Recursive sum of column values.
int sumColumn(const int *a, const int column, int i) {
	return (i -= COLUMNS) ? sumColumn(a, column, i) + *(a + column + i) : *(a + column + i);
}

int main(void) {
	int *a = (int[TOTAL]) { 0 }, i = 0, c;

	printf("Enter %d integers: ", TOTAL);
	while ((c = getchar()) != '\n' && i < TOTAL) {
		if (isdigit(c))
			 *(a + i) = *(a + i) * 10 + (c - '0');
		else
			i++;
	}

	if (++i != TOTAL) {
		printf("%d integers entered, %d are needed!\n", i, TOTAL);
		return 1;
	}

#ifndef NDEBUG
	for (i = 0; i < TOTAL; printf("%d\n", *(a + i++)));
#endif

	for (i = 0; i < ROWS; i++) {
		printf("Row #%d sum = %d\n", i + 1, sumRow(a + i*COLUMNS, COLUMNS));
		printf("Column #%d sum = %d\n", i + 1, sumColumn(a, i, TOTAL));
	}

	getchar();
}
