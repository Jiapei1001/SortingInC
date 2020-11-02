#include <stdio.h>

// LIFO

#define MAX_ELEMENTS 15

int stack[MAX_ELEMENTS] = {0};
// Head always points to the next empty spot
int head  = 0;

void push(int i) {
  if (head < MAX_ELEMENTS) {
    stack[head++] = i;
  } else {
    printf("Stack is full!!!!\n\n");
  }
}

int pop() {
  if (head > 0) {
    return stack[--head];
  } else {
    printf("Stack is empty!!\n\n");
    return -1; 
  }
}

void printStack() {
  int i;
  for (i = MAX_ELEMENTS - 1; i >= 0; i--) {
    printf("[%d]", stack[i]);
    if (i == head) {
      printf("<---");
    }
    printf("\n");
  }
}

int main() {

  printStack();
  printf("\n=====================\n");
  push(42);
  printStack();
  printf("\n=====================\n");
  int val = pop();
  printStack();
  printf("\n=====================\n");
  printf("popped value: %d\n", val);

  printf("\n=====================\n");

  int i;
  for (i = 0; i < MAX_ELEMENTS + 1; i++) {
    push(i); 
  }

  printStack();

  for (i = 0; i < 25; i++) {
    int foo = pop();
    printf("popped value: %d\n", foo);
  }

  printStack();
  
}
