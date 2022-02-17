#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int compareArrays(char a[], char b[], long unsigned int n)
{
    // Adapted from https://stackoverflow.com/a/24153920/5210078
    int ii;
    for (ii = 1; ii <= n; ii++)
    {
        if (a[ii] != b[ii])
            return 0;
    }
    return 1;
}

int main(int argc, char *const argv[])
{
    int c;
    int bible_parsed = 0;
    char *bible_name;

    while ((c = getopt(argc, argv, "b:")) != -1)
    {
        switch (c)
        {
        case 'b':
            bible_parsed = 1;
            bible_name = optarg;
            break;
        case '?':
            printf("Unknown option: -%c\n", optopt);
        }
    };
    if (!bible_parsed)
    {
        printf("ERROR: -b OPTION IS REQUIRED\n");
        exit(1);
    };

    printf("Checking bible exists: %s\n", bible_name);

    printf("Performing search in ./bibles.txt\n");

    FILE *filePointer;
    int bufferLength = 30;
    char buffer[bufferLength];

    filePointer = fopen("bibles.txt", "r");

    // check bible exists in bibles.txt
    int bible_exists = 0;
    while (fgets(buffer, bufferLength, filePointer))
    {
        if (compareArrays(buffer, bible_name, sizeof bible_name))
        {
            printf("Bible exists\n");
            bible_exists = 1;
        }
    }
    if (!bible_exists)
    {
        printf("ERROR: Bible does not exist\n");
        exit(1);
    }

    fclose(filePointer);

    return 0;
}