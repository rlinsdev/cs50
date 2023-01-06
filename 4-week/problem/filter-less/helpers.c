#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Instead for, inside the height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
			int mix = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
			image[i][j].rgbtRed = mix;
			image[i][j].rgbtGreen  = mix;
			image[i][j].rgbtBlue = mix;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
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
