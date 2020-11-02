#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

Node* CreateNode(char* data) {
  Node* out = (Node*)malloc(sizeof(Node));
  out->prevNode = NULL;
  out->nextNode = NULL;
  out->data = data;
  return out;
}

// Add node at beginning
Node* AddData(Node* node, char* data) {
  Node* newNode = CreateNode(data);
  node->prevNode = newNode;
  newNode->nextNode = node;
  return newNode; 
}

void printLinkedList(Node* head){

  while(head != NULL){
    printf("%p\tPrevNode: %15p|%20s|\tNextNode: %15p\n", head, head->prevNode, head->data, head->nextNode);
    head = head->nextNode;
  }
}


int main() {
  Node* hermie = CreateNode("Hermie");

  printLinkedList(hermie);

  printf("\n\n");

  Node* head = AddData(hermie, "Sparky");

  printLinkedList(head);

  printf("\n\n");

  Node* fido = AddData(head, "Fido");
  printLinkedList(fido);

  
}
