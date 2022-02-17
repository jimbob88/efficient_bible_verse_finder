#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
    }
    else
    {
        printf("%s\n", bible_name);
    };
    return 0;
}