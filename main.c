#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 255

struct node {
    int occurance;
    int character;
    struct node *next;
    struct node *left;
    struct node *right;
};

/* Function Declarations */
void insertSorted(struct node **head, int occur, int chara);
struct node *combineNodes(struct node *left, struct node *right);
void insertNodeSorted(struct node **headPtr, struct node **toAdd);
void removeNode(struct node **head, int character);
void printList(struct node *head);

int main(int argc, char *argv[]) {

    FILE *inFile;
    int *hTable;
    int curChar, i, lc;
    struct node *head, *temp;

    head = NULL;

    inFile = fopen(argv[1], "r");
    hTable = (int *)calloc(MAX_CHAR, sizeof(int));

    while ((curChar = fgetc(inFile)) != EOF) {
        hTable[curChar] += 1;
    }

    for(i=0; i<MAX_CHAR; i++) {
        if (hTable[i]) {
            insertSorted(&head, hTable[i], i);
        }
    }

    while(head->next != NULL) {
        lc += 1;
        temp = combineNodes(head, head->next);
        
        removeNode(&head, head->character);
        removeNode(&head, head->character);
        
        insertNodeSorted(&head, &temp);
    }
    
    return 0;
}

void insertSorted(struct node **headPtr, int occur, int chara) {

    struct node *list, *newNode, *temp, *head;
    head = *headPtr;

    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->occurance = occur;
    newNode->character = chara;
    newNode->next = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    if(head == NULL) {
        *headPtr = newNode;
        return;
    }

    list = head;
    while(list->next != NULL && list->next->occurance < occur) {
        list = list -> next;
    }
    temp = list->next;
    list->next = newNode;
    list->next->next = temp;

    *headPtr = head;
    return;

}

void insertNodeSorted(struct node **headPtr, struct node **toAdd) {

    struct node *list, *temp, *head;
    int position;

    head = *headPtr;
    
    if(head == NULL) {
        (*headPtr) = *toAdd;
        return;
    }
    if((*toAdd)->occurance <= head->occurance) {
        (*toAdd)->next = head;
        (*headPtr) = *toAdd;
        return;
    }

    list = head;
    while(list->next != NULL && list->next->occurance <= (*toAdd)->occurance) {
        position += 1;
        list = list -> next;
    }

    temp = list->next;
    list->next = *toAdd;
    list->next->next = temp;

    return ;

}


struct node *combineNodes(struct node *left, struct node *right) {
    struct node *newNode;

    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->occurance = left->occurance + right->occurance;
    newNode->character = (left->character < right->character)?
                         (left->character):(right->character);
    newNode->next = NULL;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void removeNode(struct node **head, int character){
    struct node *temp;
    temp = *head;
    
    if (temp->character == character) {
        (*head) = temp->next;
        return;
    }

    while(!(temp->next->character == character)) {
        temp = temp->next;
        if (temp->next == NULL) {
            return;
        }
    }

    temp->next = temp->next->next;
    return;
}

void printList(struct node *head) {

    while(head != NULL) {
        printf("%c with %d occurance\n", head->character, head->occurance);
        head = head->next;
    }

}
