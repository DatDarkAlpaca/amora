#include "common.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning(push, 0)

#define INPUT_BUFFER_MAX_SIZE 32
#define INPUT_BUFFER_MAX_SIZE_STR "32"

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

void flush()
{
    int c;
    do {
        c = getchar();
    } while (!isalpha(c));
}

void wait_press()
{
    int _ = _getch();
}

HEAP_ALLOCATED char* get_input()
{
    char* buffer = (char*)malloc(sizeof(char) * INPUT_BUFFER_MAX_SIZE);
    int result = scanf(" %" INPUT_BUFFER_MAX_SIZE_STR "[^\n]", buffer);
    if (!result)
        return "";

    return buffer;
}

void clear_input(HEAP_ALLOCATED char* input)
{
    free(input);
}

unsigned int get_input_number()
{
    int buffer;
    int result = scanf("%d", &buffer);

    if (!result)
        return (unsigned int)INVALID_NUMBER;

    return (unsigned int)buffer;
}

#pragma warning(pop)