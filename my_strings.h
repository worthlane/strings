#include <string.h>
#include <stdio.h>

static const int LEN = 100;

int MyPuts(const char* string);

char* MyStrchr(const char* string, int symbol);

size_t MyStrlen(const char* string); // done

char* MyStrcpy(char* dest, const char* source);

char* MyStrncpy(char* dest, const char* source, size_t limit);

char* MyStrcat(char* dest, const char* source);

char* MyStrncat (char* dest, const char* source, size_t limit);

char* MyFgets(char* string, int num, FILE* stream); // done

char* MyStrdup(const char* string);

ssize_t MyGetline(char** lineptr, size_t* n, FILE* stream); // done

