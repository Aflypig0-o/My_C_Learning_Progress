#include <stdio.h>
#include "stack.h"
#include <string.h>

bool is_balanced(const char* str)
{
    Stack s;
    initStack(&s);
    if(str == NULL) {
        return true; // An empty string is considered balanced
    }
    for(int i =0;str[i] != '\0'; ++i)
    {
        char c =str[i];
        if(c == '(' || c == '{' || c == '[') {
            push(&s, c);
        } else if(c == ')' || c == '}' || c == ']') {
            if(isEmpty(&s)) {
                return false; // Unmatched closing bracket
            }
            char top;
            pop(&s, &top);
            if((c == ')' && top != '(') ||
               (c == '}' && top != '{') ||
               (c == ']' && top != '[')) {
                return false; // Mismatched brackets
            }
        }
    }
    return isEmpty(&s); // If the stack is empty, all brackets were matched
}

int main()
{
    char input[100];
    printf("Enter a string of parentheses: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove the newline character
    if(is_balanced(input)) {
        printf("The parentheses are balanced.\n");
    } else {
        printf("The parentheses are not balanced.\n");
    }
}