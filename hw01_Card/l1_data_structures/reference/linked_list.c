#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node{
   char* data;
   Node* prevNode;
   Node* nextNode;
};

struct list{
        Node* firstNode;
};

typedef struct list List;

//===================================
// Function Prototypes
//===================================

Node* insert(List*, Node*);

Node* removeNode(List*, Node*);

Node* removeElement(List*, char*);

List* create();

void destroy(List*);

Node* createNode();

void destroyNode(Node*);

int contains(List*, Node*);

//===================================

List* create(){
        List* newList = (List*)malloc(sizeof(List));
        newList->firstNode = NULL;
        return newList;
}

Node* createNode(){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = "";
        newNode->prevNode = NULL;
        newNode->nextNode = NULL;
        return newNode;
}


Node* createNodeWithData(char* data){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prevNode = NULL;
        newNode->nextNode = NULL;
        return newNode;

        /* OR:
        Node* newNode = createNode();
        newNode->data = data;
        return newNode;

        */
}

void destroyNode(Node* aNode){
        printf("Destroying node: %s\n", aNode->data);
        aNode->nextNode = NULL;
        aNode->prevNode = NULL;
        aNode->data = NULL;
        free(aNode);
}

/**
  * Removes all elements from the list,
  * deletes them,
  * then deletes/destroys the list.
  */
void destroy(List* list){
        while (list->firstNode != NULL){
                Node* deletedNode = removeNode(list, list->firstNode);
                destroyNode(deletedNode);
        }

        free(list);
}

Node* insert(List* aList, Node *newNode){
        if (aList->firstNode !=NULL){
                // Point the new Node to the first Node
                newNode->nextNode = aList->firstNode;
                // Point it back
                aList->firstNode->prevNode = newNode;
                newNode->prevNode = NULL;
        }
        aList->firstNode = newNode;

        return newNode;
}


Node* removeNode(List *list, Node *aNode){
        if (list->firstNode == aNode){
                list->firstNode = NULL;
                list->firstNode = aNode->nextNode;
        }
        if (aNode->prevNode != NULL){
                aNode->prevNode->nextNode = aNode->nextNode;
        }
        if (aNode->nextNode != NULL){
                aNode->nextNode->prevNode = aNode->prevNode;
        }
        return aNode;
}

Node* removeElement(List *aList, char *data){

        Node *curNode = aList->firstNode;

        while(curNode != NULL){
                if (curNode->data == data){
                        return(removeNode(aList, curNode));
                }
                curNode = curNode->nextNode;
        }

        // Data was not found
        return NULL;
}

void printLinkedList(List *list){

        Node* head = list->firstNode;

        while(head != NULL){
                printf("%p\tPrevNode: %15p|%20s|\tNextNode: %15p\n", head, head->prevNode, head->data, head->nextNode);
                head = head->nextNode;
        }
}

bool contains(List *list, char* data){
        Node *curNode = list->firstNode;

        while(curNode != NULL){
                if (curNode->data == data){
                        return 1;
                }
                curNode = curNode->nextNode;
        }

        // Data was not found
        return 0;
}


void printNode(Node *node){
        printf("Node: %p\t%15s\n", node, node->data);
}

int main(){

        List *list = create();

        Node *head = createNode();
        head->data = "First Node";

        printNode(head);

        printf("\n\nList: ");

        printLinkedList(list);

        insert(list, head);

        printf("\n\nList post-add: \n");

        printLinkedList(list);




        Node *newNode = createNode();
        newNode -> data = "Second Node";
        insert(list, newNode);

        Node *node3 = createNode();
        node3->data = "Third Node";
        insert(list, node3);

        printf("\nprinting the linked list, with 3 nodes recently created: \n");
        printLinkedList(list);

        printf("\n\n");


        destroy(list);
        //printLinkedList(list);
        list = NULL;

        Node *trouble = createNode();
        trouble -> data = "Shenanigans";
        insert(list, trouble);
        printLinkedList(list);

/*	printf("\n-------\n");

        printf("I'm freeing node3...\n");
        free(node3);
        printLinkedList(list);

        Node *node4 = createNode();
        node4 -> data = "Fourth Node";
        printNode(node4);


        printLinkedList(list);

        printNode(node3);
*/

/*	removeNode(newNode);
        printLinkedList(list);

        printf("\n-------\n");

        insert(list, newNode);

        printLinkedList(list);


        printf("\n-------\n");


        Node *goneNode = removeElement(list, "First Node");

        printLinkedList(list); */

        // Should I use destroy() (the function I wrote) or free()?
        // I should use destroy(), but for demo purposes right now,
        // I'm going to use free().
/*	free(head);
        free(newNode);
        free(node3);

        free(list);

        // Playing around with freeing memory and re-using it.

        printf("The nodes are free!!\n\n");
        // I shouldn't be able to do this!!
        printLinkedList(list); */

        // I shouldn't be

/*	List *list2 = create();

        Node *head2 = createNode();
        head2->data = "The first node in list2";

        insert(list2, head2);

        printf("The list should be gone\n\n");

        printLinkedList(list2); */

}

