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

    PrintCyanText(stderr, "END OF TESTING MYGETLINE (%d incorrect, %d tested)--------------\n\n",
                                                     incorrect,    test_number);

    fclose(fp1);
    fclose(fp2);
}

bool MyGetlineTestOne(int* test_number, int* incorrect, FILE* fp1, FILE* fp2)
{
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
                             "FUNCTION: %zu EXPECTED: %zu\n", ++(*test_number), read1, read2);
        free(line1);
        free(line2);
        return true;
    }

    if (strncmp(line1, line2, LEN) != 0)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT READ\n"
                             "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), line1, line2);
    }
    else
        ++(*test_number);


    free(line1);
    free(line2);

    return true;
}

void MyFgetsTest()
{
    PrintCyanText(stderr, "TESTING MYFGETS---------------------------------\n", "");

    FILE* fp1 = fopen(TEST_FILE, "r");
    FILE* fp2 = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyFgetsTestOne(&test_number, &incorrect, fp1, fp2)) {}

    PrintCyanText(stderr, "END OF TESTING MYFGETS (%d incorrect, %d tested)----------\n\n",
                                                   incorrect,    test_number);

    fclose(fp1);
    fclose(fp2);
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
                             "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), line1, line2);
    }
    else
    {
        (*test_number)++;
    }
    return true;
}

void MyStrlenTest()
{
    PrintCyanText(stderr, "TESTING MYSTRLEN---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrlenTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRLEN (%d incorrect, %d tested)----------\n\n",
                                                    incorrect,    test_number);

    fclose(fp);
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
                             "FUNCTION: %zu\nEXPECTED: %zu\n", ++(*test_number), mysize, size);
    }
    else
    {
        (*test_number)++;
    }
    return true;
}

void MyStrdupTest()
{
    PrintCyanText(stderr, "TESTING MYSTRDUP---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrdupTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRDUP (%d incorrect, %d tested)----------\n\n",
                                                    incorrect,    test_number);

    fclose(fp);
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
                             "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), dup1, dup2);
    }
    else
    {
        (*test_number)++;
    }

    free(dup1);
    free(dup2);

    return true;
}


void MyPutsTest()
{
    PrintCyanText(stderr, "TESTING MYPUTS---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyPutsTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYPUTS (%d incorrect, %d tested)----------\n\n",
                                                  incorrect,    test_number);

    fclose(fp);
}



bool MyPutsTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line[LEN] = "";

    if (!fgets(line, LEN, fp)) return false;

    PrintCyanText(stdout, "TEST %d:\n", ++(*test_number));

    int done1 = MyPuts(line);
    int done2 = puts(line);

    if (done1 != done2)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                             "FUNCTION: %d\nEXPECTED: %d\n", *test_number, done1, done2);
    }
    return true;
}



void MyStrcpyTest()
{
    PrintCyanText(stderr, "TESTING MYSTRCPY---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrcpyTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRCPY (%d incorrect, %d tested)----------\n\n",
                                                    incorrect,    test_number);

    fclose(fp);
}



bool MyStrcpyTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line[LEN]   = "";
    char mycopy[LEN] = "";
    char copy[LEN]   = "";

    if (!fgets(line, LEN, fp)) return false;

    MyStrcpy(mycopy,line);
    strcpy(copy, line);

    if (strncmp(copy, mycopy, LEN) != 0)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                             "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), mycopy, copy);
    }
    else
    {
        (*test_number)++;
    }
    return true;
}


void MyStrncpyTest()
{
    PrintCyanText(stderr, "TESTING MYSTRNCPY---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrncpyTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRNCPY (%d incorrect, %d tested)----------\n\n",
                                                     incorrect,    test_number);

    fclose(fp);
}



bool MyStrncpyTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line[LEN]   = "";
    char mycopy[LEN] = "";
    char copy[LEN]   = "";

    if (!fgets(line, LEN, fp)) return false;

    for (int i = 0; i < LEN; i += 10)
    {

        MyStrncpy(mycopy,line, i);
        strncpy(copy, line, i);

        if (strncmp(copy, mycopy, LEN) != 0)
        {
            (*incorrect)++;
            PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                                 "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), mycopy, copy);
        }
        else
            (*test_number)++;
    }
    return true;
}

void MyStrcatTest()
{
    PrintCyanText(stderr, "TESTING MYSTRCAT---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrcatTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRCAT (%d incorrect, %d tested)----------\n\n",
                                                   incorrect,    test_number);
    fclose(fp);
}



bool MyStrcatTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line1[LEN]  = "";
    char line2[LEN]  = "";
    char mycopy[LEN] = "";
    char copy[LEN]   = "";

    if (!fgets(line1, SHORT_LEN, fp)) return false;
    if (!fgets(line2, SHORT_LEN, fp)) return false;

    strncpy(mycopy, line1, SHORT_LEN);
    strncpy(copy, line1, SHORT_LEN);

    MyStrcat(mycopy, line2);
    strcat(copy, line2);

    if (strncmp(copy, mycopy, LEN) != 0)
    {
        (*incorrect)++;
        PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                             "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), mycopy, copy);
    }
    else
        (*test_number)++;
    return true;
}



void MyStrncatTest()
{
    PrintCyanText(stderr, "TESTING MYSTRNCAT---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrncatTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRNCAT (%d incorrect, %d tested)----------\n\n",
                                                   incorrect,    test_number);
    fclose(fp);
}



bool MyStrncatTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line1[LEN]  = "";
    char line2[LEN]  = "";
    char mycopy[LEN] = "";
    char copy[LEN]   = "";

    if (!fgets(line1, SHORT_LEN, fp)) return false;
    if (!fgets(line2, SHORT_LEN, fp)) return false;

    strncpy(mycopy, line1, SHORT_LEN);
    strncpy(copy, line1, SHORT_LEN);

    for (int i = 0; i < LEN; i+=10)
    {
        MyStrncat(mycopy, line2, i);
        strncat(copy, line2, i);

        if (strncmp(copy, mycopy, LEN) != 0)
        {
            (*incorrect)++;
            PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                                 "FUNCTION: %s\nEXPECTED: %s\n", ++(*test_number), mycopy, copy);
        }
        else
            (*test_number)++;

        strncpy(mycopy, line1, SHORT_LEN);
        strncpy(copy, line1, SHORT_LEN);
    }
    return true;
}



void MyStrchrTest()
{
    PrintCyanText(stderr, "TESTING MYSTRCHR---------------------------------\n", "");

    FILE* fp = fopen(TEST_FILE, "r");

    int test_number = 0;
    int incorrect   = 0;

    while (MyStrchrTestOne(&test_number, &incorrect, fp)) {}

    PrintCyanText(stderr, "END OF TESTING MYSTRCHR (%d incorrect, %d tested)----------\n\n",
                                                   incorrect,    test_number);
    fclose(fp);
}



bool MyStrchrTestOne(int* test_number, int* incorrect, FILE* fp)
{
    char line[LEN]  = "";
    char* myptr     = NULL;
    char* ptr       = NULL;

    if (!fgets(line, SHORT_LEN, fp)) return false;

    for (int i = 'a'; i < 'z'; i++)
    {
        myptr = MyStrchr(line, i);
        ptr   = strchr(line, i);

        if ((myptr - line) != (ptr - line))
        {
            (*incorrect)++;
            PrintRedText(stderr, "TEST %d, INCORRECT RETURN\n"
                                 "FUNCTION: %ld\nEXPECTED: %ld\n", ++(*test_number),
                                            myptr - line,  ptr - line);
        }
        else
            (*test_number)++;

    }
    return true;
}



