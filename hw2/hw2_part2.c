#include <stdio.h>

void drawRectangle(int width,int height,int startingPoint,int printLastLine);
void drawDoubleCircle(int radius);
void drawCar();

void main(){
	drawCar();
}

void drawRectangle(int width,int height,int startingPoint,int printLastLine){
	int i;
	int j;
	int k;
	for(i=0; i<height;i++){
		for(k=0;k<startingPoint-1;k++){
			printf(" ");
		}
		for(j=startingPoint; j<width+startingPoint; j++){
			if(i==0){
				printf("*");
			}
			else if (i!=0 && i!=height-1){
				if(j==startingPoint || j==width+startingPoint-1){
					printf("*");
				}
				else{
					printf(" ");
				}
			}
			else if(i==height-1){
				if(printLastLine==1){
					printf("*");
				}
				else if(printLastLine==0){
					if(j==startingPoint || j==width+startingPoint-1){
						printf("*");
					}
					else{
						printf(" ");
					}

				}

			}/*büyük else starting point, baş ve sondaki yıldızlar*/

		}/*j uzunluk*/
				printf("\n");
	}/*i yükseklik*/
}

void drawDoubleCircle(int radius){
	int i;
	int j;
	int l;
	int k;
	for(i=0;i<radius*2+1;i++){
		for (j=0;j<radius*2+1;j++)
		{
			if (j==radius+1)
			{
				for (k = 0; k < radius+1;k++)
				{
					printf("*");
				}/*tam ortası için yıldız for'u*/
			}
			else if (j==1 || j==radius*2)
			{
				for (l=0;l<radius;l++)
				{
					printf(" ");
				}
				printf("*");
			}/*ilk ve son satır için yıldız sayısı*/
		}/*uzunluk için for*/
		
		

	}/*yükseklik ve yarıçap için for*/	

}

void drawCar(){
	drawRectangle(40,10,11,0);
	drawRectangle(60,10,2,1);
	void drawDoubleCircle(4);
}