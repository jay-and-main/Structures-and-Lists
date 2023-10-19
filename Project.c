#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* rlink;
    struct node* llink;
}NODE;

NODE* createNode(int data){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->rlink = NULL;
    newNode->llink = NULL;
    return newNode;
}

//  function to create the board
NODE* createTable(NODE* head){
    int i;
    NODE* p=head;
    for (i=100;i>0;i--){
        NODE* temp = createNode(i);
        p->rlink = temp;
        temp->llink = p;
        p = p->rlink;
    }
    return head;
}

// each player is a pointer to the head of the board (ie. pointing to the position 1)
NODE* createPlayer(NODE* head){
    NODE* player = head;
    return player;
}


void displayBoard(NODE* head){
    printf("\t\t**********SNAKE AND LADDER GAME**********\n\n");
    printf("\tSnakes:-46 to 9,\t 77 to 23,\t 99 to 1\n\tLadder:-14 to 36,\t 43 to 81,\t 71 to 98\n\n");
    NODE* p = head->rlink;
    int i,j;
    for (i=0;i<10;i++){
        for (j=0;j<10;j++){
            printf("%-4d\t",p->data);
            p = p->rlink;
        }
        printf("\n\n");
    }
}

// function for rolling the die
// returns a random number between 1 and 6
int rd(){
    int rem;
    do {
        rem = rand() % 7;
    } while (rem == 0);
    return rem;
}
//function to decide the dice played irl and enter that number
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
//function to create a move player function after the die is rolled
void movePlayer(NODE** player, int steps) {
    NODE* currentSquare = *player;

    // Move the player forward by 'steps' squares
    for (int i = 0; i < steps; i++) {
        if (currentSquare->rlink != NULL) {
            currentSquare = currentSquare->rlink;
        } else {
            // The player has reached the end of the board
            break;
        }
    }

    *player = currentSquare;  // Update the player's position
}

int main(){
    NODE* head = (NODE*)malloc(sizeof(NODE));
    head=createTable(head);
    char ch;
    int rem;

    // making an array of pointers to represent the players
    // assuming max no of players is 10

    NODE* players[10];
    int no_of_players;

    // input the number of players
    do {
        printf("Enter the number of players (max no. of players is 10): ");
        scanf("%d",&no_of_players);
    } while (no_of_players>10);

    // add the players to the players array
    for (int k=0; k<no_of_players; k++){
        players[k] = createPlayer(head);
    }

    // assume the index of the player in the players array is the player id

    while(1){
        rem = rd();
        printf("Press enter to roll the dice\n");
        getchar();
        printf("You got %d\n",rem);
        if (rem==6){
            displayBoard(head);
            break;
        }

    }
    while(1){
        rem=rd();
        printf("Press enter to roll the dice\n");
        getchar();
        printf("You got %d\n",rem);
        if (rem==6){
            printf("Yay you get another try!\n");
            continue;
        }
        printf("Do you wish to continue? (y/n)\n");
        scanf("%c",&ch);
        if (ch=='n'){
            break;
        }
        if (ch=='y'){
            fflush(stdin);
        }
    }
    return 0;
}
