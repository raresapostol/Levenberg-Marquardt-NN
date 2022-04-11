#include "nnLibSettings.h"

int main(void) {
	phiNNParameters nn;

	nn.inOutFileName = _strdup("nnInputOutputFile.txt");

	nn.inOutReadFileFromText();

	nn.inOutWriteDataSetMatrices();

	printf("\nPress enter to start LM!\n");
	getchar();

	// randomize the whole process!!
	srand((unsigned int)time(NULL));

	nn.phiNNPhiInitializeNeuralNetwork(3, 4, 1);

	nn.phiNNPhiTrainingParametersSettings(1e-9, 100000, 1e200, 1e-12);

	nn.phiNNPhiTrainingNeuralNetworkWithLM();

	printf("%lf ", nn.phiNNErrorNowValue);

	nn.phiNNWriteCoefficientMatrices();

	printf("Press enter to exit!\n");
	getchar();

	nn.inOutPhiExitInOut();

	nn.phiNNPhiExitNNLib();

	return 0;
}