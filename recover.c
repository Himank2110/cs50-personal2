#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // checks for correct number of command line arguments
    {
        printf("Usage : ./recover <file name>\n");
        return 1;
    }
    // open input file
    FILE *source = fopen(argv[1], "r");
    if (source == NULL) // checks whether file could open or not
    {
        printf("Could not open file\n");
        return 1;
    }
    uint8_t buffer[512];
    int n = 0;
    char string[8];
    FILE *img;
    while (fread(&buffer, sizeof(uint8_t), 512, source) == 512) // loops over all 512 byte blocks
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // if start of a jpeg image
        {
            if (n != 0) // if previous file was open
            {
                fclose(img);
            }
            sprintf(string, "%03i.jpg", n);
            n++;
            img = fopen(string, "w"); // makes new jpg file for new image
        }
        if (n > 0)
        {
            fwrite(&buffer, sizeof(uint8_t), 512, img); // writes data to new file
        }
    }
    fclose(img);
    fclose(source);
    return 0;
}
