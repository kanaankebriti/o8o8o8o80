#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define DOCS_DB_NAME		"docsdb.csv"
#define PATIENTS_DB_NAME	"patsdb.csv"
#define MAX_ID_STR_LEN		"15"
#define MAX_ID_LEN			15
#define MAX_EMAIL_STR_LEN	50
#define NO_ROOM_AVAILABLE	100
#define MAX_NUM_OF_DOCS	50
#define MAX_NUM_OF_PATIENTS	800

// finds first available free record
unsigned char first_free_room(FILE* docsdb)
{
	// variables
	unsigned char key;			// doc's unique attributed key. 1 < key < 50
	char id[MAX_ID_LEN] = { 0 };// doc's id number. id = 0 means the room is free!

	for (key = 1; key <= MAX_NUM_OF_DOCS; key++)
	{
		// retrive id. skip first vale (key).
		fscanf(docsdb, "%*[^,],%" MAX_ID_STR_LEN "[^,],%*[^\n]", id);
		if (!strcmp(id, "0"))
			return key;
	}
	
	return NO_ROOM_AVAILABLE;
}

// Doc CSV Scheme
// key, id, name, email, wallet
void add_doc()
{
	// variables
	unsigned char key;		// doc's unique attributed key. 1 < key < 50
	char key_str[3];		// doc's key string buffer as a file i/o helper
	char name_str[50];		// doc's name string buffer as a file i/o helper
	char id_str[MAX_ID_LEN];// doc's id string buffer as a file i/o helper
	char email_str[50];		// doc's email string buffer as a file i/o helper
	char db_line_buff[1024];// buffering a line of dabase to memory
	FILE* docsdb;			// doctors database file pointer
	FILE* docsdb_temp;		// temporary database file pointer
	unsigned char free_room;

	// try to open doctors database
	docsdb = fopen(DOCS_DB_NAME, "r");
	if (!docsdb) // if unavailable then try to create one
	{
		docsdb = fopen(DOCS_DB_NAME, "w");
		if (!docsdb)
		{
			printf("Database Problem!\n");
			return;
		}
		else // populate docsdb.csv
		{
			for (key = 1; key <= MAX_NUM_OF_DOCS; key++)
				fprintf(docsdb, "%s,0,0,0,10\n", _itoa(key, key_str, 10));
			// close doctors database file
			fclose(docsdb);
			// open it again in read mode
			docsdb = fopen(DOCS_DB_NAME, "r");
		}
	}

	// create a temporary database
	docsdb_temp = fopen(DOCS_DB_NAME ".temp", "w");
	if (!docsdb_temp)
	{
		printf("Database Problem!\n");
		return;
	}

	// find the first free room
	free_room = first_free_room(docsdb);
	if (free_room == NO_ROOM_AVAILABLE)
	{
		printf("No Free Room available!\n");
		_getch();
		return;
	}

	// copy till first free room to a temporary database
	rewind(docsdb);
	for (key = 1; key < free_room; key++)
	{
		fgets(db_line_buff, 1024, docsdb);
		fprintf(docsdb_temp, "%s", db_line_buff);
	}

	// get new doc's info
	printf("ID = ");
	scanf("%s", &id_str);
	printf("Name = ");
	scanf("%s", &name_str);
	printf("Email = ");
	scanf("%s", &email_str);

	// save the new doc's info
	fprintf(docsdb_temp, "%s,%s,%s,%s,10\n", _itoa(key, key_str, 10), id_str, name_str, email_str);

	// skip a line from original database
	key++;
	fgets(db_line_buff, 1024, docsdb);

	// copy till last room to temporary database
	for (; key <= MAX_NUM_OF_DOCS; key++)
	{
		fgets(db_line_buff, 1024, docsdb);
		fprintf(docsdb_temp, "%s", db_line_buff);
	}

	// close doctors database file
	fclose(docsdb);
	fclose(docsdb_temp);

	// replace previous database
	system("del " DOCS_DB_NAME);
	system("ren " DOCS_DB_NAME ".temp " DOCS_DB_NAME);
}

// Patient CSV Scheme
// key, id, name, visits, wallet
void add_patient()
{
	// variables
	unsigned short int key;	// patient's unique attributed key. 1 < key < 50
	char key_str[4];		// patient's key string buffer as a file i/o helper
	char name_str[50];		// patient's name string buffer as a file i/o helper
	char id_str[MAX_ID_LEN];// patient's id string buffer as a file i/o helper
	char db_line_buff[1024];// buffering a line of dabase to memory
	FILE* patsdb;			// doctors database file pointer
	FILE* patsdb_temp;		// temporary database file pointer
	unsigned char free_room;

	// try to open doctors database
	patsdb = fopen(PATIENTS_DB_NAME, "r");
	if (!patsdb) // if unavailable then try to create one
	{
		patsdb = fopen(PATIENTS_DB_NAME, "w");
		if (!patsdb)
		{
			printf("Database Problem!\n");
			return;
		}
		else // populate docsdb.csv
		{
			for (key = 1; key <= MAX_NUM_OF_PATIENTS; key++)
				fprintf(patsdb, "%s,0,0,0,0\n", _itoa(key, key_str, 10));
			// close doctors database file
			fclose(patsdb);
			// open it again in read mode
			patsdb = fopen(PATIENTS_DB_NAME, "r");
		}
	}

	// create a temporary database
	patsdb_temp = fopen(PATIENTS_DB_NAME ".temp", "w");
	if (!patsdb_temp)
	{
		printf("Database Problem!\n");
		return;
	}

	// find the first free room
	free_room = first_free_room(patsdb);
	if (free_room == NO_ROOM_AVAILABLE)
	{
		printf("No Free Room available!\n");
		_getch();
		return;
	}

	// copy till first free room to a temporary database
	rewind(patsdb);
	for (key = 1; key < free_room; key++)
	{
		fgets(db_line_buff, 1024, patsdb);
		fprintf(patsdb_temp, "%s", db_line_buff);
	}

	// get new doc's info
	printf("ID = ");
	scanf("%s", &id_str);
	printf("Name = ");
	scanf("%s", &name_str);

	// save the new doc's info
	fprintf(patsdb_temp, "%s,%s,%s,0,0\n", _itoa(key, key_str, 10), id_str, name_str);

	// skip a line from original database
	key++;
	fgets(db_line_buff, 1024, patsdb);

	// copy till last room to temporary database
	for (; key <= MAX_NUM_OF_PATIENTS; key++)
	{
		fgets(db_line_buff, 1024, patsdb);
		fprintf(patsdb_temp, "%s", db_line_buff);
	}

	// close doctors database file
	fclose(patsdb);
	fclose(patsdb_temp);

	// replace previous database
	system("del " PATIENTS_DB_NAME);
	system("ren " PATIENTS_DB_NAME ".temp " PATIENTS_DB_NAME);
}

void clerk_main()
{
	// variables
	char input_com;		// command

	do
	{
		// clear screen
		system("cls");
		// retrieve user input
		printf("1-Add Doctor\n2-Add Patient\n3-Monthly Schedule\n4-Visits Schedule\n5-Exit\n");
		input_com = _getch();
		switch (input_com)
		{
		case '1': // 1-Add Doctor
			// clear screen
			system("cls");
			add_doc();
			break;
		case '2': // 2-Add Patient
			system("cls");
			add_patient();
			break;
		case '3': // 3-Monthly Schedule
			break;
		case '4': // 4-Visits Schedule
			break;
		case '5': // 5-Exit
			system("cls");
			return;
		}
		// reset input command
		input_com = 0;
	} while (input_com < '1' || input_com > '3');
}
