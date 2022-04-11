#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

	// standard library usage
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#ifdef __cplusplus
}
#endif

#define ALLOCATION_ERROR 1
#define INCONSISTENT_ROW_COLUMN 2
#define FILE_OPEN_ERROR 3
#define SAMPLING_RATE_ERROR 4

class inOutParameters {
private:
protected:
public:
	/*
	 * creating an inputfile to read the file
	*/
	FILE* inOutInputFile;
	char* inOutFileName;  /*
						  * storing the name of file
						  */

	int inOutLengthNNDataset; /*
						   * row value of NN dataset
						   */

	int inOutNumberNNInputDataset;  /*
								   * column value of input NN dataset
								   */
	int inOutNumberNNOutputDataset; /*
								   * column value of output NN dataset
								   */

								   // input file information
								   ////////////////////////////////////////////////////////////
								   ////////////////////////////////////////////////////////////

								   ////////////////////////////////////////////////////////////
								   ////////////////////////////////////////////////////////////
								   // storing the whole elements in one pointer

	double** inOutInputDataArray; /*
								 * storing the whole input elements in one dynamic array
								 */

	double** inOutOutputDataArray; /*
								 * storing the whole output elements in one dynamic array
								 */

								 // storing the whole elements in one pointer
								 ////////////////////////////////////////////////////////////
								 ////////////////////////////////////////////////////////////

								 ////////////////////////////////////////////////////////////
								 ////////////////////////////////////////////////////////////
								 // CONSTRUCTOR

	inOutParameters() {
		this->inOutInputFile = NULL;

		this->inOutFileName = NULL;

		this->inOutLengthNNDataset = 0;

		this->inOutNumberNNInputDataset = 0;
		this->inOutNumberNNOutputDataset = 0;

		this->inOutInputDataArray = NULL;

		this->inOutOutputDataArray = NULL;
	}

	inOutParameters(char* fileName) {
		this->inOutInputFile = NULL;

		this->inOutFileName = fileName;

		this->inOutLengthNNDataset = 0;

		this->inOutNumberNNInputDataset = 0;
		this->inOutNumberNNOutputDataset = 0;

		this->inOutInputDataArray = NULL;

		this->inOutOutputDataArray = NULL;
	}

	~inOutParameters() {
	}

	/*
	 * simple test code to laod the whole library to the project
	 * output -> returns nothing
	 * input -> taking nothing
	*/

	void inOutPrintPhi() {
		printf("\n\n Libraries are loaded to the project!\n");
		printf("Process is started...\n\n");
		//Sleep(5);
	}

	/*
	 * reading the whole data for a given text file
	 * output -> returns nothing
	 * input -> taking nothing
	*/
	void inOutReadFileFromText() {
		this->inOutInputFile = fopen(this->inOutFileName, "r");

		if (this->inOutInputFile == NULL) {
			printf("Text file is not opened!\n");
			exit(EXIT_FAILURE);
		}

		double emptyReading1, emptyReading2, emptyReading3;
		double emptyReading;
		double fillReading;

		char endOfFileControl = 0;

		int varTextInfo = 0;
		int rowCounter = 0;

		while (endOfFileControl != EOF) {
			if (varTextInfo == 0) {
				varTextInfo = 1;
				fscanf(this->inOutInputFile, "%lf %lf %lf", &emptyReading1,
					&emptyReading2,
					&emptyReading3);

				printf("Row %d Input Column %d Output Column %d\n", (int)emptyReading1,
					(int)emptyReading2,
					(int)emptyReading3);

				this->inOutLengthNNDataset = (int)emptyReading1;
				this->inOutNumberNNInputDataset = (int)emptyReading2;
				this->inOutNumberNNOutputDataset = (int)emptyReading3;

				for (int j = 0; j < (this->inOutNumberNNOutputDataset + this->inOutNumberNNInputDataset - 3); j++)
					fscanf(this->inOutInputFile, "%lf", &emptyReading);

				this->inOutFillInputAndOutputMatrices();

				endOfFileControl = getc(this->inOutInputFile);
			}
			else {
				if (rowCounter < this->inOutLengthNNDataset) {
					for (int j = 0; j < this->inOutNumberNNInputDataset; j++) {
						fscanf(this->inOutInputFile, "%lf ", &fillReading);
						this->inOutInputDataArray[j][rowCounter] = fillReading;
					}

					for (int j = 0; j < this->inOutNumberNNOutputDataset; j++) {
						fscanf(this->inOutInputFile, "%lf", &fillReading);
						this->inOutOutputDataArray[j][rowCounter] = fillReading;
					}
				}

				rowCounter++;
				endOfFileControl = getc(this->inOutInputFile);
			}
		}

		fclose(this->inOutInputFile);
	}

