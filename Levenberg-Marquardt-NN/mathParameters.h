#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#ifdef __cplusplus
}
#endif

#include "inOutParameters.h"

class mathParameters : public inOutParameters {
private:
protected:
public:

	mathParameters() {
	}

	~mathParameters() {
	}

	/*
	 * creating dynamically matrices produced by multiplication
	 * output -> address of multiplied matrices
	 * input  -> address of first Matrices
	 *           address of second Matrices
	 *           row of first Matrices
	 *           col of first Matrices
	 *           row of second Matrices
	 *           col of second Matrices
	*/
	double** phiMathPhiVectorMatrixMultiplication(double** firstTerm,
		double** SecondTerm,
		int row1,
		int col1,
		int row2,
		int col2) {
		double** pd = this->inOutCreatingEmptyMatrices(row1, col2);
		double sum = 0;

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < row1; i++) { //row of first matrix
			for (int j = 0; j < col2; j++) { //column of second matrix
				sum = 0;
				for (int k = 0; k < col1; k++)
					sum = sum + firstTerm[i][k] * SecondTerm[k][j];
				pd[i][j] = sum;
			}
		}
		return pd;
	}

	/*
	 * creating dynamically matrices produced by skalar multiplication
	 * output -> address of multiplied matrices
	 * input  -> value of skalar term
	 *           address of second Matrices
	 *           row of second Matrices
	 *           col of second Matrices
	*/
	double** phiMathPhiSkalarMatrixMultiplication(double skalarTerm,
		double** SecondTerm,
		int row,
		int col) {
		double** pd = this->inOutCreatingEmptyMatrices(row, col);

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				pd[i][j] = skalarTerm * SecondTerm[i][j];
		}

		return pd;
	}

	/*
	 * creating dynamically matrices produced by summation
	 * output -> address of summed matrices
	 * input  -> address of first Matrices
	 *           address of second Matrices
	 *           row of second Matrices
	 *           col of second Matrices
	*/
	double** phiMathPhiMatrixSummation(double** firstTerm,
		double** SecondTerm,
		int row,
		int col) {
		double** pd = this->inOutCreatingEmptyMatrices(row, col);

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				pd[i][j] = firstTerm[i][j] + SecondTerm[i][j];
		}

		return pd;
	}

	/*
	 * creating dynamically matrices resulting with determinant
	 * output -> address of summed matrices
	 * input  -> address of first Matrices
	 *           row of second Matrices
	 *           col of second Matrices
	*/
	double phiMathPhiDeterminationCalculation(double** phiMatrices,
		int row,
		int col) {
		double phiDet = 1.0; // Initialize result
		double ratio = 0.0;

		/* Conversion of matrix to upper triangular */
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < row; j++) {
				if (j > i) {
					ratio = phiMatrices[j][i] / phiMatrices[i][i];
					for (int k = 0; k < row; k++) {
						phiMatrices[j][k] -= ratio * phiMatrices[i][k];
					}
				}
			}
		}

		for (int i = 0; i < row; i++) {
			phiDet *= phiMatrices[i][i];
		}
		printf("The determinant of matrix is: %e\n\n", phiDet);

		return phiDet;
	}

	/*
	 * creating inverse matrices of phiMatrices
	 * output -> address of summed matrices
	 * input  -> address of first Matrices
	 *           value of row
	 *           value of col
	 *           address of transpose matrices
	*/
	void phiMathPhiTranspose(double** phiMatrices, int row, int col, double** phiTransMatrices) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				phiTransMatrices[j][i] = phiMatrices[i][j];
			}
		}
	}

	/*
	 * creating dynamically matrices to equalize these terms
	 * output -> address of summed matrices
	 * input  -> address of first Matrices
	 *           address of second Matrices
	 *           row of second Matrices
	 *           col of second Matrices
	*/
	void phiMathPhiMatrixAssignment(double** assignedTerm,
		double** SecondTerm,
		int row,
		int col) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				assignedTerm[i][j] = SecondTerm[i][j];
			}
		}
	}

	/*
	 * generating random number in float number for a given min/max
	 * output -> value of float number
	 * input  -> value of min value
	 *           value of max value
	*/
	double phiMathPhiRand(double min, double max) {
		double scale = rand() / (double)RAND_MAX; /* [0, 1.0] */
		return min + scale * (max - min);         /* [min, max] */
	}

	/*
	 * summation value of matrices
	 * output -> value of sum number
	 * input  -> address of matrices
	 *           value of row
	 *           value of column
	*/
	double phiMathPhiSumMatrices(double** pd, int row, int col) {
		double sumValue = 0.0;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				sumValue = sumValue + pd[i][j];
			}
		}

		return sumValue;
	}

	/*
	 * mean value of matrices
	 * output -> value of sum number
	 * input  -> address of matrices
	 *           value of row
	 *           value of column
	*/
	double phiMathPhiMeanMatrices(double** pd, int row, int col) {
		double sumValue = 0.0;
		int counter = 0;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				counter++;
				sumValue = sumValue + pd[i][j];
			}
		}

		return sumValue / (double)counter;
	}

	/*
	 * creating eyematrices for a given row value
	 * output -> address of this vector
	 * input -> value of row
	*/
	double** phiMathPhiEyeCreationMatrices(int row) {
		double** pd = this->inOutCreatingEmptyMatrices(row, row);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < row; j++) {
				if (i == j) {
					pd[i][j] = 1;
				}
				else {
					pd[i][j] = 0;
				}
			}
		}

		return pd;
	}

	/*
	 * creating inverse matrices of phiMatrices
	 * output -> address inverseMatrices
	 * input  -> address of first Matrices
	 *           value of row
	 *           value of col
	*/
	double** phiMathPhiInverseMatrices(double** phiMatrices, int row, int col)
	{
		 // dynamic memory allocation

		 // inverse Matrice
		double** inv = this->inOutCreatingEmptyMatrices(row, 2 * col);
		double** realInv = inOutCreatingEmptyMatrices(row, col);

		this->phiMathPhiMatrixAssignment(inv, phiMatrices, row, col);

		realInv = this->phiMathInverseOfMatrix(inv, row);

		// control for realInv matrices
		/*
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (realInv[i][j] > 1e50)
				{
					realInv[i][j] = 1e50;
				}
				else
				{
					if (realInv[i][j] < -1e50)
					{
						realInv[i][j] = -1e50;
					}
				}
			}
		}*/

		this->inOutPhiFree(inv, row, 2 * col);

		return realInv;
	}

	void phiMathPrintMatrix(double** ar, int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				printf("%e ", ar[i][j]);
			}
			printf("\n");
		}
		return;
	}

	void phiMathPrintInverse(double** ar, int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = n; j < m; j++)
			{
				printf("%e ", ar[i][j]);
			}
			printf("\n");
		}
		return;
	}

	double** phiMathInverseOfMatrix(double** matrix, int order)
	{
		// Matrix Declaration.

		double temp;

		// PrintMatrix function to print the element
		// of the matrix.
		//printf("=== Matrix ===\n");
		//PrintMatrix(matrix, order, order);

		// Create the augmented matrix
		// Add the identity matrix
		// of order at the end of original matrix.
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < 2 * order; j++)
			{
				// Add '1' at the diagonal places of
				// the matrix to create a identity matirx
				if (j == (i + order))
				{
					matrix[i][j] = 1;
				}
			}
		}

		// Interchange the row of matrix,
		// interchanging of row will start from the last row
		for (int i = order - 1; i > 0; i--)
		{
			// Swapping each and every element of the two rows
			// if (matrix[i - 1][0] < matrix[i][0])
			// for (int j = 0; j < 2 * order; j++) {
			//
			//	 // Swapping of the row, if above
			//	 // condition satisfied.
			// temp = matrix[i][j];
			// matrix[i][j] = matrix[i - 1][j];
			// matrix[i - 1][j] = temp;
			// }

			// Directly swapping the rows using pointers saves
			// time

			if (matrix[i - 1][0] < matrix[i][0])
			{
				double* temp = matrix[i];
				matrix[i] = matrix[i - 1];
				matrix[i - 1] = temp;
			}
		}

		// Print matrix after interchange operations.
		//printf("\n=== Augmented Matrix ===\n");
		//PrintMatrix(matrix, order, order * 2);

		// Replace a row by sum of itself and a
		// constant multiple of another row of the matrix
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < order; j++)
			{
				if (j != i)
				{
					if (matrix[i][i] == 0)
					{
						//matrix[i][i] = 1;
						temp = 1e-100;
					}
					else
					{
						temp = matrix[j][i] / matrix[i][i];
					}

					for (int k = 0; k < 2 * order; k++)
					{
						matrix[j][k] -= matrix[i][k] * temp;
					}
				}
			}
		}

		// Multiply each row by a nonzero integer.
		// Divide row element by the diagonal element
		for (int i = 0; i < order; i++)
		{
			temp = matrix[i][i];
			for (int j = 0; j < 2 * order; j++)
			{
				matrix[i][j] = matrix[i][j] / temp;
			}
		}

		double** pdInv = this->inOutCreatingEmptyMatrices(order, order);

		for (int i = 0; i < order; i++)
		{
			for (int j = order; j < 2 * order; j++)
			{
				pdInv[i][j - order] = matrix[i][j];
			}
		}

		//PrintInverse(matrix, order, 2 * order);

		return pdInv;
	}
};
