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

int rd(){
    int rem;
    do {
        rem = rand() % 7;
    } while (rem == 0);
    return rem;
}

int main(){
    NODE* head = (NODE*)malloc(sizeof(NODE));
    head=createTable(head);
    char ch;
    int rem;
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