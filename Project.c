#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  // Added to use bool type

bool gameOver = false;  // Added to track if the game is over

#define MAX_PLAYERS 10

typedef struct node {
    int data;
    char playerSymbols[MAX_PLAYERS + 1];  // Added to represent the players on the board
    struct node* rlink;
    struct node* llink;
} NODE;

NODE* squares[100];

typedef struct player { // structure to represent a player
    int id;
    NODE* position;
} PLAYER;

PLAYER* winner = NULL;  // Added to track the winner

NODE* createNode(int data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    memset(newNode->playerSymbols, ' ', MAX_PLAYERS);  // Initialize player symbols as empty
    newNode->playerSymbols[MAX_PLAYERS] = '\0';  // Null-terminate the string
    newNode->rlink = NULL;
    newNode->llink = NULL;
    return newNode;
}

// function to create the board
NODE* createTable(NODE* head) {
    int i;
    NODE* p = head;
    for (i = 100; i > 0; i--) {
        NODE* temp = createNode(i);
        p->rlink = temp;
        temp->llink = p;
        p = p->rlink;
        squares[i - 1] = p;  // Update the squares array
    }
    return head;
}

// each player is a pointer to the head of the board (i.e., pointing to position 1)
NODE* createPlayer(NODE* head) {
    while (head->rlink != NULL) {
        head = head->rlink;
    }
    NODE* player = head;
    return player;
}

// function to display the board
void displayBoard(NODE* head, int no_of_players) {
    printf("\t\t**********SNAKE AND LADDER GAME**********\n\n");
    printf("\tSnakes:-46 to 9,\t 77 to 23,\t 99 to 1\n\tLadder:-14 to 36,\t 43 to 81,\t 71 to 98\n\n");
    NODE* p = head->rlink; // Added to skip the head node
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("[%s%-2d]\t", p->playerSymbols, p->data);// Added player symbols to the output
            p = p->rlink;
        }
        printf("\n\n");
    }
}


// function for rolling the die
// returns a random number between 1 and 6
int randomDie() {
    int rem;
    do {
        rem = rand() % 7;
    } while (rem == 0);
    return rem;
}

// function to decide the dice played in real life and enter that number
int rollPhysicalDie() {
    int userInput;
    printf("Enter the number rolled on the physical die (1-6): ");
    scanf("%d", &userInput);

    // Validate the input
    if (userInput < 1 || userInput > 6) {
        printf("Invalid input. Please enter a number between 1 and 6.\n");
        return rollPhysicalDie(); // Recursive call to get valid input
    }

    return userInput;
}

// function to update player's position on the board after rolling the die
void movePlayer(PLAYER* player, int steps) {
    NODE* currentSquare = player->position;

    // Clear the player's symbol from the current square
    currentSquare->playerSymbols[player->id - 1] = ' ';

    // Move the player forward by 'steps' squares
    for (int i = 0; i < steps; i++) {
        if (currentSquare->llink != NULL) {
            currentSquare = currentSquare->llink;
        } else {
            // The player has reached the end of the board
            break;
        }
    }

    // Update the player's position and set the player symbol on the new square
    player->position = currentSquare;
    currentSquare->playerSymbols[player->id - 1] = '@' + player->id;  // Use unique symbols for each player
    if (player->position->data == 100) {
        gameOver = true;
        winner = player;
    }
}


// Function to check if the player has landed on a snake or ladder and update the position
void checkSnakeOrLadder(PLAYER* player) {
    NODE* currentSquare = player->position;
    int currentSquareNumber = currentSquare->data;

    // Check if the player has landed on a snake or ladder
    switch (currentSquareNumber) {
        case 46:
            currentSquare->playerSymbols[player->id - 1] = ' ';  // Clear the player's symbol from the old square
            currentSquare = squares[8];
            break;
        case 77:
            currentSquare->playerSymbols[player->id - 1] = ' ';  // Clear the player's symbol from the old square
            currentSquare = squares[22];
            break;
        case 99:
            currentSquare->playerSymbols[player->id - 1] = ' ';  // Clear the player's symbol from the old square
            currentSquare = squares[0];
            break;
        case 14:
            currentSquare->playerSymbols[player->id - 1] = ' ';  // Clear the player's symbol from the old square
            currentSquare = squares[35];
            break;
        case 43:
            currentSquare->playerSymbols[player->id - 1] = ' ';  // Clear the player's symbol from the old square
            currentSquare = squares[80];
            break;
        case 71:
            currentSquare->playerSymbols[player->id - 1] = ' ';  // Clear the player's symbol from the old square
            currentSquare = squares[97];
            break;
    }

    // Update the player's position and set the player symbol on the new square
    player->position = currentSquare;
    currentSquare->playerSymbols[player->id - 1] = '@' + player->id;  // Use unique symbols for each player
}


int main() {
    NODE* head = (NODE*)malloc(sizeof(NODE));
    head = createTable(head);
    char ch;
    int rem;

    // array of player structures to represent the players
    PLAYER players[MAX_PLAYERS];
    int no_of_players;

    // input the number of players
    do {
        printf("Enter the number of players (max no. of players is %d): ", MAX_PLAYERS);
        scanf("%d", &no_of_players);
    } while (no_of_players > MAX_PLAYERS);

    // add the players to the players array
    for (int k = 0; k < no_of_players; k++) {
        players[k].id = k + 1;  // Player IDs start from 1
        players[k].position = createPlayer(head);
    }

    while (1) {
        rem = rollPhysicalDie();
        printf("Press enter to roll the dice\n");
        getchar();
        printf("You got %d\n", rem);
        if (rem == 6) {
            displayBoard(head, no_of_players);
            break;
        }
    }

    while (1) {
        for (int k = 0; k < no_of_players; k++) {
            rem = rollPhysicalDie();
            printf("Press enter to roll the dice for Player %d\n", players[k].id);
            getchar();
            printf("Player %d got %d\n", players[k].id, rem);
            movePlayer(&players[k], rem);
            checkSnakeOrLadder(&players[k]);  // Check for snake or ladder after moving the player
            if (gameOver) {
                printf("Player %d has won the game!\n", winner->id);
                printf("Do you want to start a new game? (y/n)\n");
                scanf(" %c", &ch);  // Added a space before %c to consume the newline character
                if (ch == 'n') {
                    return 0;  // Exit the program
                } else {
                    // Reset the game
                    gameOver = false;
                    winner = NULL;
                    for (int i = 0; i < no_of_players; i++) {
                        players[i].position = createPlayer(head);
                    }
                    break;  // Break the inner loop to start a new game
                }
            }
        }

        displayBoard(head, no_of_players);

        printf("Do you wish to continue? (y/n)\n");
        scanf(" %c", &ch);  // Added a space before %c to consume the newline character
        if (ch == 'n') {
            break;
        }
    }

    // Free allocated memory before exiting the program
    free(head);
    return 0;
}