	/*
	 * reading the whole data for a given CSV file
	 * output -> returns nothing
	 * input -> address of InOutparameters structure
	*/
	void inOutReadFileFromCSV() {
		this->inOutInputFile = fopen(this->inOutFileName, "r");

		if (this->inOutInputFile == NULL) {
			printf("CSV file is not opened!\n");
			exit(EXIT_FAILURE);
		}

		double emptyReading1, emptyReading2, emptyReading3;
		double emptyReading;
		double fillReading;

		char endOfFileControl = 0;

		int varTextInfo = 0;
		int rowCounter = 0;

		while (endOfFileControl != EOF) {
			if (varTextInfo == 0) {
				varTextInfo = 1;
				fscanf(this->inOutInputFile, "%lf,%lf,%lf,", &emptyReading1,
					&emptyReading2,
					&emptyReading3);

				printf("Row %d Input Column %d Output Column %d\n", (int)emptyReading1,
					(int)emptyReading2,
					(int)emptyReading3);

				this->inOutLengthNNDataset = (int)emptyReading1;
				this->inOutNumberNNInputDataset = (int)emptyReading2;
				this->inOutNumberNNOutputDataset = (int)emptyReading3;

				for (int j = 0; j < (this->inOutNumberNNOutputDataset + this->inOutNumberNNInputDataset - 3); j++)
					fscanf(this->inOutInputFile, "%lf,", &emptyReading);

				this->inOutFillInputAndOutputMatrices();

				endOfFileControl = getc(this->inOutInputFile);
			}
			else {
				if (rowCounter < this->inOutLengthNNDataset) {
					for (int j = 0; j < this->inOutNumberNNInputDataset; j++) {
						fscanf(this->inOutInputFile, "%lf,", &fillReading);
						this->inOutInputDataArray[j][rowCounter] = fillReading;
					}

					for (int j = 0; j < this->inOutNumberNNOutputDataset; j++) {
						fscanf(this->inOutInputFile, "%lf,", &fillReading);
						this->inOutOutputDataArray[j][rowCounter] = fillReading;
					}
				}

				rowCounter++;
				endOfFileControl = getc(this->inOutInputFile);
			}
		}

		fclose(this->inOutInputFile);
	}

	/*
	 * creating dynamically empty input matrices for data storage
	 * output -> address of matrices (float **)
	 * input  -> address of phinioutparameters
	*/
	double** inOutCreatingEmptyInputMatrices() {
		double** pd = (double**)malloc(this->inOutNumberNNInputDataset * sizeof(double*));

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < this->inOutNumberNNInputDataset; i++)
			pd[i] = (double*)malloc(this->inOutLengthNNDataset * sizeof(double));

