#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void pat_main()
{
	// variables
	char input_com;		// command

	do
	{
		// clear screen
		system("cls");
		// retrieve user input
		printf("1-Book an Appointment\n2-Cancel an Appointment\n3-All Appointments\n4-Prescriptions\n5-Exit\n");
		input_com = _getch();
		switch (input_com)
		{
		case '1': // 1-Book an Appointment
			break;
		case '2': // 2-Cancel an Appointment
			break;
		case '3': // 3-All Appointments
			break;
		case '4': // 4 - Prescriptions
			break;
		case '5': // 5-Exit
			system("cls");
			return;
		}
		// reset input command
		input_com = 0;
	} while (input_com < '1' || input_com > '6');
}
