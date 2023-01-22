#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define CLERK_ID			"Admin"
#define CLERK_PSWD			"Admin"
#define USERS_DB_NAME		"usersdb.csv"
#define USERSDB_TYPE_DOC	"doc"
#define USERSDB_TYPE_PAT	"pat"
#define MAX_ID_STR_LEN		"15"
#define USER_IS_DOC			1
#define USER_IS_PAT			2
#define USER_IS_NAN			3
#define MAX_ID_LEN			15

// function prototyps
void clerk_main();
void doc_main();
void pat_main();

// Users CSV Scheme
// id, password, type (USERSDB_TYPE_DOC or USERSDB_TYPE_PAT)

char is_user_in_db(char* user, char* password)
{
	char usrnm[MAX_ID_LEN] = { 0 };	// username
	char pswd[MAX_ID_LEN] = { 0 };	// password
	char usrtyp[MAX_ID_LEN] = { 0 };// account's type
	FILE* usersdb;					// users database file pointer

	// try to open users database
	usersdb = fopen(USERS_DB_NAME, "r");
	if (!usersdb) // if unavailable
		return USER_IS_NAN;
	else
		while (fscanf(usersdb, "%"MAX_ID_STR_LEN"[^,],%"MAX_ID_STR_LEN"[^,],%"MAX_ID_STR_LEN"[^\n]\n", usrnm, pswd, usrtyp) != EOF)
		{
			if (!strcmp(user, usrnm) && !strcmp(password, pswd))
			{
				if (!strcmp(usrtyp, USERSDB_TYPE_DOC))
				{
					fclose(usersdb);
					return USER_IS_DOC;
				}
				else if (!strcmp(usrtyp, USERSDB_TYPE_PAT))
				{
					fclose(usersdb);
					return USER_IS_PAT;
				}
				else
				{
					fclose(usersdb);
					return USER_IS_NAN;
				}
			}
		}

	fclose(usersdb);
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
