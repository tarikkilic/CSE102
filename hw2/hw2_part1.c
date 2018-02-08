#include <stdio.h>
int fTheFunction(int x,int functionNumber);
void drawFunction(int xAxis,int yAxis,int functionNumber);

void main()
{
	int result;
	result = fTheFunction(2,5);
	drawFunction(40,40,5);
}

int fTheFunction(int x,int functionNumber){
	if (functionNumber == 1)
	{
		return 2*x;
	}
	else if (functionNumber == 2)
	{
		return 5*x;
	}
	else if (functionNumber == 3)
	{
		return -x-1;
	}
	else if (functionNumber == 4)
	{
		return x+3;
	}
	else if (functionNumber == 5)
	{
		return 5*x+7;
	}

}

/* Created by Tarık Kılıç */
/* Bu program verdiğiniz fonksiyonun grafiğini çizer.*/
/*Parametreler:x ve y ekseni uzunluğu,fonksiyon numarası.*/
/*Çıktı ise verdiğiniz fonksiyonun grafiği. */

void drawFunction(int xAxis,int yAxis,int functionNumber){ /* Parametreler:x ve y ekseni uzunluğu,fonksiyon numarası.*/
	int i;   /*Değişkenlerimiz*/ /*Dikey çizgiler*/
	int j; /*yatay çizgiler*/
	int y; /*Fonksiyonumuzun sonucu*/
	int k; /*hangi x noktasında yıldız koyucağımızı belirten değişken. */
	int x; /*fonksiyona gireciğimiz değerler için kullandığjmız değişken. */
	for (i = 0; i < yAxis;i++){/*her bir dikey koordinat çizgileri için*/
		printf("|");
		for(x = 1; x < xAxis+1 ;x++){           /*Fonksiyonuza tek tek x değerlerini deniyoruz. */
			y = fTheFunction(x,functionNumber); /*Ve sonucu y değişkenine atıyoruz*/
			if(i == yAxis - y){                 /*Bu y değişkeni ile hangi y noktasına yıldızı koyacağımızı belirliyoruz.*/
				for(k = 0;k < x;k++){         /*Hangi x noktasında yıldızı koyacağımızı belirliyoruz.*/
					printf(" ");
				}
				printf("*");
			}
		}
		printf("\n");
		if(i == yAxis-1){ /*x ekseni çizgileri için koşul*/
			printf("|");
			for (j = 0; j < xAxis;j++){/*x ekseninin uzunluğu için döngü */
				printf("-");
			}
		}
	}
	printf("\n");


}
