#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int search(int minimum, int maximum);
char *lowerString(char *str);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: NumberGuesser.elf minimum maximum\n");
        return (1);
    }
    // Parse the provided limits
    char *endPtr;
    int minimum = strtol(argv[1], &endPtr, 10);
    if (argv[1] == endPtr)
    {
        printf("Invalid minimum provided.\n");
        return (1);
    }
    int maximum = strtol(argv[2], &endPtr, 10);
    if (argv[2] == endPtr)
    {
        printf("Invalid maximum provided.\n");
        return (1);
    }
    // Check if the limit is invalid
    if (maximum - minimum <= 0)
    {
        printf("Invalid limits of %i to %i provided.\n", minimum, maximum);
        return (1);
    }
    int totalSize = maximum - minimum;
    int guessCount = 0;
    for (int finished = 0; !finished; guessCount++)
    {
        int guess = search(minimum, maximum);
        printf("Is %i your number? (Yes/No)\n", guess);
        char *userIn = malloc(3);
        scanf("%s[^\n]", userIn);
        while ('\n' != getchar()) // Clean the stdin buffer
        {
        };
        char *lowerUserIn = lowerString(userIn);
        free(userIn);
        userIn = lowerUserIn;
        if (!strcmp(userIn, "yes")) // User input was "yes"
        {
            finished = 1;
            free(userIn);
            break;
        }
        else if (strcmp(userIn, "no")) // User input was not "yes" or "no"
        {
            printf("Invalid input provided, assuming input was \"No\".\n");
        }
        free(userIn);
        // User input was "no"
        // Keep guessing
        printf("Was the guess higher than or lower than your number? (Higher/Lower)\n");
        userIn = malloc(6);
        scanf("%s[^\n]", userIn);
        while ('\n' != getchar()) // Clean the stdin buffer
        {
        };
        lowerUserIn = lowerString(userIn);
        free(userIn);
        userIn = lowerUserIn;
        if (!strcmp(userIn, "higher"))
        {
            maximum = guess;
        }
        else if (!strcmp(userIn, "lower"))
        {
            minimum = guess;
        }
        else
        {
            printf("Invalid response, skipping and asking again.\n");
            continue;
        }
        printf("\n");
    }
    double averageOLog = log(totalSize) / log(2);
    printf("\nI found your number with %i checks, binary search takes up to %0.f times with %i list members.\n", guessCount, round(averageOLog), totalSize);
}

int search(int minimum, int maximum)
{
    int difference = maximum - minimum;
    int midDif = difference / 2;
    return (round(minimum + midDif));
}

char *lowerString(char *str)
{
    char *outStr = malloc(0);
    int i = 0;
    for (; str[i] != '\0'; i++)
    {
        outStr = realloc(outStr, i + 1);
        outStr[i] = tolower(str[i]);
    }
    outStr[i] = '\0';
    // The user must be careful to still free the char *str argument
    return (outStr);
}