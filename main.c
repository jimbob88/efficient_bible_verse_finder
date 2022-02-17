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
globber(char *glob_text, char *bible_name, char *book_name, int verse_num)
{
    struct fnd result;
    char **found;
    glob_t gstruct;
    int r;
    char buff[1024];
    // printf("%s", glob_text);
    snprintf(buff, sizeof(buff), glob_text, bible_name, bible_name, book_name, verse_num);
    // printf("\n%s\n", buff);
    r = glob(buff, GLOB_ERR, NULL, &gstruct);
    if (r != 0)
    {
        if (r == GLOB_NOMATCH)
        {
            fprintf(stderr, "\033[0;33mNo matches\033[0m\n");
            result.r = 2;
            return result;
        }
        else
        {
            fprintf(stderr, "\033[0;33mUnknown glob error\033[0m\n");
            result.r = 2;
            return result;
        }
    }
    result.r = 0;
    result.found = gstruct.gl_pathv;
    return result;
}

void print_file(FILE *filePointer, char *text_file)
{
    int bufferLength = 2000;
    char buffer[bufferLength];

    filePointer = fopen(text_file, "r");

    // Reading verse text
    while (fgets(buffer, bufferLength, filePointer))
    {
        printf("%s\n", buffer);
    }
    fclose(filePointer);
}

int main(int argc, char *const argv[])
{
    int c;
    int bible_parsed = 0;
    int book_parsed = 0;
    int verse_parsed = 0;
    char *bible_name;
    char *book_name;
    int verse_num;

    while ((c = getopt(argc, argv, "hb:B:V:")) != -1)
    {
        switch (c)
        {
        case 'h':
            printf("-b [bible_name]\n-B [book_name]\n-V [verse_number]\n");
            break;
        case 'b':
            bible_parsed = 1;
            bible_name = optarg;
            break;
        case 'B':
            book_parsed = 1;
            book_name = optarg;
            break;
        case 'V':
            verse_parsed = 1;
            verse_num = atoi(optarg);
            break;
        case '?':
            printf("Unknown option: -%c\n", optopt);
        }
    };
    if (!bible_parsed)
    {
        printf("\033[0;31mERROR: -b OPTION IS REQUIRED\033[0m\n");
        exit(1);
    };

    if (!book_parsed)
    {
        printf("\033[0;31mERROR: -B OPTION IS REQUIRED\033[0m\n");
        exit(1);
    }

    if (!verse_parsed)
    {
        printf("\033[0;31mERROR: -V OPTION IS REQUIRED\033[0m\n");
        exit(1);
    }

    printf("Checking bible exists: %s\n", bible_name);

    printf("Performing search in ./bibles.txt\n");

    FILE *filePointer;
    int bufferLength = 30;
    char buffer[bufferLength];

    filePointer = fopen("bibles.txt", "r");

    if (filePointer == NULL)
    {
        printf("\033[0;31mERROR: bibles.txt does not exist\033[0m\n");
        exit(1);
    }

    // check bible exists in bibles.txt
    int bible_exists = 0;
    while (fgets(buffer, bufferLength, filePointer))
    {
        if (compareArrays(buffer, bible_name, sizeof bible_name))
        {
            printf("\033[0;32mBible exists\033[0m\n");
            bible_exists = 1;
            break;
        }
    }
    fclose(filePointer);

    if (!bible_exists)
    {
        printf("\033[0;31mERROR: Bible does not exist\033[0m\n");
        exit(1);
    }

    struct fnd glob_result;
    // Test with 2 decimal places
    glob_result = globber("./bibles/%s/%s_*_%s_%.2d_read.txt", bible_name, book_name, verse_num);

    char *text_file;

    if (glob_result.r == 0)
    {
        while (*glob_result.found)
        {
            text_file = *glob_result.found;
            printf("%s\n", text_file);
            glob_result.found++;
        }
    }
    else
    {
        // Test with 3 decimal places because PSA uses 3 decimal places
        printf("Testing integers with 3 sig figs\n");
        glob_result = globber("./bibles/%s/%s_*_%s_%.3d_read.txt", bible_name, book_name, verse_num);
        if (glob_result.r == 0)
        {
            while (*glob_result.found)
            {
                text_file = *glob_result.found;
                printf("%s\n", text_file);
                glob_result.found++;
            }
        }
        else
        {
            printf("\033[0;31m%s: No verse found in %s at verse %d\n\033[0m", bible_name, book_name, verse_num);
            exit(1);
        }
    }

    print_file(filePointer, text_file);

    return 0;
}