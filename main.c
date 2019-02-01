#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 256

struct node {
    int occurance;
    int character;
    struct node *next;
    struct node *left;
    struct node *right;
};

struct listNode {
    int data;
    struct listNode *next;
};

/* Function Declarations */
void insertSorted(struct node **head, int occur, int chara);
struct node *combineNodes(struct node *left, struct node *right);
void insertNodeSorted(struct node **headPtr, struct node **toAdd);
void removeNode(struct node **head, int character);
void printList(struct node *head);
int **createHuffmanCode(int **huffmanCodes, struct node *head);
int **huffmanCodeHelper(int **huffmanCodes, struct node *cur, struct node *prev, int *code, int depth);

int main(int argc, char *argv[]) {

    FILE *inFile;
    int *hTable;
    int *huffmanCodes[MAX_CHAR];
    int curChar, i, j;
    struct node *head, *temp;

    head = NULL;

    inFile = fopen(argv[1], "r");
    hTable = (int *)calloc(MAX_CHAR, sizeof(int));

    for (i=0; i<MAX_CHAR; i++)
         huffmanCodes[i] = (int *)calloc(MAX_CHAR, sizeof(int));

    while ((curChar = fgetc(inFile)) != EOF) {
        hTable[curChar] += 1;
    }

    for(i=0; i<MAX_CHAR; i++) {
        if (hTable[i]) {
            insertSorted(&head, hTable[i], i);
        }
    }

    while(head->next != NULL) {
        temp = combineNodes(head, head->next);

        removeNode(&head, head->character);
        removeNode(&head, head->character);

        insertNodeSorted(&head, &temp);
    }

    createHuffmanCode(huffmanCodes, head);

    for(i=0; i<MAX_CHAR; i++) {
        if (huffmanCodes[i][0] != 0) {
            printf("0x%02x: ", i);
            /********* POSSIBLE TROUBLE ********/
            for(j=0; huffmanCodes[i][j]!=0; j++) {
                printf("%c", huffmanCodes[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}

int **createHuffmanCode(int **huffmanCodes, struct node *head) {
    int *code;
    if(head == NULL) {
        code = (int *)calloc(MAX_CHAR, sizeof(int));
        return huffmanCodes;
    }
    code = (int *)calloc(MAX_CHAR, sizeof(int));
    return huffmanCodeHelper(huffmanCodes, head, NULL, code, 0);
}

int **huffmanCodeHelper(int **huffmanCodes, struct node *cur, struct node *prev, int *code, int depth) {
    if(cur->left == NULL && cur->right == NULL) {
        int i;
        i=0;
        if (prev == NULL)
            return huffmanCodes;
        while(i < depth) {
          huffmanCodes[cur->character][i] = code[i];
          i += 1;
        }
    } else if (cur->left && cur->right) {
        code[depth] = '0';
        huffmanCodes = huffmanCodeHelper(huffmanCodes, cur->left, cur, code, depth+1);
        code[depth] = '1';
        huffmanCodes = huffmanCodeHelper(huffmanCodes, cur->right, cur, code, depth+1);
    }
    return huffmanCodes;
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
    while(list->next != NULL && list->next->occurance <= occur) {
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
    while(list->next != NULL && list->next->occurance < (*toAdd)->occurance) {
        position += 1;
        list = list -> next;
    }

    temp = list->next;
    list->next = *toAdd;
    list->next->next = temp;

    return;
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
