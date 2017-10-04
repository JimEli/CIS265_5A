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
*  (2) Row entry numbers are delimited by the space character.
*  (3) No attempt is made to validate the integer input. The atoi()
*      function handles the under/overflow.
*  (4) MS version uses secure strtok_s.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/02/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definitions.
#define ROWS               5  // Number of rows in array.
#define COLUMNS            5  // Number of columns in array.
#define MAX_CHARS          36 // (7 chars per x 5) + 1

// Attempt to get an input of 5 integers from user. Return true if successful.
bool getRow(const unsigned int rowNum, int row[]) {
	int count = 0;       // Count of elements in row.
	bool retVal = false; // Function return value, ture = success (assumed false).

	assert(row != NULL);
	assert((rowNum > 0) && (rowNum <= ROWS));

	// Reserve temporary space for the input string.
	char *s = (char *)malloc(sizeof(char) * MAX_CHARS);
	// Check valid.
	if (s == NULL)
		return retVal;

	// Prompt and grab input.
	fprintf(stdout, "Enter row %d: ", rowNum);
	if (!fgets(s, MAX_CHARS, stdin)) {
		free(s);
		return retVal;
	}
	else if (!strchr(s, '\n')) {
		// input too long, eat it.
		while (fgets(s, MAX_CHARS, stdin) && !strchr(s, '\n'));
		fputs("Too many characters input.\n", stdout);
	}
	else if (strlen(s) > 1) {
		// Iterate string and convert to integer.
		char *context = NULL;
		char *delimiters = " ,/|-:\n";
		//char *number = strtok_s(s, " \n", &context);
		char *number = strtok_s(s, delimiters, &context);
		while (number != NULL) {
			row[count++] = atoi(number);
			number = strtok_s(NULL, delimiters, &context);
		}

		// Confirm correct number of integers.
		if (count > ROWS)
			fputs("Too many numbers entered for this row.\n", stdout);
		else if (count < ROWS)
			fputs("Too few numbers entered for this row.\n", stdout);
		else
			retVal = true; // Success.
	}

	// Free memory and return.
	free(s);
	return retVal;
}

// Sum a row of 2d array.
int sumRow(const int row[], const size_t n) {
	int sum = 0;
	
	assert(n == ROWS);

	// Itereate row, summing values.
	for (int i = 0; i < (int)n; i++)
		sum += row[i];
	return sum;
}

// Sum column of 2d array.
int sumColumn(const int array[ROWS][COLUMNS], const int column, const size_t n) {
	int sum = 0;

	assert((n == ROWS*COLUMNS) && (column >= 0) && (column < COLUMNS));

	// Iterate column, summing values.
	for (int i = 0; i < (int)n/ROWS; i++)
		sum += array[i][column];
	return sum;
}

// Program starts here.
int main(void) {
	int matrix[ROWS][COLUMNS];

	// Display program instructions.
	fputs("Enter 5 rows of 5 integers. Separate the integers by the space character.\n", stdout);

	// Enter 5 rows of 5 columns.
	for (int r = 0; r < ROWS; r++) {
		if (getRow(r + 1, matrix[r]) == false) {
			// We are highly intolerant of input error...
			fputs("Program terminating.\n", stderr);
			exit(EXIT_FAILURE);
		}
	}

	// Total and display rows and columns.
	fputs("Row totals: ", stdout);
	for (int i = 0; i < ROWS; i++)
		printf("%d ", sumRow(matrix[i], sizeof(matrix[i]) / sizeof(matrix[i][0])));

	fputs("\nColumn totals: ", stdout);
	for (int i = 0; i < COLUMNS; i++)
		printf("%d ", sumColumn(matrix, i, sizeof(matrix) / sizeof(int)));

	fputs("\n", stdout);
}
