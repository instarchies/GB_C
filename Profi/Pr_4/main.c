#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//выолнил одно задание ибо не успеваю пока что, даже отсрочку взял этой практической ((
#define STACK_SIZE 100
struct Stack {
    int top;
    char items[STACK_SIZE];
};

void initialize(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == STACK_SIZE - 1;
}

void push(struct Stack *s, char c) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = c;
}

char pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

int precedence(char op) {
    switch(op) {
        case '^':
            return 3;
        case '&':
        case '|':
            return 2;
        case '(':
            return 1;
        default:
            return 0;
    }
}

void infixToPostfix(char *exp) {
    struct Stack s;
    initialize(&s);
    int i, k;

    for (i = 0, k = -1; exp[i]; ++i) {
        if (isalnum(exp[i]))
            exp[++k] = exp[i];
        else if (exp[i] == '(')
            push(&s, exp[i]);
        else if (exp[i] == ')') {
            while (!isEmpty(&s) && s.items[s.top] != '(')
                exp[++k] = pop(&s);
            if (!isEmpty(&s) && s.items[s.top] != '(') {
                printf("Invalid Expression\n");
                exit(EXIT_FAILURE);
            } else
                pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(exp[i]) <= precedence(s.items[s.top]))
                exp[++k] = pop(&s);
            push(&s, exp[i]);
        }
    }

    while (!isEmpty(&s))
        exp[++k] = pop(&s);

    exp[++k] = '\0';
}

int main() {
    char exp[100];
    printf("Enter infix expression: ");
    fgets(exp, sizeof(exp), stdin);

    char trimmed_exp[100];
    int j = 0;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] != ' ' && exp[i] != '\n')
            trimmed_exp[j++] = exp[i];
    }
    trimmed_exp[j] = '\0';

    infixToPostfix(trimmed_exp);
    printf("Postfix expression: %s\n", trimmed_exp);

    return 0;
}
