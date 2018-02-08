/*
 Created by tarik on 23.04.2017.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NUM_WORDS 500
#define WORD_LENGHT 50

int getAndFilterWord(char* w);
void addWord(char* w,char words[MAX_NUM_WORDS][WORD_LENGHT],
        int occur[MAX_NUM_WORDS], int* word_count);
void sortWords(char words[MAX_NUM_WORDS][WORD_LENGHT],
               int occur[MAX_NUM_WORDS],int word_count);
void lower_case(char* w);
void myTest();


int main(int argc,char **argv){
	printf("%s %s",argv[1],argv[0]);
	//myTest();
	return 0;
}
void myTest(){
	char w[50], words[MAX_NUM_WORDS][WORD_LENGHT];
    int occur[MAX_NUM_WORDS];
    int j = 0, i = 0,word_count = 0;
    for(j = 0; j < MAX_NUM_WORDS; j++){   /*her kelime en az bir kere yazılacağından occur dizisini 1 ile dolduruyoruz.*/
    	occur[j] = 1;
    }
    while(strcmp(w,"end") != 0){  /*kullanıcı end girene kadar kelime girer.*/
    	scanf("%s", w);		
    	getAndFilterWord(w);		/*Kelimeyi düzenler.Büyük harfleri küçültür,sayı, nokta vb. şeyleri siler.*/
    	addWord(w,words,occur,&word_count); /*kelimeleri tek tek word dizisine ekler eğer aynı kelimeyi girerse occur dizisinde işlem ypaar.*/
    }
    sortWords(words,occur,word_count);  /*En çok kullanılan kelimeyi bulabilmek için sıralama yapar.*/
  	for(i = 0; i < 3;i++){				/*En çok kullanılan 3 kelimeyi bulur.*/
        printf("Word: %s -> Repetition: %d\n", words[i], occur[i]);
    }
}

int getAndFilterWord(char* w){
    int i,stat = 0,j,k;
    lower_case(w);  /*Büyük olan harfleri küçültür.*/
    for(i = 0; i < strlen(w);i++){
        while(!( isalpha(w[i])  || w[i] == '\0')){  /*harf olmayan karakterleri siler.*/
        	for(j = i; w[j] != '\0'; j++){
            	w[j] = w[j+1];
        	}
        	w[j] = '\0';
           
        }
    }
   for(k = 0; w[k] != '\0'; k++){
    	if(isalpha(w[k])){
    		stat = 1;             /*harf girmişse 1 girmemişse 0 return eder.*/
    	}
    }
	
    return stat;
}

void addWord(char* w,char words[MAX_NUM_WORDS][WORD_LENGHT],
        int occur[MAX_NUM_WORDS], int* word_count){
	int i,status = 1;
	for(i = 0; i < *word_count;i++){
		if(strcmp(words[i],w) == 0){   /*Kelime öncede varsa bir artırır.*/
			occur[i] +=1;
			status = 0;	
			break;
		}
	}
	if(status == 1 && strcmp(w,"end")){         /*yoksa kelimeyi words dizisine ekler.*/
		strcpy(words[*word_count],w);
		(*word_count)++;
	}
}

void sortWords(char words[MAX_NUM_WORDS][WORD_LENGHT],
               int occur[MAX_NUM_WORDS],int word_count){
	int i,j,temp;
	char temp1[WORD_LENGHT];
	for(i = 0; i < word_count; i++){
		for(j = i; j < word_count; j++){
			if(occur[j] > occur[i]){
				temp = occur[j];               /*En çok tekrarlana kelime büyükten küçüğe sıralanır.*/
				occur[j] = occur[i];			/*kaç defa tekrarlandığını tutan occur diziside aynı şekilde sıralanır. */
				occur[i] = temp;

				strcpy(temp1,words[j]);
				strcpy(words[j],words[i]);
				strcpy(words[i],temp1);
			}
		}
	}
}

void lower_case(char *w){   /*Harfleri küçültür.*/
	int i;
	for ( i = 0; w[i] != '\0'; ++i){
		if(w[i] >= 'A' && w[i] <= 'Z'){
			w[i] = w[i] + ('a' - 'A');
		}
	}

}


