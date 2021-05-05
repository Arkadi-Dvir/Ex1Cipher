#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COMMAND1 "encode"
#define COMMAND2 "decode"
#define BASE 26
#define CAPITAL_START 'A'
#define CAPITAL_END 'Z'
#define SMALL_START 'a'
#define SMALL_END 'z'

/**
 * This function encoding the char it gets
 * @param curChar - The char we want to encode
 * @param shiftMov - The size of the shift
 * @return - Returns the new value of the char
 */
int encodeCalc(const int curChar, const int shiftMov)
{
    if(curChar < CAPITAL_START || (curChar > CAPITAL_END && curChar < SMALL_START) || curChar > SMALL_END)
    {
        return curChar;
    }
    int movNum = shiftMov % BASE;
    int newNum = curChar + movNum;
    if(curChar >= CAPITAL_START && curChar <= CAPITAL_END && newNum > CAPITAL_END)
    {
        newNum = newNum - CAPITAL_END;
        newNum = newNum + CAPITAL_START - 1;
    }
    else if(curChar >= SMALL_START && curChar <= SMALL_END && newNum > SMALL_END)
    {
        newNum = newNum - SMALL_END;
        newNum = newNum + SMALL_START - 1;
    }
    else
    {
        return newNum;
    }
    return newNum;
}

/**
 * This function decoding the char it gets
 * @param curChar - The char we want to decode
 * @param shiftMov - The size of the shift
 * @return - Returns the new value of the char
 */
int decodeCalc(const int curChar, const int shiftMov)
{
    if(curChar < CAPITAL_START || (curChar > CAPITAL_END && curChar < SMALL_START) || curChar > SMALL_END)
    {
        return curChar;
    }
    int movNum = shiftMov % BASE;
    int newNum = curChar - movNum;
    if(curChar >= CAPITAL_START && curChar <= CAPITAL_END && newNum < CAPITAL_START)
    {
        newNum = CAPITAL_START - newNum;
        newNum = CAPITAL_END - newNum + 1;
    }
    else if(curChar >= SMALL_START && curChar <= SMALL_END && newNum < SMALL_START)
    {
        newNum = SMALL_START - newNum;
        newNum = SMALL_END - newNum + 1;
    }
    else
    {
        return newNum;
    }
    return newNum;
}

/**
 * This the main function that runs the program
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    if(argc != 4)  // Checking the number of arguments we got
    {
        fprintf(stderr, "Usage: cipher <encode|decode> <k> <message>\n");
        return EXIT_FAILURE;
    }
    int k = 0;  // The counter on the number string
    while (argv[2][k] != '\0')  // Checking the input of the number
    {
        if((argv[2][k] < 48 || argv[2][k] > 57) && k == 0)
        {
            fprintf(stderr, "The given shifts value is invalid\n");
            return EXIT_FAILURE;
        }
        k++;
    }
    const int myNum = atoi(argv[2]);  // Assigning the number value to int
    if(!strcmp(argv[1], COMMAND1))  // Checking if the command is encode
    {
        int j = 0;
        while(argv[3][j] != '\0')  // Running over the string chars till the end on the string
        {
            int curChar = argv[3][j];
            int newChar = encodeCalc(curChar, myNum);  // Encoding the char
            argv[3][j] = newChar;  // Assigning the new char to the string
            j++;
        }
        printf("%s\n", argv[3]);
    }
    else if(!strcmp(argv[1], COMMAND2))  // Checking if the command is decode
    {
        int j = 0;
        while(argv[3][j] != '\0')  // Running over the string chars till the end on the string
        {
            int curChar = argv[3][j];
            int newChar = decodeCalc(curChar, myNum);  // Decoding the char
            argv[3][j] = newChar;  // Assigning the new char to the string
            j++;
        }
        printf("%s\n", argv[3]);
    }
    else  // If the command is illegal
    {
        fprintf(stderr, "%s", "The given command is invalid\n");
        return EXIT_FAILURE;
    }
    return 0;
}