#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("It seems like you passed no commands?\n");
        return -1;
    }
    else
    {
        // for (int i = 1; i < argc; ++i)
        // {
        //     printf("argv[%d]: %s\n", i, argv[i]);
        // }
        if (strcmp("-bible", argv[1]) == 0 && argc > 2)
        {
            printf("Selecting bible: %s\n", argv[2]);
            // printf("typeof: %s", typeof(argv[2]));
            // char bible_name[] = argv[2];
        }
        else
        {
            printf("No bible passed, choosing default bible: engwebp\n");
            char bible_name[] = "engwebp";
        };
        return 0;
    }
}