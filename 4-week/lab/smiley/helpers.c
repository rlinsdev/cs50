#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Instead for, inside the height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check all collor in black
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                // I had got a color in hexa. Looks lik a blue.
                image[i][j].rgbtRed = 0x75;
                image[i][j].rgbtGreen = 0xE6;
                image[i][j].rgbtBlue = 0xDA;
            }
        }
    }
}
