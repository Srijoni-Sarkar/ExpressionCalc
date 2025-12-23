#include <stdio.h>
#include <ctype.h>


void initStack();
void push(char);
char pop();
char peek();
int isEmpty();


int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    initStack();   
    int k = 0;
    int prevIsOperator = 1;

    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];

        if (ch == ' ')
            continue;

       
        if (ch == '-' && prevIsOperator) {
            postfix[k++] = ch; 
            i++;
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i];
                i++;
            }
            i--;
            postfix[k++] = ' '; 
            prevIsOperator = 0;
            continue;
        }

     
        if (isdigit(ch)) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i];
                i++;
            }
            i--;
            postfix[k++] = ' ';
            prevIsOperator = 0;
        }
        else if (ch == '(') {
            push(ch);
            prevIsOperator = 1;
        }
        else if (ch == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            pop(); 
            prevIsOperator = 0;
        }
        else { 
            while (!isEmpty() && precedence(peek()) >= precedence(ch)) {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            push(ch);
            prevIsOperator = 1;
        }
    }

    
    while (!isEmpty()) {
        postfix[k++] = pop();
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';
}

int evalPostfix(char postfix[]) {
    int stack[100];
    int top = -1;

    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];

        if (ch == ' ') continue;

       
        if (isdigit(ch) || (ch == '-' && isdigit(postfix[i+1]))) {
            int num = 0;
            int sign = 1;

            if (ch == '-') {
                sign = -1;
                i++;
            }

            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--; 
            stack[++top] = num * sign;
        }
        else { 
            int b = stack[top--];
            int a = stack[top--];

            switch (ch) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        }
    }

    return stack[top];
}