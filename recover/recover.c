#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512]; // Buffer to store a block of data
    bool found_jpeg = false;
    int counter = 0;
    char filename[8];
    FILE *img = NULL;

    // Loop through the raw file until the end
    while (fread(buffer, 1, 512, f) == 512)
    {
        // Check if the block indicates the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a previous JPEG is open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new filename for the JPEG
            sprintf(filename, "%03i.jpg", counter);

            // Open a new file for writing the JPEG
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create JPEG file.\n");
                fclose(f);
                return 1;
            }

            counter++; // Increment the file counter

            // Write the JPEG header block to the new file
            fwrite(buffer, 1, 512, img);
        }
        else if (img != NULL)
        {
            // Continue writing to the current JPEG file
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(f);

    return 0;
}
