#include <stdio.h>
#include <stdlib.h>

int chinstr(char c, char *str)
{
    char *seeker = str;
    while (*seeker != '\0')
    {
        if (*seeker == c)
            return 1;
        seeker++;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        printf("USAGE\n\t%s filename [rgb]\n", argv[0]);
        exit(0);
    }

    FILE *fp = fopen(argv[1], "wb");
    if (fp == NULL)
    {
        printf("Couldn't create file %s\n", argv[1]);
        exit(0);
    }

    const int width = 255, height = 255;
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    int i, j;
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            static unsigned char pixel[3];
            if (argc == 3)
            {
                pixel[0] = chinstr('r', argv[2]) ? i : (i * j) / 255;
                pixel[1] = chinstr('g', argv[2]) ? i : (i * j) / 255;
                pixel[2] = chinstr('b', argv[2]) ? i : (i * j) / 255;
            }
            else
            {
                pixel[0] = pixel[1] = pixel[2] = (i * j) / 255;
            }

            fwrite(pixel, 3, 1, fp);
        }
    }
    fclose(fp);
    
    return 0;
}
