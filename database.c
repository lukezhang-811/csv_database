#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// initializing the structure of the NODE
struct NODE {
        char ID[50];
        char name[50];
        char age[3];
        char gpa[10];
	struct NODE *next;
} *database = NULL;
// initializing a head NODE
// a program that loops through the linked list and prints out each line formatted
void show(struct NODE *records) {
	struct NODE *temp = records;
	int i=1;
	while(temp != NULL) {
		printf("Record %d: ID=%s NAME=%s AGE=%s GPA=%s \n", i, temp->ID, temp->name, temp->age, temp->gpa);
		temp = temp->next;
		i++;
	}
}
// a program that writes the new linked list into a new file and replace database.csv with that file
void update(struct NODE *records) {
        FILE *replace = fopen("database.tmp", "wt");
        struct NODE *temp = records;
        while(temp != NULL) {
                fprintf(replace, "%s,%s,%s,%s", temp->ID, temp->name, temp->age, temp->gpa);
		temp = temp->next;
	}
	system("rm database.csv");
	// I used mv here instead of cp becuase with mv you can do it in one line
	system("mv database.tmp database.csv");
}
// a program that removes the unwanted spaces from the csv file
void rmSpace(char *s) {
        char *d = s;
        do {
                while (*d == ' ') {
                        d++;
                }
        } while (*s++ = *d++);
}
// a program that deletes the first record that matches the inputted ID 
void delete(struct NODE *records, char *ID) {
	FILE *data;
        data=fopen("database.csv", "rt");
        char array[50];
	int index = 0;
	records = NULL;
	// basically creates a new linked list without the first record that matches the inputted ID
        while (fgets(array, 49, data) != NULL) {
		struct NODE *new = malloc(sizeof(struct NODE));
                struct NODE *temp;
		char *getID = strtok(array, ",");
		// if the ID match and no record has been removed, do not add record into the linked list
		if ((strcmp(ID, getID) == 0) && index == 0) {
			index = 1;
			continue;
		} else {
			rmSpace(getID);
			strcpy(new->ID, getID);
                        char *getName = strtok(NULL, ",");
			rmSpace(getName);
                        strcpy(new->name, getName);
                        char *getAge = strtok(NULL, ",");
			rmSpace(getAge);
                        strcpy(new->age, getAge);
                        char *getGPA = strtok(NULL, ",");
			rmSpace(getGPA);
                        strcpy(new->gpa, getGPA);
                        if (records == NULL) {
                        	records = new;
			} else {
				temp->next = new;
			}
			temp = new;
		}
        }
        fclose(data);
	show(records);
	// update the csv file
	update(records);
}
// a program that creates a node from the inputted data and appends it to the end of the csv file
void add(struct NODE *new, char *ID, char *name, char *age, char *gpa) {
	struct NODE *records = malloc(sizeof(struct NODE));
	struct NODE *temp;
	strcpy(records->ID, ID);
	strcpy(records->name, name);
	strcpy(records->age, age);
	strcpy(records->gpa, gpa);
	temp = new;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = records;
	new = temp;
	FILE *data = fopen("database.csv", "at");
	fprintf(data, "%s,%s,%s,%s \n", ID, name, age, gpa);
	fclose(data);
}
// a program that reverses the linked list because my linked list is backwards for some reason
// and i got too lazy to fix that and this does it
void reverse(){
	struct NODE *current=database;
	struct NODE *prev = NULL;
	struct NODE *apres = NULL;

	while (current != NULL) {
		apres = current->next;
		current->next = prev;
		prev = current;
		current = apres;
	}
	database = prev;
}

int main(int argc, char *argv[]) {
	// converts the data from the csv file into a linked lists
	FILE *data;
        data=fopen("database.csv", "rt");
	// makes a temporary linked list that takes from the csv file
        char array[50];
	struct NODE *records;
        while (fgets(array, 49, data) != NULL) {
                records = malloc(sizeof(struct NODE));
                char *getID = strtok(array, ",");
		rmSpace(getID);
                strcpy(records->ID, getID);
                char *getName = strtok(NULL, ",");
		rmSpace(getName);
                strcpy(records->name, getName);
                char *getAge = strtok(NULL, ",");
		rmSpace(getAge);
                strcpy(records->age, getAge);
                char *getGPA = strtok(NULL, ",");
		rmSpace(getGPA);
                strcpy(records->gpa, getGPA);
		records->next=database;
		database=records;
        }
	database = records;
	reverse();
        fclose(data);
	// if no cmd is entered, error msg appears and program is terminated
        if (argc == 1) {
                puts("Please enter: ./database CMD OPT1 OPT2 OPT3 OPT4");
                exit;
        }
        char *command = argv[1];
	// check if the cmd entered is SHOW, DELETE, or, ADD
        if ((strcmp(argv[1], "SHOW") !=0) && (strcmp(argv[1], "DELETE") !=0) && (strcmp(argv[1], "ADD") !=0)) {
                puts("The command you requested is invalid. Please select from one of these :SHOW, DELETE, ADD");
                exit;
        } 
	// if cmd is SHOW use function show()
        if (strcmp(command, "SHOW")==0) {
                show(database);
        }
	// if cmd is DELETE use function delete()
	if (strcmp(command, "DELETE")==0) {
		if (argc == 2) {
			puts("Name of record to delete is missing");
			exit;
		}
		delete(database, argv[2]);
	}
	// if cmd is ADD use function add()
	if (strcmp(command, "ADD")==0) {
		if (argc != 6) {
			puts("Missing ID, Name, AGE, and GPA arguments");
			exit;
		}
		add(database, argv[2], argv[3], argv[4], argv[5]);
		show(database);
	}
}

// Name: Luke Zhang
// ID: 260771133
