#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void main()
{
	const int numberRange = 100;
	int computerNumber = 0;
	int playerNumber = 0;

	time_t currentTime = time(0);

	srand(currentTime);
	computerNumber = rand();
	computerNumber = computerNumber % (numberRange + 1);
	printf("Computer set some number inrange from %i to %i \n", 0, numberRange);

	do

	{
		printf("Input your number: ");
		scanf_s("%i", &playerNumber);


		if (playerNumber < computerNumber)
		{
			printf("Larger!\n");
		}
		else
		{
			if (playerNumber > computerNumber)
			{
				printf("Less!\n");
			}
			else
			{
				printf("Yeaah!!!\n");
			}

		}

	}
	while (playerNumber != computerNumber);


	printf("Press anykey to continue...");
	getchar();
	getchar();

}