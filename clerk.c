#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_ID_STR_LEN		"15"
#define MAX_ID_LEN			15
#define MAX_EMAIL_STR_LEN	50
#define NO_ROOM_AVAILABLE	100
#define MAX_NUM_OF_ROOMS	50

// Doc CSV Scheme
// key, id, name, email, wallet

unsigned char first_free_room(FILE* docsdb)
{
	// variables
	unsigned char key;			// doc's unique attributed key. 1 < key < 50
	char id[MAX_ID_LEN] = { 0 };// doc's id number. id = 0 means the room is free!

	for (key = 1; key <= MAX_NUM_OF_ROOMS; key++)
	{
		// retrive id. skip first vale (key).
		fscanf(docsdb, "%*[^,],%" MAX_ID_STR_LEN "[^,],%*[^\n]", id);
		if (!strcmp(id, "0"))
			return key;
	}
	
	return NO_ROOM_AVAILABLE;
}

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
	docsdb = fopen("docsdb.csv", "r");
	if (!docsdb) // if unavailable then try to create one
	{
		docsdb = fopen("docsdb.csv", "w");
		if (!docsdb)
		{
			printf("Database Problem!\n");
			return;
		}
		else // populate docsdb.csv
		{
			for (key = 1; key <= MAX_NUM_OF_ROOMS; key++)
				fprintf(docsdb, "%s,0,0,0,10\n", _itoa(key, key_str, 10));
			// close doctors database file
			fclose(docsdb);
			// open it again in read mode
			docsdb = fopen("docsdb.csv", "r");
		}
	}
	// create temporary database
	docsdb_temp = fopen("docsdb.csv.temp", "w");
	if (!docsdb)
	{
		printf("Database Problem!\n");
		return;
	}

	// find first free room
	free_room = first_free_room(docsdb);
	printf("free room = %d\n", free_room);
	if (free_room == NO_ROOM_AVAILABLE)
	{
		printf("No Free Room available!\n");
		_getch();
		return;
	}

	// save till first free room to temporary database
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

	// save new doc's info
	fprintf(docsdb_temp, "%s,%s,%s,%s,10\n", _itoa(key, key_str, 10), id_str, name_str, email_str);

	// skip one line from original database
	key++;
	fgets(db_line_buff, 1024, docsdb);

	// save till last room to temporary database
	for (; key <= MAX_NUM_OF_ROOMS; key++)
	{
		fgets(db_line_buff, 1024, docsdb);
		fprintf(docsdb_temp, "%s", db_line_buff);
	}

	// close doctors database file
	fclose(docsdb);
	fclose(docsdb_temp);

	// replace previous database
	system("del docsdb.csv");
	system("ren docsdb.csv.temp docsdb.csv");
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
