#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void doc_main()
{
	// variables
	char input_com;		// command

	do
	{
		// clear screen
		system("cls");
		// retrieve user input
		printf("1-Determining the shifts\n2-Reserved Visits\n3-Patient Prescription\n4-Rent Payment\n5-Visits Payment\n6-Exit\n");
		input_com = _getch();
		switch (input_com)
		{
		case '1': // 1-Determining the shifts
			break;
		case '2': // 2-Reserved Visits
			break;
		case '3': // 3-Patient Prescription
			break;
		case '4': // 4-Rent Payment
			break;
		case '5': // 5-Visits Payment
			break;
		case '6': // 6-Exit
			system("cls");
			return;
		}
		// reset input command
		input_com = 0;
	} while (input_com < '1' || input_com > '6');
}
