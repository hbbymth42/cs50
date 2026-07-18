#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            // Update pixel values
            image[i][j].rgbtRed = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtBlue = (int) round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                       .189 * image[i][j].rgbtBlue;
            if ((int) round(sepiaRed) > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                         .168 * image[i][j].rgbtBlue;
            if ((int) round(sepiaGreen) > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                        .131 * image[i][j].rgbtBlue;
            if ((int) round(sepiaBlue) > 255)
            {
                sepiaBlue = 255;
            }
            // Update pixel with sepia values
            image[i][j].rgbtRed = (int) round(sepiaRed);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // Calculate middle of each row
    int middle = (int) round((float) width / 2.0) - 1;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reflect image by swapping pixels
            if (j > middle)
            {
                break;
            }
            else
            {
                temp = image[i][width - (1 + j)];
                image[i][width - (1 + j)] = image[i][j];
                image[i][j] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float averageRed, averageGreen, averageBlue;
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Blur image pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top Row Pixels
            if (i - 1 < 0)
            {
                // Top Left Corner Pixel
                if (j - 1 < 0)
                {
                    // Calculate averages of pixels in Box Window (4)
                    averageRed = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                  copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                 4.0;
                    averageGreen = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                    copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                                   4.0;
                    averageBlue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                   copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                                  4.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
                // Top Right Corner Pixel
                else if (j + 1 == width)
                {
                    // Calculate averages of pixels in Box Window (4)
                    averageRed = (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                 4.0;
                    averageGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                   4.0;
                    averageBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                                  4.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
                // Top Middle Pixels
                else
                {
                    // Calculate averages of pixels in Box Window (6)
                    averageRed = (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                  copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                 6.0;
                    averageGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                                    copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                   6.0;
                    averageBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                                   copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                                  6.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
            }
            // Bottom Row Pixels
            else if (i + 1 == height)
            {
                // Bottom Left Corner Pixel
                if (j - 1 < 0)
                {
                    // Calculate averages of pixels in Box Window (4)
                    averageRed = (copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                  copy[i][j + 1].rgbtRed + copy[i][j].rgbtRed) /
                                 4.0;
                    averageGreen = (copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                    copy[i][j + 1].rgbtGreen + copy[i][j].rgbtGreen) /
                                   4.0;
                    averageBlue = (copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                   copy[i][j + 1].rgbtBlue + copy[i][j].rgbtBlue) /
                                  4.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
                // Bottom Right Corner Pixel
                else if (j + 1 == width)
                {
                    // Calculate averages of pixels in Box Window (4)
                    averageRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                  copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed) /
                                 4.0;
                    averageGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                                   4.0;
                    averageBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                                  4.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
                // Bottom Middle Pixels
                else
                {
                    // Calculate averages of pixels in Box Window (6)
                    averageRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                  copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                  copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed) /
                                 6.0;
                    averageGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                    copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                                   6.0;
                    averageBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                   copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                                  6.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
            }
            // Middle Pixels
            else
            {
                // Left-Most Middle Pixels
                if (j - 1 < 0)
                {
                    // Calculate averages of pixels in Box Window (6)
                    averageRed = (copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                  copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i][j].rgbtRed) /
                                 6.0;
                    averageGreen = (copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                    copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i][j].rgbtGreen) /
                                   6.0;
                    averageBlue = (copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                   copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i][j].rgbtBlue) /
                                  6.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
                // Right-Most Middle Pixels
                else if (j + 1 == width)
                {
                    // Calculate averages of pixels in Box Window (6)
                    averageRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                  copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed +
                                  copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) /
                                 6.0;
                    averageGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                    copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                                   6.0;
                    averageBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                   copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                                  6.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
                // Middle-Middle Pixels
                else
                {
                    // Calculate averages of pixels in Box Window (9)
                    averageRed =
                        (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                         copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                         copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed +
                         copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                        9.0;
                    averageGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                    copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                    copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                    copy[i][j].rgbtGreen) /
                                   9.0;
                    averageBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                   copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                   copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                   copy[i][j].rgbtBlue) /
                                  9.0;
                    image[i][j].rgbtRed = (int) round(averageRed);
                    image[i][j].rgbtGreen = (int) round(averageGreen);
                    image[i][j].rgbtBlue = (int) round(averageBlue);
                }
            }
        }
    }
    return;
}
