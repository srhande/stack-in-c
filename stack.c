#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

// Edit only after this line //

// pop function for stack
Element* pop(Stack* s){
  if(isEmpty(s)) {
    return NULL;
  }
  Element* returnValue = s->elements[s->top];
  s->elements[s->top] = NULL;
  s->top = s->top - 1;
  if(s->dynamic && (currentSize(s) <= s->shrinkFactor * s->capacity) && s->capacity > 1) {
    Element** shrinkArray = (Element**) calloc(s->capacity / 2, sizeof(Element*));
    for(int i = 0; i < s->capacity / 2; i++) {
      shrinkArray[i] = s->elements[i];
    }
    s->capacity = (s->capacity)/2;
    free(s->elements);
    s->elements = shrinkArray;
  }
  return returnValue;
}

// multipop: pop multiple elements from stack
Element** multiPop(Stack* s, int k){
  if(isEmpty(s)) {
    return NULL;
  }
  int popAmount = k;
  if (k > currentSize(s)) {
    popAmount = currentSize(s);
  }
  Element** poppedElementArray = (Element**) calloc(popAmount, sizeof(Element*));
  int index = 0;
  if(k > currentSize(s)) {
    for (int i = 0; i < currentSize(s); i++) {
      poppedElementArray[index] = pop(s);
      index++;
    }
  } else {
      for (int i = 0; i < k; i++) {
        poppedElementArray[index] = pop(s);
        index++;
      }
  } 
  return poppedElementArray;
}

// Utility function: add element for push
// This function is a hint, you may ignore its implementation
void addE(Stack* s, int k, char* v) {

}

// Utility function: expandCapacity for push
// This function is a hint, you may ignore its implementation
void expandCapacity(Stack* s) {

}

// push function for stack
bool push(Stack* s, int k, char* v){
  if(isFull(s) && !(s->dynamic)) {
    return false;
  }
  if(s->dynamic && (currentSize(s) + 1 > s->growthFactor * s->capacity)) {
    Element** newArray = (Element**) calloc(2 * s->capacity, sizeof(Element*));
    for(int i = 0; i < currentSize(s); i++) {
      newArray[i] = s->elements[i];
    }
    s->capacity = 2 * s->capacity;
    free(s->elements);
    s->elements = newArray;
  }
  Element* newElementPointer = (Element*) malloc(sizeof(Element));
  newElementPointer->key = k;
  newElementPointer->value = v;
  s->elements[++(s->top)] = newElementPointer;
  return true;
}

// push unique function for stack
bool pushUnique(Stack* s, int k, char* v){
  if( isEmpty( s ) ) {
    return push(s, k, v);
  }
  Element* topElementPointer = s->elements[s->top];
  if(topElementPointer->key == k && strcmp(topElementPointer->value, v) == 0) {
    return false;
  }
  return push(s, k, v);
}

// reverse the elements in stack
void reverse(Stack* s){
  for(int i = 0; i < currentSize(s) / 2; i++) {
    Element* topElementPointer = s->elements[i];
    s->elements[i] = s->elements[s->top - i];
    s->elements[s->top - i] = topElementPointer;
  }
}

// peek function for stack
Element* peek(Stack* s){
  if(isEmpty(s)) {
    return NULL;
  }
  return s->elements[s->top];
}

// search for element from top of stack
int search(Stack* s, int k, char* v){
  if(isEmpty(s)) {
    return -1;
  }
  for(int i = s->top; i >= 0; i--) {
    Element* elementPointer = s->elements[i];
    if(elementPointer->key == k && strcmp(elementPointer->value, v) == 0) {
      return s->top-i+1; 
    }
  }
  return -1;
}

// get current capacity of stack
int getCapacity(Stack* s){
  return s->capacity;
}

//check if stack is full
bool isFull(Stack* s){
  return !s->dynamic && s->top+1 == s->capacity;
}

// clear the stack
void clear(Stack *s) {
  for(int i = 0; i < s->capacity; i++) {
    free(s->elements[i]);
    s->elements[i] = NULL;
  }
  s->top = -1;
}

// clean the stack
void cleanStack(Stack *s) {
  for(int i = 0; i < s->capacity; i++) {
    free(s->elements[i]);
  }
	free(s->elements);
	free(s);
}

// current size of stack
int currentSize(Stack* s){
  return s->top + 1;
}

// check if stack empty
bool isEmpty(Stack* s){
  return s->top == -1;
}

// Stack with fixed capacity
Stack* makeStack(int cap){
  struct Stack* s = (struct Stack*) malloc( sizeof(struct Stack) );
  s->top = -1;
  s->capacity = cap;
  s->growthFactor = 0;
  s->shrinkFactor = 0;
  s->dynamic = false;
  s->elements = (Element**) calloc(cap, sizeof(Element*));
  return s;
}

// Stack that can grow
Stack* makeStackG(int cap, float growF){
  struct Stack* s = (struct Stack*) malloc( sizeof(struct Stack) );
  s->top = -1;
  s->capacity = cap;
  s->growthFactor = growF;
  s->shrinkFactor = 0;
  s->dynamic = true;
  s->elements = (Element**) calloc(cap, sizeof(Element*));
  return s;
}

// Stack that can grow and shrink
Stack* makeStackGnS(int cap, float growF, float shrinkF){
  struct Stack* s = (struct Stack*) malloc( sizeof(struct Stack) );
  s->top = -1;
  s->capacity = cap;
  s->growthFactor = growF;
  s->shrinkFactor = shrinkF;
  s->dynamic = true;
  s->elements = (Element**) calloc(cap, sizeof(Element*));
  return s;
}
