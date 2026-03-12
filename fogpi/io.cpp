#include "io.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int get_int()
{
    int x;
    int result;

    result = scanf("%d", &x);

    if (result == EOF)
    {
        exit(1);
    }
    else if (result == 0)
    {
        printf("Invalid input. Please enter an integer: ");
        clear_input_buffer();
        x = get_int(); // Try again recursively
    }
    else
    {
        clear_input_buffer();
    }

    return x;
}

char get_char()
{
    char c;

    int result = scanf("%c", &c);

    if (result == EOF)
    {
        exit(1);
    }
    else if (result == 0)
    {
        printf("Invalid input. Please enter an char: ");
        clear_input_buffer();
        c = get_char();
    }
    else
    {
        clear_input_buffer();
    }

    return c;
}

char *get_string()
{
    char buffer[1024]; // Adjust the buffer size as needed
    char *input = NULL;
    int length;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        length = strlen(buffer);

        // Remove the newline character if present
        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
        }

        // Allocate memory for the input string and copy the buffer
        input = (char *)malloc(length);
        if (input != NULL)
        {
            strcpy(input, buffer);
        }

        return input;
    }

    return input;
}

float get_float()
{
    float x;
    int result;

    result = scanf("%f", &x);

    if (result == EOF)
    {
        exit(1);
    }
    if (result == 0)
    {
        printf("Invalid input. Please enter a float: ");
        clear_input_buffer();
        x = get_float(); // Try again recursively
    }
    else
    {
        clear_input_buffer();
    }

    return x;
}

int request_int(const char *_message)
{
    printf("%s : ", _message);
    return get_int();
}

float request_float(const char *_message)
{
    printf("%s : ", _message);
    return get_float();
}

char request_char(const char *_message)
{
    printf("%s : ", _message);
    return get_char();
}

char *request_string(const char *_message)
{
    printf("%s : ", _message);
    return get_string();
}

int random_int(int _min, int _max)
{
    if (_max < _min)
        return _min;
    
    if (_min == _max)
        return _min;
    
    int range = 1 + _max - _min;

    return _min + rand() % range;
}

float random_float(float _min, float _max)
{
    if (_max > _min)
    {
        float random = ((float)rand()) / (float)RAND_MAX;
        float range = _max - _min;
        return (random * range) + _min;
    }

    if (_min == _max)
        return _min;

    return random_float(_max, _min);
}