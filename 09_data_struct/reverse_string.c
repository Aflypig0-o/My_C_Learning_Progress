#include <stdio.h>
#include "stack.h"`
#include <string.h>

void reverse_string(char* str)
{
    Stack s;
    initStack(&s);
    for(int i = 0; str[i] != '\0'; ++i)
    {
        push(&s, str[i]);
    }
    for(int i = 0;str[i] != '\0'; ++i)
    {
        char c;
        pop(&s, &c);
        str[i] = c;
    }
}  

int main()
{
    char input[100];
    printf("Enter a string to reverse: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove the newline character
    reverse_string(input);
    printf("Reversed string: %s\n", input);
    return 0;
}