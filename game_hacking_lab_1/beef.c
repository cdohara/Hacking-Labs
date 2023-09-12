#include <stdio.h>
#include <stdlib.h>

#define A 1664525
#define C 1013904223
#define M 4294967296 // 2^32

unsigned long seed = 1243;

struct answer
{
    int index;
    unsigned long value;
};

unsigned long pseudoRandom()
{
    seed = (A * seed + C) % M;
    return seed;
}

void victory()
{
    char flag[6];
    flag[5] = 0x1D;
    flag[1] = 0x7E;
    flag[3] = 0x96;
    flag[0] = 0x94;
    flag[4] = 0x92;
    flag[2] = 0x84;

    for (unsigned int BhwKJ = 0, WhGdn = 0; BhwKJ < 6; BhwKJ++)
    {
        WhGdn = flag[BhwKJ];
        WhGdn += BhwKJ;
        WhGdn += 0xE3;
        WhGdn -= BhwKJ;
        flag[BhwKJ] = WhGdn;
    }
    printf("Flag: %s\n", flag);
}

int compare(unsigned long guess, unsigned long answer)
{
    if (guess == answer)
    {
        victory();
        exit(0);
    }
    else
    {
        printf("Wrong!\n");
        return 0;
    }
}

int main()
{
    char buffer[50];
    struct answer a;
    a.index = 0;
    a.value = pseudoRandom();
    do
    {
        printf("What is the next number? ");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Convert the buffer to an unsigned long
            char *endptr;
            unsigned long guess = strtoul(buffer, &endptr, 10);

            if (*endptr != '\0' && *endptr != '\n')
            {
                printf("Invalid input\n");
            }
            else
            {
                compare(guess, a.value);
                printf("Attempt %d: The number was %lu\n", a.index,  a.value);
            }
        }
        else
        {
            printf("Error reading input\n");
            break;
        }
        a.index++;
        a.value = pseudoRandom();
    } while (1);

    return 0;
}
