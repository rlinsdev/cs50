#include "helpers.h"

static int check_max_int(int result);
static int sepia_new_red(BYTE o_red, BYTE o_green, BYTE o_blue);
static int sepia_new_green(BYTE o_red, BYTE o_green, BYTE o_blue);
static int sepia_new_blue(BYTE o_red, BYTE o_green, BYTE o_blue);

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
        // Instead for, inside the height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Temp original colors
            BYTE o_red = image[i][j].rgbtRed;
            BYTE o_green = image[i][j].rgbtGreen;
            BYTE o_blue = image[i][j].rgbtBlue;

            // Call methods to change color
            image[i][j].rgbtRed = sepia_new_red(o_red, o_green, o_blue);
            image[i][j].rgbtGreen = sepia_new_green(o_red, o_green, o_blue);
            image[i][j].rgbtBlue =sepia_new_blue(o_red, o_green, o_blue);
        }
    }
}

/**
 * @brief Verify if the calc. is greater than 255. Max size is 255
 * @param result Value to check
 * @return int. Max 255
 */
static int check_max_int(int result)
{
    if (result > 255)
    {
        return 255;
    }
    return result;
}

/**
 * @brief Handle the formula to change the color RED
 * @param o_red Original color Red
 * @param o_green Original color Green
 * @param o_blue Original color Blue
 * @return int value. Max of 255
 */
static int sepia_new_red(BYTE o_red, BYTE o_green, BYTE o_blue)
{
    int result = (int)(0.393 * o_red) + (0.769 * o_green) + (0.189 * o_blue);
    return check_max_int(result);
}

/**
 * @brief Handle the formula to change the color GREEN
 * @param o_red Original color Red
 * @param o_green Original color Green
 * @param o_blue Original color Blue
 * @return int value. Max of 255
 */
static int sepia_new_green(BYTE o_red, BYTE o_green, BYTE o_blue)
{
    int result = (int)(0.349 * o_red) + (0.686 * o_green) + (0.168 * o_blue);
    return check_max_int(result);
}

/**
 * @brief Handle the formula to change the color BLUE
 * @param o_red Original color Red
 * @param o_green Original color Green
 * @param o_blue Original color Blue
 * @return int value. Max of 255
 */
static int sepia_new_blue(BYTE o_red, BYTE o_green, BYTE o_blue)
{
    int result = (int)(0.272 * o_red) + (0.534 * o_green) + (0.131 * o_blue);
    return check_max_int(result);
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
