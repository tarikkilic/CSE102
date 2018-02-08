#include <stdio.h>
#include <string.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct person_s {
	int id;
	char name[NAMELEN];
} Person;

typedef struct record_s {
	int id;
	char number[NAMELEN];
} Record;

typedef struct Records_s {
	Record data[MAXRECORD];
	int size;
} Records;

typedef struct people_s {
	Person data[MAXRECORD];
	int size;
} People;

/* ========== IMPLEMENT THE FUNCTIONS BELOW ========== */
/*
	Write Records.data array to the filename.
	Note that file should be binary.
*/
void writeRecords(Records records, char* filename) {
	int i;
	FILE *trk;
	trk = fopen(filename,"wb");
	for (i = 0; i < records.size;i++){
		fwrite(&records.data[i],sizeof(Record),1,trk);
	}

	fclose(trk);
}
	

/*
	Reads Record structs from the binary file and places them to Records.data array.
	Note that the number of Record structs in the file is unkown.
*/
void readRecords(Records *records, char* filename) {
	records->size = 0;
	FILE *trk;
	trk = fopen(filename,"rb");
	if(trk == NULL)
		printf("köyüne dön\n");
	else
		while(fread(&records->data[records->size],sizeof(Record),1,trk) > 0){
			records->size++;
		}

	fclose(trk);	
}

/*
	Write People.data array to the filename.
	Note that file should be binary.
*/
void writePeople(People people, char* filename) {
	int i;
	FILE *trk;
	trk = fopen(filename,"wb");
	for (i = 0; i < people.size;i++){
		fwrite(&people.data[i],sizeof(Person),1,trk);
	}

	fclose(trk);

}

/*
	Reads Person structs from the binary file and places them to People.data array.
	Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) {
	people->size=0;
	FILE *trk;
	trk = fopen(filename,"rb");
	if(trk == NULL){
		printf("köyüne dön\n");
	}
	else
		while(fread(&people->data[people->size],sizeof(Person),1,trk) > 0){
			people->size++;
		}
	fclose(trk);	

}

/**
  * Reads the input file and constructs People and Records structs.
  	Note that each Record in Records is unique (should not present multiple times).
  */
void read(char* filename, People *people, Records *records) {
	int x = 0,k = 0;
	char temp_surname[20];
	FILE *trk;
	trk = fopen("input.txt","r");
	
	if(trk == NULL){
		printf("yalla\n");
	}
	else{
		while(!(feof(trk))){
			fscanf(trk,"%d",&people->data[people->size].id);
			fscanf(trk,"%s",people->data[people->size].name);
			fscanf(trk,"%s",temp_surname);
			strcat(people->data[people->size].name," ");
			strcat(people->data[people->size].name,temp_surname);
			fscanf(trk,"%d",&x);
			for(k = 0; k < x;k++){
				records->data[records->size].id = people->data[people->size].id;
				fscanf(trk,"%s",records->data[records->size].number);
				records->size +=1;
			}
			people->size +=1;
		}
	}


	fclose(trk);
}

/* ========== IMPLEMENT THE FUNCTIONS ABOVE ========== */

void print(People people, Records records) {
	int i,j,found = 0;
	/* header */
	printf("%-5s %-30s %-20s\n", "ID","NAME","NUMBER(s)");
	/* line */
	for (i = 0; i < 57; ++i)
		printf("-");
	printf("\n");

	for (i = 0; i < people.size; ++i) {
		found = 0;
		printf("%-5d %-30s", people.data[i].id, people.data[i].name);
		for (j = 0; j < records.size; ++j) {
			if(records.data[j].id == people.data[i].id) {
				if(found)
					printf("%36s", "");
				printf("%-20s\n", records.data[j].number);
				found = 1;
			}
		}
		printf("\n");
	}
}

int isPeopleEq(People ppl1, People ppl2) {
	int i;
	if(ppl1.size != ppl2.size)
		return 0;
	for (i = 0; i < ppl1.size; ++i)
		if(strcmp(ppl1.data[i].name,ppl2.data[i].name) ||
			ppl1.data[i].id != ppl2.data[i].id)
			return 0;
	return 1;
}

int isRecordsEq(Records rec1, Records rec2) {
	int i;
	if(rec1.size != rec2.size)
		return 0;
	for (i = 0; i < rec1.size; ++i)
		if(strcmp(rec1.data[i].number,rec2.data[i].number) ||
			rec1.data[i].id != rec2.data[i].id)
			return 0;
	return 1;
}

int main(int argc, char** argv) {
	People people1,people2;
	Records records1,records2;
	people1.size = 0;
	records1.size = 0;
	read(argv[1],&people1, &records1);
	print(people1, records1);
	writePeople(people1,"people.bin");
	writeRecords(records1,"records.bin");
	readRecords(&records2,"records.bin");
	readPeople(&people2,"people.bin");
	print(people2, records2);
	printf("%s\n", isRecordsEq(records1,records2) ? "RECORDS ARE SAME" : "RECORDS ARE DIFFERENT!");
	printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
	return 0;
}
