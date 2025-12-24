#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

/* ---------- STACK FOR OPERATORS ---------- */
char opStack[MAX];
int opTop = -1;

void pushChar(char ch) {
    if (opTop == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    opStack[++opTop] = ch;
}

char popChar() {
    if (opTop == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return opStack[opTop--];
}

char topChar() {
    return opStack[opTop];
}

int isStackEmpty() {
    return opTop == -1;
}

/* ---------- STACK FOR OPERANDS ---------- */
int valStack[MAX];
int valTop = -1;

void pushValue(int x) {
    valStack[++valTop] = x;
}

int popValue() {
    return valStack[valTop--];
}

/* ---------- INFIX TO POSTFIX ---------- */
int getPrecedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

int isOp(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void convertInfixToPostfix(char infix[], char postfix[]) {
    int i, pos = 0;
    char symbol;

    for (i = 0; infix[i] != '\0'; i++) {
        symbol = infix[i];

        if (isalnum(symbol)) {
            postfix[pos++] = symbol;
        }
        else if (symbol == '(') {
            pushChar(symbol);
        }
        else if (symbol == ')') {
            while (!isStackEmpty() && topChar() != '(')
                postfix[pos++] = popChar();
            popChar();   // remove '('
        }
        else if (isOp(symbol)) {
            while (!isStackEmpty() &&
                   getPrecedence(topChar()) >= getPrecedence(symbol))
                postfix[pos++] = popChar();
            pushChar(symbol);
        }
    }

    while (!isStackEmpty())
        postfix[pos++] = popChar();

    postfix[pos] = '\0';
}

/* ---------- POSTFIX EVALUATION ---------- */
int evaluatePostfixExpr(char postfix[]) {
    int i, a, b, res;
    char ch;

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        if (isdigit(ch)) {
            pushValue(ch - '0');
        }
        else if (isOp(ch)) {
            b = popValue();
            a = popValue();

            switch (ch) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^':
                    res = 1;
                    for (int j = 0; j < b; j++)
                        res *= a;
                    break;
            }
            pushValue(res);
        }
    }
    return popValue();
}

/* ---------- MAIN FUNCTION ---------- */
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter Infix Expression (single-digit operands only): ");
    scanf("%s", infix);

    convertInfixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    int ans = evaluatePostfixExpr(postfix);
    printf("Evaluation Result: %d\n", ans);

    return 0;
}
