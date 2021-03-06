#include <stdio.h>
/*kaça kaçlık alanda oynanacağına karar verir.*/
#define GRIDSIZE 4
typedef enum {mined,
empty,
flaggedMined,
flaggedEmpty,
closedEmpty,
closedMined
}cell;
/*
*printGrid fonksiyonu  kapalı boş ve mayınlı hücreleri '.',
*bayrak konulan yerleri 'f',
*açılmış boş hücreleri 'e' ile gösterir.Ayrıca hücre şeklinde yazdırır.
*/
void printGrid(cell grid[][GRIDSIZE]);
/*
*openCell fonksiyonu, kullanıcı hücre açmak istediği zaman,girdiği koordinatta ki hücreyi ve komşularını açar..
*Eğer tanımlı olmayan koordinat söyler ise hiçbir işlem yapmadan tekrar koordinat ister.
*Tanımlı ise boşken hücreyi açar,mayınlı ise oyun biter.
*/
int openCell(cell grid[][GRIDSIZE], int x, int y);
/*
*flagCell fonksiyonu, kullanıcı hücrede bomba olduğunu düşünüyor ise bayrak koyar.
*Eğer bayrağı tekrar kaldırmak isterse kaldırır.
*/
void flagCell(cell grid[][GRIDSIZE], int x, int y);
/*
*İsCellEmpty fonksiyonu, hücrenin boş olup olmadığını kontrol eder.
*/
int isCellEmpty(cell grid[][GRIDSIZE], int x, int y);
/*
*isLocationLegal fonksiyonu, kullanıcının girdiği koordinat tanımlı mı değil mi kontrol eder.
*/
int isLocationLegal(int x, int y);
/*
*initGrid fonksiyonu, kullanacağımız grid arrayinin içini doldurur.
*/
void initGrid(cell grid[][GRIDSIZE]);
/*
*asMain fonksiyonu, tüm yazdığımız fonksiyonları bu fonksiyon içide çalıştırırız.
*/
int asMain();
/*Oyunun nasıl oynanacağını anlatır.*/
void instruct();
int isOver(cell grid[][GRIDSIZE]);
int openCellaux(cell grid[][GRIDSIZE], int x, int y);


/*
* game_cnt değişkeni, oyunun devam edip etmeyeceğini kontrol eder.
* f değişkeni, kullanıcı hücre mi açmak istiyor yoksa bayrak mı koymak istiyor bunu belirler.
* x ve y değişkenleri, kullanıcının hangi hücrelerde işlem yapacağını belirler.
* result değişkeni, openCell'den gelen return değerini alır ve oyun ne yapıcağını karar verir.
* move değişkeni, hamle sayısını ifade eder.
*/
int main(){
	asMain();
	return 0;
}
int asMain(){

	int game_cnt = 1,f,x,y,result,move = 0;
	/*grid arrayini deklare ediyoruz.*/
	cell grid[GRIDSIZE][GRIDSIZE];
	/*initGrid'de oluşturduğum arrayi çağırıyoruz.*/
	instruct();
	initGrid(grid);

	/*game_cnt 1 oldukça oyun devam edicek.*/
	do{
	/*Kullanıcıdan girdileri alıyoruz.*/
	printGrid(grid);
	printf("X değerini girin : ");
	scanf("%d", &x);
	printf("Y değerini girin : ");
	scanf("%d", &y);
	printf("Hücreyi acmak icin 0'a, bayrak koyup veya kaldırmak icin 1'e basin :");
	scanf("%d", &f);
	/*f değişkeni 0 ise hücre açar, 1 ise bayrak koyar.*/
	if(f == 0){
		/*openCell de arrayi değiştirdikten sonra return değerini resulta atar.
		* Result a göre yukarıda açıkladığım gibi ne olacağını karar verir.
		*/
		result = openCell(grid,x,y);
		if(result == 0){
			move++;
			printGrid(grid);
			printf("Kaybettiniz. (Hamle sayisi: %d)\n", move);
			game_cnt = 0;
				
		}
		else if(result == -2){
			printf("Orayı secemezsiniz. Tekrar deneyiniz\n\n\n");
			game_cnt = 1;
			move--;
		}
		else if(isOver(grid)){
			printGrid(grid);
			move++;
			printf("TEBRİKLER KAZANDINIZ. (Hamle sayisi: %d)\n", move);
			game_cnt = 0;
		}
		move++;
	}
	else if(f == 1){
		flagCell(grid,x,y);
		move++;
	}

	} while(game_cnt);
	return 0;
}

