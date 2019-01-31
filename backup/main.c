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

struct node *insertSorted(struct node *head, int occur, int chara);
struct node *combineNodes(struct node *left, struct node *right);
struct node *insertNodeSorted(struct node *head, struct node* toAdd);
void printList(struct node *head);

int main(int argc, char *argv[]) {

    FILE *inFile;
    int *hTable;
    int curChar, i;
    struct node *head, *list, *temp;

    head = NULL;

    inFile = fopen(argv[1], "r");
    hTable = (int *)calloc(MAX_CHAR, sizeof(char));

    while ((curChar = fgetc(inFile)) != EOF) {
        hTable[curChar] += 1;
    }

    for(i=0; i<MAX_CHAR; i++) {
        if (hTable[i]) {
            head = insertSorted(head, hTable[i], i);
        }
    }

    list = head;
    while (list->next != NULL) {
        temp = combineNodes(list, list->next);
        list = list->next->next;
        list = insertNodeSorted(list, temp);
    }


    return 0;
}

struct node *insertSorted(struct node *head, int occur, int chara) {

    struct node *list, *newNode, *temp;

    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->occurance = occur;
    newNode->character = chara;
    newNode->next = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    if(head == NULL) {
        return newNode;
    }

    list = head;
    while(list->next != NULL && list->next->occurance < occur) {
        list = list -> next;
    }
    temp = list->next;
    list->next = newNode;
    list->next->next = temp;

    return head;

}

struct node *insertNodeSorted(struct node *head, struct node* toAdd) {

    struct node *list, *temp;

    if(head == NULL) {
        return NULL;
    }

    list = head;
    while(list->next != NULL && list->next->occurance < toAdd->occurance) {
        list = list -> next;
    }
    temp = list->next;
    list->next = toAdd;
    list->next->next = temp;

    return head;

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

void printList(struct node *head) {

    while(head != NULL) {
        printf("%c with %d occurance\n", head->character, head->occurance);
        head = head->next;
    }

}