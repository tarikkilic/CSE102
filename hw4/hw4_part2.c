#include <stdio.h>
typedef enum _paddingType { ZERO, HALF, SAME} PaddingType;
int convolution(double inputArr[], int inputArraySize, double kernelArr[], int
kernelArraySize, double outputArr[], int* outputArraySize, int stride, PaddingType
padding);
void addPadding(double inputArr[], int inputArraySize, double outputArr[], 
	int* outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);



int main(){
	double inputArr[] = {1, 3, 5, 7, 9};
	double kernelArr[] = {2};
	double outputArr[255];
	int outputArrSize = 0;
	convolution(inputArr, 5, kernelArr, 1, outputArr, &outputArrSize, 1, ZERO);
	return 0;
}


int convolution(double inputArr[], int inputArraySize, double kernelArr[], int kernelArraySize, double outputArr[], int* outputArraySize, int stride, PaddingType padding){
	int tempArraySize,m,k,i,j = 0,z = 0,stat = 0;
	double tempArr[255];
	double sum = 0;
	int paddingWidth = (kernelArraySize - 1)/2;
	tempArraySize = inputArraySize + 2*paddingWidth;
	*outputArraySize = ((inputArraySize - kernelArraySize + 2*paddingWidth)/stride) + 1;
	switch (padding){
		case ZERO:
			addPadding(inputArr, inputArraySize, tempArr, &tempArraySize, paddingWidth, zeroPadding);
			break;
	
		case SAME:
			addPadding(inputArr, inputArraySize, tempArr, &tempArraySize, paddingWidth, samePadding);
			break;
		case HALF:
			addPadding(inputArr, inputArraySize, tempArr, &tempArraySize, paddingWidth, halfPadding);
			break;
	}	

	if(kernelArraySize > inputArraySize)
		stat = -1;
	else{
		for(m = 0; m < *outputArraySize; m++){
			j = 0;
			for (k = z; k < kernelArraySize + z; k++){
				sum += tempArr[k]*kernelArr[j];
				outputArr[m] = sum;
				j++;
			}
			z += stride;
			sum = 0;

		}
		for (i = 0; i < *outputArraySize; i++){
			printf("%.1f\n", outputArr[i]);
		}
		stat = 0;
	}
	return stat;


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
	int i,k;

	for(i = 0; i < paddingWidth - 1; i++){
		outputArr[i] = 0;
	}
	for(k = outputArraySize - paddingWidth -1 ; k < outputArraySize;k++){
		outputArr[i] = 0;
	}

}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j;
	for(i = 0; i < paddingWidth; i++)
		outputArr[i] = outputArr[paddingWidth];	
	for(j = outputArraySize - paddingWidth ; j < outputArraySize; j++)
		outputArr[j] = outputArr[outputArraySize - paddingWidth - 1];

}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth){
	int i,j;
	for(i = 0; i < paddingWidth; i++)
		outputArr[i] = outputArr[paddingWidth]/2;	
	for(j = outputArraySize - paddingWidth ; j < outputArraySize; j++)
		outputArr[j] = outputArr[outputArraySize - paddingWidth - 1]/2;

}