void initGrid(cell grid[][GRIDSIZE]){
	int i,j;
	cell init_arr[GRIDSIZE][GRIDSIZE] = {
			{closedEmpty,closedEmpty,closedMined,closedEmpty},
			{closedEmpty,closedEmpty,closedMined,closedMined},
			{closedEmpty,closedEmpty,closedEmpty,closedEmpty},
			{closedEmpty,closedEmpty,closedEmpty,closedEmpty}
		};

		for(i = 0; i < GRIDSIZE; i++){
			for(j = 0; j < GRIDSIZE; j++){
				grid[i][j] = init_arr[i][j];
			}
		}

}

/*
r açılan hücre sayısıdır.
*/
int openCell(cell grid[][GRIDSIZE], int x, int y){
	int r;
	if(grid[x][y] == closedMined){
		r = 0;
	}
	if(grid[x][y] == flaggedEmpty || grid[x][y] == flaggedMined || !(isLocationLegal(x,y))){
		r = -2;
	}
	if(isCellEmpty(grid,x,y)){
		r = openCellaux(grid,x,y);
	}

	return r;
}
/*bu fonksiyon her bir hücrenin etrafındaki hücreleri kontrol eder.*/
int openCellaux(cell grid[][GRIDSIZE], int x, int y){
	int total = 0;
	if(isCellEmpty(grid,x,y) && isLocationLegal(x,y)){
		grid[x][y] = empty;
		total++;
		total = total + openCellaux(grid,x+1,y) + openCellaux(grid,x,y+1)+ openCellaux(grid,x-1,y) + openCellaux(grid,x,y-1)+
		openCellaux(grid,x+1,y-1) + openCellaux(grid,x-1,y+1) + openCellaux(grid,x+1,y+1) + openCellaux(grid,x-1,y-1);
	}
	return total;
}

void flagCell(cell grid[][GRIDSIZE], int x, int y){
	if(isLocationLegal(x,y) && isCellEmpty(grid,x,y)){
		grid[x][y] = flaggedEmpty;
	}
	else if(isLocationLegal(x,y) && grid[x][y] == closedMined){
		grid[x][y] = flaggedMined;
	}

	else if(isLocationLegal(x,y) && grid[x][y] == flaggedEmpty){
		grid[x][y] = closedEmpty;
	}
	else if(isLocationLegal(x,y) && grid[x][y] == flaggedMined){
		grid[x][y] = closedMined;
	}

}

int isCellEmpty(cell grid[][GRIDSIZE], int x, int y){
	return grid[x][y] == closedEmpty;
}

int isLocationLegal(int x, int y){
	return (x < GRIDSIZE && x >= 0 && y < GRIDSIZE && y >= 0);

}

int isOver(cell grid[][GRIDSIZE]){
	int k,l,result;
	for(k = 0; k < GRIDSIZE; k++){
		for(l = 0; l < GRIDSIZE; l++){
			if(grid[k][l] == closedEmpty || grid[k][l] == flaggedEmpty){
				result = 0;
				break;
			}
			else{
				result = 1;
			}
		}
		if(result == 0){
			break;
		}
	}
	return result;
}

/*i ve j değişkeni, satır sütun kontrol eder ve duruma göre '.', 'e', 'f' basar.
*l değişkeni, hücreleri yapmamızı sağlar.
*/
void printGrid(cell grid[][GRIDSIZE]){

	int i,j,l;

	for(i = 0; i < GRIDSIZE; i++){
		for (l = 1; l < GRIDSIZE*3-2; l++){
			printf("-");
		}
		printf("\n");
		printf("|");
		for(j = 0; j < GRIDSIZE; j++){
			if (grid[i][j] == closedEmpty){
				printf(".|");
			}
			else if(grid[i][j] == closedMined){
				printf(".|");
			}
			else if(grid[i][j] == empty){
				printf("e|");
			}
			else if(grid[i][j] == flaggedMined || grid[i][j] == flaggedEmpty){
				printf("f|");
			}

		}
		printf("\n");
	}
	for (l = 1; l < GRIDSIZE*3-2; l++){
		printf("-");
	}

	printf("\n");
}

void instruct(){
	printf("----------MINESWEEPER--------\n");
	printf("//Oyunun amacı hücrelerde ki mayınları seçmeden mayın olmayan tüm hücreleri açmak.\n");
	printf("//X'e satır,Y'ye ise sütun değerini girin.DIKKAT! Satır ve sütunlar 0'dan başlar.\n");
	printf("//Eğer bomba olduğunu düşünüyorsanız bayrak koyabilirsiniz.Vazgeçerseniz kaldırabilirsiniz.\n");
	printf("IYI OYUNLAR\n\n");
}