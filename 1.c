#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYERS 10

typedef struct node {
    int data;
    struct node* rlink;
    struct node* llink;
} NODE;

NODE* createNode(int data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->rlink = NULL;
    newNode->llink = NULL;
    return newNode;
}

NODE* createTable(NODE* head) {
    int i;
    NODE* p = head;
    for (i = 100; i > 0; i--) {
        NODE* temp = createNode(i);
        p->rlink = temp;
        temp->llink = p;
        p = p->rlink;
    }
    return head;
}

NODE* createPlayer(NODE* head) {
    while (head->rlink != NULL) {
        head = head->rlink;
    }
    NODE* player = head;
    return player;
}

void displayBoard(NODE* head) {
    printf("\t\t**********SNAKE AND LADDER GAME**********\n\n");
    printf("\tSnakes:-46 to 9,\t 77 to 23,\t 99 to 1\n\tLadder:-14 to 36,\t 43 to 81,\t 71 to 98\n\n");
    NODE* p = head->rlink;
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%-4d\t", p->data);
            p = p->rlink;
        }
        printf("\n\n");
    }
}

void movePlayer(NODE** player, int steps) {
    NODE* currentSquare = *player;
    for (int i = 0; i < steps; i++) {
        if (currentSquare->llink != NULL) {
            currentSquare = currentSquare->llink;
        } else {
            break;
        }
    }
    *player = currentSquare;
}

void displayPlayerPositions(NODE** players, int no_of_players) {
    printf("Player Positions:\n");
    for (int i = 0; i < no_of_players; i++) {
        if (players[i]->data < 100) {
            printf("Player %d: Square %d\n", i + 1, players[i]->data);
        } else {
            printf("Player %d: Square 100\n", i + 1);
        }
    }
}

int findLeadingPlayer(NODE** players, int no_of_players) {
    int leadingPlayer = 0;
    int leadingPosition = players[0]->data;

    for (int i = 1; i < no_of_players; i++) {
        if (players[i]->data > leadingPosition) {
            leadingPlayer = i;
            leadingPosition = players[i]->data;
        }
    }

    return leadingPlayer;
}

int checkForWinner(NODE** players, int no_of_players) {
    for (int i = 0; i < no_of_players; i++) {
        if (players[i]->data >= 100) {
            return i;
        }
    }
    return -1;
}

int main() {
    NODE* head = (NODE*)malloc(sizeof(NODE));
    head = createTable(head);
    char ch;
    int rem;

    NODE* players[MAX_PLAYERS];
    int no_of_players;

    do {
        printf("Enter the number of players (max no. of players is %d): ", MAX_PLAYERS);
        scanf("%d", &no_of_players);
    } while (no_of_players > MAX_PLAYERS);

    for (int k = 0; k < no_of_players; k++) {
        players[k] = createPlayer(head);
    }

    int current_player = 0;

    while (1) {
        printf("Press enter to roll the dice for Player %d\n", current_player + 1);
        getchar();
        rem = rand() % 6 + 1;
        printf("Player %d got %d\n", current_player + 1, rem);
        movePlayer(&players[current_player], rem);
        displayBoard(head);
        displayPlayerPositions(players, no_of_players);

        if (rem == 6) {
            printf("Yay, Player %d gets another try!\n", current_player + 1);
        } else {
            int winner = checkForWinner(players, no_of_players);
            if (winner != -1) {
                printf("Player %d has won the game!\n", winner + 1);
                break;
            }
            current_player = (current_player + 1) % no_of_players;
        }

        printf("Do you wish to continue? (y/n): ");
        scanf(" %c", &ch);
        if (ch == 'n') {
            break;
        }
        if (ch == 'y') {
            fflush(stdin);
        }
    }
    return 0;
}
