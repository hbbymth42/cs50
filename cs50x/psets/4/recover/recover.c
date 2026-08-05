#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define FILENAME_SIZE 7

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("File wasn't opened properly!");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    // Initialise first JPEG file
    char *filename = malloc(FILENAME_SIZE + 1);
    sprintf(filename, "%03i.jpg", 0);
    FILE *img = fopen(filename, "w");
    int file_num = 0;
    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Create JPEGs from the data
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            file_num = file_num + 1;
            // Write to created first file
            if (file_num == 1)
            {
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
            // When a new file is found, close previous file and start writing to new file
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", file_num - 1);
                img = fopen(filename, "w");
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
        }
        else
        {
            // Keep writing to open file if the first image was found
            if (file_num > 0)
            {
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
        }
    }
    // Close files
    free(filename);
    fclose(img);
    fclose(card);
    return 0;
}
