#include <stdio.h>
void addPadding(double inputArr[], int inputArraySize, double outputArr[], 
	int* outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main(){
	double inputArr[] = {5, 6, 7, 8, 9};
	double outputArr[255];
	int outputArraySize = 0;
	addPadding(inputArr, 5 , outputArr, &outputArraySize, 4, halfPadding);

	return 0;
}

void addPadding(double inputArr[], int inputArraySize, double outputArr[], 
	int* outputArraySize, int paddingWidth, void paddingMethod(double[], int, int)){
	int i,k = inputArraySize;
	*outputArraySize = inputArraySize + 2*paddingWidth;
	
	
	for(i = k-1; i >= 0 ; i--){
		outputArr[i + paddingWidth] = inputArr[i];
	}
	paddingMethod(outputArr, *outputArraySize, paddingWidth);

}



void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,k,j;

	for(i = 0; i < paddingWidth - 1; i++){
		outputArr[i] = 0;
	}
	for(k = outputArraySize - paddingWidth -1 ; k < outputArraySize;k++){
		outputArr[i] = 0;
	}
	for (j = 0; j < outputArraySize; j++){
		printf("%.2f ", outputArr[j]);
	}

}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j,k;
	for(i = 0; i < paddingWidth; i++)
		outputArr[i] = outputArr[paddingWidth];	
	for(j = outputArraySize - paddingWidth ; j < outputArraySize; j++)
		outputArr[j] = outputArr[outputArraySize - paddingWidth - 1];
	for (k = 0; k < outputArraySize; k++){
		printf("%.2f ", outputArr[k]);
	}
}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j,k;
	for(i = 0; i < paddingWidth; i++)
		outputArr[i] = outputArr[paddingWidth]/2;	
	for(j = outputArraySize - paddingWidth ; j < outputArraySize; j++)
		outputArr[j] = outputArr[outputArraySize - paddingWidth - 1]/2;
	for (k = 0; k < outputArraySize; k++){
		printf("%.2f ", outputArr[k]);
	}
}

