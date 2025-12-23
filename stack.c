#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    int top;
    int capacity;
} Stack;

Stack s;


void initStack() {
    s.capacity = 10;         
    s.top = -1;
    s.data = (char *)malloc(s.capacity * sizeof(char));

    if (s.data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}


void resizeStack() {
    s.capacity *= 2;
    s.data = (char *)realloc(s.data, s.capacity * sizeof(char));

    if (s.data == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
}


void push(char x) {
    if (s.top == s.capacity - 1) {
        resizeStack();   
    }
    s.data[++s.top] = x;
}


char pop() {
    if (s.top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return s.data[s.top--];
}

char peek() {
    if (s.top == -1)
        return '\0';
    return s.data[s.top];
}


int isEmpty() {
    return s.top == -1;
}