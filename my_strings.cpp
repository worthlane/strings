#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_strings.h"

int MyPuts(const char* string)
{
    assert(string);

    while (*string)
        if (putchar(*(string++)) == EOF) return EOF;

    return putchar('\n');
}

char* MyStrchr(const char* string, int symbol)
{
    assert(string);

    do
        if (*string == symbol) return (char* ) (string);
    while (*(string++));

    return NULL;
}

size_t MyStrlen(const char* string)
{
    assert(string);

    size_t len = 0;

    while (*(string++))
        len++;

    return len;
}

char* MyStrcpy(char* dest, const char* source)
{
    assert(source);
    assert(dest);
    assert(source != dest);

    int cnt = 0;

    while (source[cnt++])
        dest[cnt] = source[cnt];

    dest[cnt] = '\0';

    return dest;
}

char* MyStrncpy(char* dest, const char* source, size_t limit)
{
    assert(dest);
    assert(source);
    assert(source != dest);

    int cnt = 0;

    while (source[cnt] && cnt < limit)
    {
        dest[cnt] = source[cnt];
        cnt++;
    }

    while (cnt < limit)
        dest[cnt++] = 0;

    return dest;
}

char* MyStrcat(char* dest, const char* source)
{
    assert(dest);
    assert(source);
    assert(source != dest);

    int cnt = 0;
    while (dest[cnt++]) {}

    cnt--;

    while (*(source))
        dest[cnt++] = *(source++);

    dest[cnt] = 0;

    return dest;
}

char* MyStrncat (char* dest, const char* source, size_t limit)
{
    assert(dest);
    assert(source);
    assert(source != dest);

    int cnt = 0;
    while (dest[cnt++]) {}

    cnt--;

    while (*(source) && limit--)
        dest[cnt++] = *(source++);

    dest[cnt] = 0;

    return dest;
}

char* MyFgets(char* string, int num, FILE* stream)
{
    assert(string);

    int ch = 1;
    int cnt = 0;
    num--;

    while(ch && ch != EOF && ch != '\n' && num--)
    {
        if ((ch = fgetc(stream)) == EOF) return NULL;
        string[cnt++] = ch;
    }
    string[cnt] = '\0';

    return string;
}

char* MyStrdup(const char* string)
{
    char* duplicate = (char*) malloc((strlen(string) + 1) * sizeof(char));
    if (duplicate == NULL)
        return NULL;

    int cnt = 0;

    while (string[cnt])
    {
        duplicate[cnt] = string[cnt];
        cnt++;
    }

    return duplicate;
}

ssize_t MyGetline(char** lineptr, size_t* n, FILE* stream)
{
    assert(lineptr);
    assert(n);
    assert(stream);

    ssize_t count = 0;
    static const size_t step = 8;
    size_t size = step;

    if (*lineptr == NULL)
    {
        *lineptr = (char* ) calloc(size, sizeof(char));
        if (*lineptr == NULL)
            return -1;
        else
            *n = size;
    }

    int c = 1;

    while ((c = fgetc(stream)) != EOF)
    {
        if (count >= *n)
        {
            size += step;
            char* new_ptr = (char*) realloc(*lineptr, size);
            if (new_ptr == NULL)
                return -1;
            else
            {
                *lineptr = new_ptr;
                *n = size;
            }
        }

        (*lineptr)[count++] = c;

        if (c == '\0' || c == '\n')
            break;
    }

    (*lineptr)[count] = '\0';

    if (c == EOF) return -1;

    return count;
}
