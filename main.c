#include <stdio.h>
#include <string.h>  

void infixToPostfix(char infix[], char postfix[]);
int evalPostfix(char postfix[]);

int main() {
    char infix[200];
    char postfix[200];

    printf("Enter infix expression: ");
    fgets(infix, 200, stdin);

 
    int len = strlen(infix);
    if (len > 0 && infix[len-1] == '\n') {
        infix[len-1] = '\0';
    }

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);
    printf("Result: %d\n", evalPostfix(postfix));

    return 0;
}