		return pd;
	}

	/*
	 * creating dynamically empty output matrices for data storage
	 * output -> address of matrices (float **)
	 * input  -> taking nothing
	*/
	double** inOutCreatingEmptyOutputMatrices() {
		double** pd = (double**)malloc(this->inOutNumberNNOutputDataset * sizeof(double*));

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < this->inOutNumberNNOutputDataset; i++)
			pd[i] = (double*)malloc(this->inOutLengthNNDataset * sizeof(double));

		return pd;
	}

	/*
	 * creating dynamically empty matrices for general usage
	 * output -> address of empty matrices
	 * input  -> rows and columns values of matrices
	 */
	double** inOutCreatingEmptyMatrices(int rows, int cols) {
		double** pd = (double**)malloc(rows * sizeof(double*));

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < rows; i++)
			pd[i] = (double*)malloc(cols * sizeof(double));

		// initialize the matrices
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				pd[i][j] = 0.0;
			}
		}

		return pd;
	}

	/*
	 * creating dynamically empty matrices for general usage
	 * output -> address of empty matrices
	 * input  -> rows and columns values of matrices
	*/
	int** inOutCreatingEmptyMatricesIntegralType(int rows, int cols) {
		int** pd = (int**)malloc(rows * sizeof(int*));

		if (pd == NULL) {
			this->inOutPhiErrorHandler(ALLOCATION_ERROR);
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < rows; i++)
			pd[i] = (int*)malloc(cols * sizeof(int));

		// initialize the matrices
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				pd[i][j] = 0;
			}
		}

		return pd;
	}

	/*
	 * filling the whole data to the matrices
	 * output -> returns nothing
	 * input  -> taking nothing
	*/
	void inOutFillInputAndOutputMatrices() {
		this->inOutInputDataArray = this->inOutCreatingEmptyInputMatrices();
		this->inOutOutputDataArray = this->inOutCreatingEmptyOutputMatrices();
	}

	/*
	 * writing the whole data to the matrices
	 * output -> returns nothing
	 * input  -> taking nothing
	*/
	void inOutWriteDataSetMatrices() {
		printf("Printing dataset...\n");

		printf("In1 In2 In3 Out1\n");

		for (int i = 0; i < this->inOutLengthNNDataset; i++) {
			for (int j = 0; j < this->inOutNumberNNInputDataset; j++) {
				printf("%lf ", this->inOutInputDataArray[j][i]);
			}

			for (int j = 0; j < this->inOutNumberNNOutputDataset; j++) {
				printf("%lf ", this->inOutOutputDataArray[j][i]);
			}

			printf("\n");
		}
	}

	/*
	 * free the whole memory allocation
	 * output -> return nothing
	 * input  -> address of memory
	 *           row value of matrices
	 *           column value of matrices
	 */
	void inOutPhiFree(double** pd, int row, int col) {
		for (int i = 0; i < row; i++)
			free(pd[i]);

		free(pd);
	}

	/*
	 * free the whole memory allocation
	 * output -> return nothing
	 * input  -> address of memory
	 *           row value of matrices
	 *           column value of matrices
	*/
	void inOutPhiFreeIntegralType(int** pd, int row, int col) {
		for (int i = 0; i < row; i++)
			free(pd[i]);

		free(pd);
	}

	/*
	 * exiting the whole variables and functions
	 * output -> returns nothing
	 * input -> address of ptrInOut
	 */
	void inOutPhiExitInOut() {
		this->inOutPhiFree(this->inOutInputDataArray, this->inOutNumberNNInputDataset, this->inOutLengthNNDataset);
		this->inOutPhiFree(this->inOutOutputDataArray, this->inOutNumberNNOutputDataset, this->inOutLengthNNDataset);
	}

	/*
	 * notifying the error result
	 * output -> return nothing
	 * input  -> type of error
	*/
	void inOutPhiErrorHandler(int errorType) {
		switch (errorType)
		{
		case FILE_OPEN_ERROR:
			printf("System Dynamic Parameter files cannot be created!\n");
			break;
		case INCONSISTENT_ROW_COLUMN:
			printf("The rows and columns are not consistent!\n");
			break;
		case ALLOCATION_ERROR:
			printf("Memory allocation cannot be done!\n");
			break;
		case SAMPLING_RATE_ERROR:
			printf("Sampling period cannot be assigned to either negative or zero value!\n");
			break;

		default:
			break;
		}
	}
};

//typedef inOutParameters* phiInOutParameterPtr;
