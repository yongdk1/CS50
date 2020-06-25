#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://cs50.harvard.edu/x/2020/psets/4/recover/
// First 3 bytes of jpeg are 0xff 0xd8 0xff
// Fourth byte is 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;

    BYTE buffer[512];

    // Check if the user gave only one file name, return error message if not given
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open file as inptr, return error message if unopenable
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }

    // Initialize string to hold filename "XXX.jpg\0", int to hold filecount, value of XXX, and FILE outptr
    char filename[8];
    int filecount = 0;
    FILE *outptr = NULL;

    // Check if 512 bytes exist in the current block and repeat code until less than 512 bytes remain in inptr
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        // Check if first 4 bytes in current block match .jpg file header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Modify the very first .jpg
            if (filecount == 0)
            {
                sprintf(filename, "%03i.jpg", filecount);
                outptr = fopen(filename, "w");
                fwrite(buffer, 1, 512, outptr);
                filecount ++;
            }
            // Close previous .jpg and open/modify next .jpg
            else
            {
                fclose(outptr);
                sprintf(filename, "%03i.jpg", filecount);
                outptr = fopen(filename, "w");
                fwrite(buffer, 1, 512, outptr);
                filecount ++;
            }
        }
        // If a .jpg is open, write block to the outptr file
        else if (filecount > 0)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }

    // Close input and last output file
    fclose(inptr);
    fclose(outptr);

    return 0;
}