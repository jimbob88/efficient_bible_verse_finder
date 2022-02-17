/*
BIBLE READER SOFTWARE

REQUIRES:
 - bible.txt
 - Bibles in the read_aloud format

Example command:
$ ./main -b engwebpb -B GEN -h
*/
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <glob.h>

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

struct fnd
{
    int r;
    char **found;
};

struct fnd
globber(char *glob_text, char *bible_name, char *book_name)
{
    struct fnd result;
    char **found;
    glob_t gstruct;
    int r;
    char buff[1024];
    snprintf(buff, sizeof(buff), glob_text, bible_name, bible_name, book_name);
    printf("%s\n", buff);
    r = glob(buff, GLOB_ERR, NULL, &gstruct);
    if (r != 0)
    {
        if (r == GLOB_NOMATCH)
        {
            fprintf(stderr, "No matches\n");
            result.r = 2;
            return result;
        }
        else
        {
            fprintf(stderr, "Some kinda glob error\n");
            result.r = 2;
            return result;
        }
    }
    result.r = 0;
    result.found = gstruct.gl_pathv;
    return result;
}

int main(int argc, char *const argv[])
{
    int c;
    int bible_parsed = 0;
    int book_parsed = 0;
    char *bible_name;
    char *book_name;

    while ((c = getopt(argc, argv, "hb:B:")) != -1)
    {
        switch (c)
        {
        case 'h':
            printf("-b [bible_name]\n-B [book_name]\n");
            break;
        case 'b':
            bible_parsed = 1;
            bible_name = optarg;
            break;
        case 'B':
            book_parsed = 1;
            book_name = optarg;
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

    if (!book_parsed)
    {
        printf("ERROR: -B OPTION IS REQUIRED\n");
        exit(1);
    }

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
            break;
        }
    }
    fclose(filePointer);

    if (!bible_exists)
    {
        printf("ERROR: Bible does not exist\n");
        exit(1);
    }

    struct fnd glob_result1;
    glob_result1 = globber("./bibles/%s/%s_*_%s*.txt", bible_name, book_name);

    if (glob_result1.r == 0)
    {
        while (*glob_result1.found)
        {
            printf("%s\n", *glob_result1.found);
            glob_result1.found++;
        }
    }
    else
    {
        printf("ERROR: NOT FOUND?");
    }

    // char **found;
    // glob_t gstruct;
    // int r;
    // char buff[1024];
    // snprintf(buff, sizeof(buff), "./bibles/%s/%s_*_%s*.txt", bible_name, bible_name, book_name);
    // printf("%s\n", buff);
    // r = glob(buff, GLOB_ERR, NULL, &gstruct);
    // if (r != 0)
    // {
    //     if (r == GLOB_NOMATCH)
    //         fprintf(stderr, "No matches with initial test\n");
    //     else
    //         fprintf(stderr, "Some kinda glob error\n");
    //     exit(1);
    // }
    // found = gstruct.gl_pathv;
    // while (*found)
    // {
    //     printf("%s\n", *found);
    //     found++;
    // }
    return 0;
}