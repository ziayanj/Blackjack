// Blackjack!

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // To use the time() function 

// Function declarations
char card(int x); 
int cardvalue(int currentcard, int handvalue);
void printer(int array[], int currentindex);

int main()
{
	srand(time(NULL));

	int player[10], dealer[10]; // Store the player and dealer card values, respectively. (size 10 supposed required value)
	char command, playagain; 
	int playerindex, dealerindex; // Store the current index, increasing whenever a new card is taken.
	int playervalue, dealervalue; // Store the current hand value of player/dealer.
	int playerwins = 0, dealerwins = 0; // Store the current number games won by player/dealer.
	
	do
	{
		playervalue = 0, dealervalue = 0; // Since no cards have been taken yet, the value of cards is 0 for both player and dealer.

		// Randomly distributing the first two cards to both the player and the dealer and storing in the respective array.
		player[0] = rand() % 13 + 1; 
		player[1] = rand() % 13 + 1;
		dealer[0] = rand() % 13 + 1;
		dealer[1] = rand() % 13 + 1;

		playerindex = 2, dealerindex = 2; // Since the 0th and 1st index has been filled by the two cards
		
		// Calculating values of first and second card for both the player and dealer.
		playervalue += cardvalue(player[0], playervalue); 
		playervalue += cardvalue(player[1], playervalue);
		dealervalue += cardvalue(dealer[0], dealervalue);
		dealervalue += cardvalue(dealer[1], dealervalue);

		// Printing out the first set of cards, with the dealer's hole card hidden.
		printf("Player's Hand: ");
		printer(player, playerindex);
		printf("\nDealer's Hand: ");
		printer(dealer, dealerindex - 1);
		printf("X\n");

		if (playervalue != 21) // Since if player's hand equals 21, it's dealer's turn automatically.
		{
			printf("Enter command: ");
			scanf(" %c", &command);
		}

		while (command == 'h' && playervalue != 21) // 'h' basically means the user is asking for another card
		{
			// Getting another card, calculating the updated hand value and incrementing the index for the players' cards.
			player[playerindex] = rand() % 13 + 1;
			playervalue += cardvalue(player[playerindex], playervalue);
			playerindex++;

			if (playervalue != 21) // Skip this if the player's hand value equals 21, since player's turn ends.
			{
				printf("\nPlayer's Hand: ");
				printer(player, playerindex);

				if (playervalue > 21) // The player busts if his value has gone over 21.
				{
					printf("\nDealer's Hand: ");
					printer(dealer, dealerindex);

					printf("\nPlayer busts.\n");
					break;
				}
				printf("\nDealer's Hand: ");
				printer(dealer, dealerindex - 1);
				printf("X\n");

				printf("Enter command: ");
				scanf(" %c", &command);
			}
		}

		if (command == 's' || playervalue == 21)
		{
			while (dealervalue < 17) // Keep taking cards for dealer and updating his hand value till it gets to 17.
			{
				dealer[dealerindex] = rand() % 13 + 1;
				dealervalue += cardvalue(dealer[dealerindex], dealervalue);
				dealerindex++;
			}

			printf("\nPlayer's Hand: ");
			printer(player, playerindex);
			printf("\nDealer's Hand: ");
			printer(dealer, dealerindex);

			if (dealervalue > 21) // Dealer busts if his hand value goes over 21.
			{
				printf("\nDealer busts.\n");
			}
			else // Otherwise, player and dealer hand values are compared to determine the result.
			{
				if (playervalue > dealervalue)
				{
					printf("\nPlayer wins.\n");
					playerwins++; // Keeping a count of how many times the player has won.
				}
				else if (dealervalue > playervalue)
				{
					printf("\nDealer wins.\n");
					dealerwins++; // Keeping a count of how many times the dealer has won.
				}
				else // If both hand values are equal, the one with the less cards wins.
				{
					if (playerindex > dealerindex)
					{
						printf("\nDealer wins.\n");
						dealerwins++;
					}
					else if (playerindex < dealerindex)
					{
						printf("\nPlayer wins.\n");
						playerwins++;
					}
					else // If both have the same hand value and the same number of cards, the hand is a tie, called a push.
						printf("\nA push! No one won.\n");
				}
			}
		}
		else if (command == 'q')
		{
			printf("\nDealer wins.\n");
			dealerwins++;
		}
		printf("Enter 'q' to quit, anything else to play another game: ");
		scanf(" %c", &playagain);
	}
	while (playagain != 'q');

	printf("\t\t\t  Total Score\n");
	printf("\t\t\tDealer wins = %d\n", dealerwins);
	printf("\t\t\tPlayer wins = %d\n", playerwins);

	getch();
	return 0;
}

char card(int x) // Used to handle face cards generation (J, Q, K, A).
{
	if (x == 11)
		return 'J';
	else if (x == 12)
		return 'Q';
	else if (x == 13)
		return 'K';
	else if (x == 1)
		return 'A';
}

int cardvalue(int currentcard, int handvalue) // Used to calculate the value of face cards.
{
	if (currentcard == 1)
	{
		if ((handvalue + 11) > 21)
			return 1; // If adding 11 to the current hand value takes it over 21, the value of A will be taken as 1.
		else 
			return 11; // Otherwise, it'll be taken as 11 as it's more advantageous.
	}
	else if ((currentcard == 11) || (currentcard == 12) || (currentcard == 13)) 
		return 10; // Since J, Q and K have a value of 10.
	else 
		return currentcard; // Since numeric cards have their numeric value.
}

void printer(int array[], int currentindex) /*	array = the player/dealer array containing all card values,
												currentindex = how many cards this array currently has.		 */
{
	for (int index = 0; index < currentindex; index++)
	{
		if ((array[index] == 1) || (array[index] > 10)) // Print J, Q, K, A as a character.
			printf("%c ", card(array[index]));
		else											// Print numeric cards using their integer values.
			printf("%d ", array[index]);
	}
}
