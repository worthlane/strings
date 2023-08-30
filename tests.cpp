#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_strings.h"
#include "colorlib.h"
#include "tests.h"

static const char* TEST_FILE = "TestFile.txt";

void MyGetlineTest()
{
    PrintCyanText(stderr, "TESTING MYGETLINE--------------------------------------\n", "");

    FILE* fp1 = fopen(TEST_FILE, "r");
    FILE* fp2 = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyGetlineTestOne(&test_number, &incorrect, fp1, fp2)) {}

    PrintCyanText(stderr, "END OF TESTING MYGETLINE (%d incorrect)--------------\n\n", incorrect);
}

bool MyGetlineTestOne(int* test_number, int* incorrect, FILE* fp1, FILE* fp2)
{
    (*test_number)++;

    char* line1 = NULL;
    size_t len1 = 0;
    ssize_t read1 = 0;

    char* line2 = NULL;
    size_t len2 = 0;
    ssize_t read2 = 0;

    read1 = MyGetline(&line1, &len1, fp1);
    read2 = getline(&line2, &len2, fp2);

    if (read1 == -1 || read2 == -1)
        return false;

    if (read1 != read2)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                             "FUNCTION: %zu EXPECTED: %zu\n", *test_number, read1, read2);
    }

    if (strncmp(line1, line2, LEN) != 0)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT READ\n"
                             "FUNCTION: %s\nEXPECTED: %s\n", *test_number, line1, line2);
    }
    else
        PrintGreenText(stderr, "TEST %d, CORRECT\n", *test_number);


    free(line1);
    free(line2);

    return true;
}

void MyFgetsTest()
{
    PrintCyanText(stderr, "TESTING MYFGETS---------------------------------\n", "");

    FILE* fp1 = fopen(TEST_FILE, "r");
    FILE* fp2 = fopen(TEST_FILE, "r");

    int test_number = 1;
    int incorrect   = 0;

    while (MyFgetsTestOne(&test_number, &incorrect, fp1, fp2)) {}

    PrintCyanText(stderr, "END OF TESTING MYFGETS (%d incorrect)----------\n\n", incorrect);
}

bool MyFgetsTestOne(int* test_number, int* incorrect, FILE* fp1, FILE* fp2)
{
    char line1[LEN] = "";
    char line2[LEN] = "";

    if (!MyFgets(line1, LEN, fp2)) return false;
    if (!fgets(line2, LEN, fp1)) return false;


    if (strncmp(line1, line2, LEN) != 0)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT READ\n"
                             "FUNCTION: %s\nEXPECTED: %s\n", (*test_number)++, line1, line2);
    }
    else
    {
        PrintGreenText(stderr, "TEST %d, CORRECT\n", (*test_number)++);
    }
    return true;
}

void MyStrlenTest()
{
    PrintCyanText(stderr, "TESTING MYSTRLEN---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 1;
    int incorrect   = 0;

    while (MyStrlenTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRLEN (%d incorrect)----------\n\n", incorrect);
}

bool MyStrlenTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line[LEN] = "";

    if (!fgets(line, LEN, fp)) return false;

    size_t size   = strlen(line);
    size_t mysize = MyStrlen(line);

    if (size != mysize)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT READ\n"
                             "FUNCTION: %zu\nEXPECTED: %zu\n", (*test_number)++, mysize, size);
    }
    else
    {
        PrintGreenText(stderr, "TEST %d, CORRECT\n", (*test_number)++);
    }
    return true;
}

void MyStrdupTest()
{
    PrintCyanText(stderr, "TESTING MYSTRDUP---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 1;
    int incorrect   = 0;

    while (MyStrdupTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRDUP (%d incorrect)----------\n\n", incorrect);
}


bool MyStrdupTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line[LEN] = "";

    if (!fgets(line, LEN, fp)) return false;

    char* dup1 = MyStrdup(line);
    char* dup2 = strdup(line);

    if (strncmp(dup1, dup2, LEN) != 0)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT READ\n"
                             "FUNCTION: %s\nEXPECTED: %s\n", (*test_number)++, dup1, dup2);
    }
    else
    {
        PrintGreenText(stderr, "TEST %d, CORRECT\n", (*test_number)++);
    }
    return true;
}
