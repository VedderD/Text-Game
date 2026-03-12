#pragma once
#include <string.h>

// these helper functions are writen in
// c style but modified for cpp projects

int     get_int();
float   get_float();
char    get_char();
char*   get_string();

int     request_int(const char* _message);
float   request_float(const char* _message);
char    request_char(const char* _message);
char*   request_string(const char* _message);

int     random_int(int _min, int _max);
float   random_float(float _min, float _max);