#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct record_s {
    int id;
    char number[NAMELEN];
    struct record_s *next;
} Record;

typedef struct person_s {
    int id;
    char name[NAMELEN];
    double expenditure;
    Record *numbers;
} Person;

typedef struct people_s {
    Person data[MAXRECORD];
    int size;
} People;


/*
 Write People.data array to the filename.
*/
void writePeople(People people, char* filename) {
    FILE *trk;
	int i;
	trk = fopen(filename,"wb");
	for (i = 0; i < people.size;i++){
		fwrite(&people.data[i],sizeof(Person),1,trk);
	}

	fclose(trk);
}

/*
 Reads Person structs from file and places them to People.data array.
 Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) {
	FILE *trk;
	people->size=0;
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

/*
 Calculates the expected expenditure for the person with unknown expenditure.
 Persons' expenditure is -1 if their expenditure is unknown.
 You should calculate average bill amount for a phone number and multiply it by
 the phone number count for the person.
*/
void imputation(People *people) {
	int not_neg = 0,i,neg = 0;
	double sum = 0;
	Record* rec;
	for(i = 0; i < people->size;i++){
		if(people->data[i].expenditure != -1){
			rec = people->data[i].numbers;
			sum += people->data[i].expenditure;
			while(rec != NULL){
				not_neg++;
				rec = rec->next;
			}
		}
			

		
	}
	for(i = 0; i < people->size; i++){
		if(people->data[i].expenditure == -1){
			neg = 0;
			rec = people->data[i].numbers;
			while(rec != NULL){
				neg++;
				rec = rec->next;
			}
			people->data[i].expenditure = (sum/not_neg)*neg;
		}
	}
}

/*
 Reads the input file and constructs People struct.
 Note that the number of phone numbers in file is unknown unlike your
 previous homework. You should keep phone numbers in the linked list
 (numbers field)
*/
void read(char* filename, People *people) {
	FILE *trk;
	int status = 1;
	char *name = (char*)calloc(NAMELEN,sizeof(char));
	char *surname = (char*)calloc(NAMELEN,sizeof(char));
	char str[50];
	char *pch;
	Record *rec; 
	trk = fopen(filename,"r");
	if(trk == NULL){
		printf("köyüne dön\n");
	}
	else{
		while(1){
			status = fscanf(trk,"%d",&people->data[people->size].id);
			if(status != 1)
				break;
			fscanf(trk,"%s %s",name,surname);
			sprintf(people->data[people->size].name,"%s %s",name,surname);
			fscanf(trk,"%lf",&people->data[people->size].expenditure);
			people->data[people->size].numbers = (Record*)malloc(sizeof(Record));
			rec = people->data[people->size].numbers;
			fgets(str,50,trk);
			pch = strtok (str," \n");
			rec->id = people->data[people->size].id;
			strcpy(rec->number,pch);
  			while (1){
  				pch = strtok (NULL, " \n");
  				if (pch != NULL) {
  					rec->id = people->data[people->size].id;
	  				rec->next = (Record*)malloc(sizeof(Record));
	  				rec->next->id = people->data[people->size].id,
	      			strcpy(rec->next->number,pch);
	    			rec = rec->next;
	    		} else {
	    			break;
	    		}
 	 		}
 	 		rec->next = NULL;
 	 		people->size++;
		}
	}
	fclose(trk);
	free(name);
	free(surname);
}


void print(People people) {
    int i,found = 0;
    Record *rec;
    /* header */
    printf("%-5s %-30s %-20s %-20s\n", "ID","NAME","EXPENDITURE","NUMBER(s)");
    /* line */
    for (i = 0; i < 78; ++i)
        printf("-");
    printf("\n");

    for (i = 0; i < people.size; ++i) {
        found = 0;
        printf("%-5d %-30s %-20.4f", people.data[i].id, people.data[i].name, people.data[i].expenditure);
        rec = people.data[i].numbers;
        while(rec) {
            if(found)
                printf("%57s", "");
            else
                found = 1;
            printf("%-20s\n", rec->number);
            rec = rec->next;
        }
        printf("\n");
    }
}

int isPeopleEq(People ppl1, People ppl2) {
    Record *rec1,*rec2;
    int i,found = 0;
    int p1size = 0, p2size = 0;
    if(ppl1.size != ppl2.size)
        return 0;
    for (i = 0; i < ppl1.size; ++i)
        if(strcmp(ppl1.data[i].name,ppl2.data[i].name))
            return 0;
        if(ppl1.data[i].id != ppl2.data[i].id)
            return 0;

        p1size = p2size = 0;
        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            ++p1size;
            rec1 = rec1->next;
        }

        rec2 = ppl2.data[i].numbers;
        while(rec2) {
            ++p2size;
            rec2 = rec2->next;
        }

        if(p1size != p2size) {
            return 0;
        }

        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            rec2 = ppl2.data[i].numbers;
            found = 0;
            while(!found && rec2) {
                if(strcmp(rec1->number,rec2->number) == 0) {
                    found = 1;
                    break;
                }
                rec2 = rec2->next;
            }
            if(!found) {
                return 0;
            }
            rec1 = rec1->next;
        }
    return 1;
}

int main(int argc, char** argv) {
    People people1,people2;
    people1.size = 0;
    read(argv[1],&people1);
    print(people1);
  	writePeople(people1,"people.bin");
    readPeople(&people2,"people.bin");
	print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n");
    imputation(&people1);
    print(people1);
    return 0;
}
