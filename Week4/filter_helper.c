#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
             average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
             image[i][j].rgbtBlue = average;
             image[i][j].rgbtGreen = average;
             image[i][j].rgbtRed = average;
        }
    }
    return;
}

static uint8_t clamp(int value)
{
    if(value<0) return 0;
    if(value>255) return 255;
    return value;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double sepiaRed = 0.0;
    double sepiaGreen = 0.0;
    double sepiaBlue = 0.0;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

             sepiaRed = clamp(round(.189*image[i][j].rgbtBlue + .769*image[i][j].rgbtGreen + .393*image[i][j].rgbtRed));
             sepiaGreen = clamp(round(.168*image[i][j].rgbtBlue + .686*image[i][j].rgbtGreen + .349*image[i][j].rgbtRed));
             sepiaBlue = clamp(round(.131*image[i][j].rgbtBlue + .534*image[i][j].rgbtGreen + .272*image[i][j].rgbtRed));
             image[i][j].rgbtBlue = sepiaBlue;
             image[i][j].rgbtGreen = sepiaGreen;
             image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    double averageRed;
    double averageGreen;
    double averageBlue;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1- j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int blueAvg  = 0;
            int redAvg  = 0;
            int greenAvg = 0;
            double counter = 0;
            for (int s = i - 1; s < i + 2; s++) {
                if (s < 0 || s >= height)
                    continue;
                for (int m = j - 1; m < j + 2; m++) {
                    if (m < 0 || m >= width)
                        continue;
                    redAvg   += tmp[s][m].rgbtRed;
                    greenAvg += tmp[s][m].rgbtGreen;
                    blueAvg  += tmp[s][m].rgbtBlue;
                    counter += 1;
                }
            }
            image[i][j].rgbtRed   = round(redAvg/counter);
            image[i][j].rgbtGreen = round(greenAvg/counter);
            image[i][j].rgbtBlue  = round(blueAvg/counter);
        }
    }

    return;
}