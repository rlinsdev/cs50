#include "helpers.h"
#include <stdio.h>
#include <math.h>

static float check_max_int(float result);
static float sepia_new_red(BYTE o_red, BYTE o_green, BYTE o_blue);
static float sepia_new_green(BYTE o_red, BYTE o_green, BYTE o_blue);
static float sepia_new_blue(BYTE o_red, BYTE o_green, BYTE o_blue);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Instead for, inside the height and width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int mix = roundf((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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
            image[i][j].rgbtBlue = sepia_new_blue(o_red, o_green, o_blue);
        }
    }
}

/**
 * @brief Verify if the calc. is greater than 255. Max size is 255
 * @param result Value to check
 * @return float. Max 255
 */
static float check_max_int(float result)
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
 * @return float value. Max of 255
 */
static float sepia_new_red(BYTE o_red, BYTE o_green, BYTE o_blue)
{
    float result = roundf((0.393 * o_red) + (0.769 * o_green) + (0.189 * o_blue));
    return check_max_int(result);
}

/**
 * @brief Handle the formula to change the color GREEN
 * @param o_red Original color Red
 * @param o_green Original color Green
 * @param o_blue Original color Blue
 * @return float value. Max of 255
 */
static float sepia_new_green(BYTE o_red, BYTE o_green, BYTE o_blue)
{

    float result = roundf((0.349 * o_red) + (0.686 * o_green) + (0.168 * o_blue));
    return check_max_int(result);
}

/**
 * @brief Handle the formula to change the color BLUE
 * @param o_red Original color Red
 * @param o_green Original color Green
 * @param o_blue Original color Blue
 * @return float value. Max of 255
 */
static float sepia_new_blue(BYTE o_red, BYTE o_green, BYTE o_blue)
{
    float result = roundf((0.272 * o_red) + (0.534 * o_green) + (0.131 * o_blue));
    return check_max_int(result);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int)(width / 2); j++)
        {
            // Temp reflected colors
            BYTE r_red = image[i][width - 1 - j].rgbtRed;
            BYTE r_green = image[i][width - 1 - j].rgbtGreen;
            BYTE r_blue = image[i][width - 1 - j].rgbtBlue;

            // Temp original colors
            BYTE o_red = image[i][j].rgbtRed;
            BYTE o_green = image[i][j].rgbtGreen;
            BYTE o_blue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = r_red;
            image[i][width - 1 - j].rgbtRed = o_red;

            image[i][j].rgbtGreen = r_green;
            image[i][width - 1 - j].rgbtGreen = o_green;

            image[i][j].rgbtBlue = r_blue;
            image[i][width - 1 - j].rgbtBlue = o_blue;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i <= (height - 1); i++)
    {
        for (int j = 0; j <= (width - 1); j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Instead for, inside the height and width
    for (int i = 0; i <= (height - 1); i++)
    {
        for (int j = 0; j <= (width - 1); j++)
        {
            // red
            int result = 0;
            int sum = 0;
            float count = 0.0;
            for (int k = -1; k <= 1; k++)
            {
                if ((i + k) == -1 || (i + k) == (height + 1))
                {
                    continue;
                }
                for (int l = -1; l <= 1; l++)
                {
                    if ((j + l) == -1 || (j + l) > (width + 1))
                    {
                        continue;
                    }
                    result = copy[i + k][l + j].rgbtRed;
                    sum += result;
                    count ++;
                }
            }
            // Update pixel with new average
            if (count > 0 && sum > 0)
            {
                float calc = (roundf(sum / count));
                image[i][j].rgbtRed = calc;
            }

            // Green
            result = 0;
            sum = 0;
            count = 0;
            for (int k = -1; k <= 1; k++)
            {
                if ((i + k) == -1 || (i + k) == (height + 1))
                {
                    continue;
                }
                for (int l = -1; l <= 1; l++)
                {
                    if ((j + l) == -1 || (j + l) > (width + 1))
                    {
                        continue;
                    }
                    result = copy[i + k][l + j].rgbtGreen;
                    sum += result;
                    count ++;
                }
            }
            // Update pixel with new average
            if (count > 0 && sum > 0)
            {
                float calc = (roundf(sum / count));
                image[i][j].rgbtGreen = calc;
            }

            // Blue
            result = 0;
            sum = 0;
            count = 0;
            for (int k = -1; k <= 1; k++)
            {
                // Boards / inexistent pixels, just go to next
                if ((i + k) == -1 || (i + k) == (height + 1))
                {
                    continue;
                }
                for (int l = -1; l <= 1; l++)
                {
                    // Boards / inexistent pixels, just go to next
                    if ((j + l) == -1 || (j + l) > (width + 1))
                    {
                        continue;
                    }
                    result = copy[i + k][l + j].rgbtBlue;
                    sum += result;
                    count ++;
                }
            }
            // Update pixel with new average
            if (count > 0 && sum > 0)
            {
                float calc = (roundf(sum / count));
                image[i][j].rgbtBlue = calc;
            }
        }
    }
}
