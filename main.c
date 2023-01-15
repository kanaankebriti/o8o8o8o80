#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define CLERK_ID	"a"
#define CLERK_PSWD	"a"

// function prototyps
void clerk_main();

void user_sign_in(char* user, char* password)
{
	if (!strcmp(user, CLERK_ID) && !strcmp(password, CLERK_PSWD))
	{
		system("cls");
		clerk_main();
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
