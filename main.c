#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "defs.h"

// function prototyps
void clerk_main();
void doc_main();
void pat_main();

char is_user_in_db(char* user, char* password)
{
	// variables
	unsigned int key;				// unique attributed key. docs: 1 < key < 50 & pats: 1 < key < 800
	char usrnm[MAX_ID_LEN] = { 0 };	// username
	char pswd[MAX_ID_LEN] = { 0 };	// password
	char usrtyp[MAX_ID_LEN] = { 0 };// account's type
	FILE* dbfile;					// users database file pointer

	// search doctors database
	dbfile = fopen(DOCS_DB_NAME, "r");
	if (!dbfile) // if unavailable
		return USER_IS_NAN;
	else
		for (key = 1; key <= MAX_NUM_OF_DOCS; key++)
		{
			// retrive id. skip first vale (key).
			fscanf(dbfile, "%*[^,],%" MAX_ID_STR_LEN "[^,],%" MAX_ID_STR_LEN "[^,],%*[^\n]", usrnm, pswd);

			// skip free rooms
			if (!strcmp(usrnm, "0"))
				continue;

			if (!strcmp(user, usrnm) && !strcmp(password, pswd))
			{
				fclose(dbfile);
				return USER_IS_DOC;
			}
		}

	// search patients database
	dbfile = fopen(PATS_DB_NAME, "r");
	if (!dbfile) // if unavailable
		return USER_IS_NAN;
	else
		for (key = 1; key <= MAX_NUM_OF_PATS; key++)
		{
			// retrive id. skip first vale (key).
			fscanf(dbfile, "%*[^,],%" MAX_ID_STR_LEN "[^,],%" MAX_ID_STR_LEN "[^,],%*[^\n]", usrnm, pswd);

			// skip free rooms
			if (!strcmp(usrnm, "0"))
				continue;

			if (!strcmp(user, usrnm) && !strcmp(password, pswd))
			{
				fclose(dbfile);
				return USER_IS_PAT;
			}
		}

	fclose(dbfile);
	return USER_IS_NAN;
}

void user_sign_in(char* user, char* password)
{
	if (!strcmp(user, CLERK_ID) && !strcmp(password, CLERK_PSWD))
	{
		system("cls");
		clerk_main();
	}
	else if (is_user_in_db(user, password) == USER_IS_DOC)
	{
		system("cls");
		doc_main();
	}
	else if(is_user_in_db(user, password) == USER_IS_PAT)
	{
		system("cls");
		pat_main();
	}
	else
	{
		system("cls");
		printf("user is not available!\n");
		_getch();
	}
}

int main()
{
	// variables
	char input_com;		// command
	char input_id[50];	// id number
	char input_pswd[50];// password

	// main loop
	do
	{
		// clear screen
		system("cls");
		// retrieve user input
		printf("1-Sign in\n2-Forgot Password\n3-Exit\n");
		input_com = _getch();
		switch (input_com)
		{
		case '1': // 1-Sign in
			// clear screen
			system("cls");
			// id
			printf("ID Number = ");
			scanf("%s", &input_id);
			// password
			printf("Password = ");
			scanf("%s", &input_pswd);
			// handle signing in
			user_sign_in(input_id, input_pswd);
			break;
		case '2': // 2-Forgot Password
			system("cls");
			break;
		case '3': // 3-Exit
			return EXIT_SUCCESS;
		}
		// reset input command
		input_com = 0;
	} while (input_com < '1' || input_com > '3');
}
