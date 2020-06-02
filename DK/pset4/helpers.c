#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// https://cs50.harvard.edu/x/2020/psets/4/filter/more/
// To run: ./filter -g images/yard.bmp out.bmp

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image RBGTRIPLE
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //convert to float for rounding purposes
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            int colorAverage = round((blue + red + green) / 3);
            //assign each pixel to the average grey color
            image[i][j].rgbtBlue = colorAverage;
            image[i][j].rgbtGreen = colorAverage;
            image[i][j].rgbtRed = colorAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new RGBTRIPLE to store reflected image first
    RGBTRIPLE(*imagereflect)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // Iterate through image[][] to work on each pixel[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store each pixel[i][j] in its reflected position [i][width - j -1]
            imagereflect[i][j] = image[i][width - j - 1];
        }
    }
    // Update image[][] to be identical to imagereflect[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imagereflect[i][j];
        }
    }
    // Free memory allocated for temporary reflected matrix
    free(*imagereflect);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new RGBTRIPLE to store blurred image first
    RGBTRIPLE(*imageblur)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // Iterate through image[][] to work on each pixel[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize bgr values for each pixel[i][j] and pixelCount to keep track of number to divide for average
            float blue = 0;
            float green = 0;
            float red = 0;
            float pixelCount = 0;
            // Iterate through the 9 pixels (including itself) surrounding pixel[i][j]
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Checking that they exist within the bounds of the image
                    if ((i + k) < height && (i + k) >= 0 && (j + l) < width && (j + l) >= 0)
                    {
                        // Add to total bgr values then increase number to divide for average
                        blue += image[i + k][j + l].rgbtBlue;
                        green += image[i + k][j + l].rgbtGreen;
                        red += image[i + k][j + l].rgbtRed;
                        pixelCount ++;
                    }
                }
            }
            // Find average bgr values
            int avgBlue = round(blue / pixelCount);
            int avgGreen = round(green / pixelCount);
            int avgRed = round(red / pixelCount);
            // Store new bgr values in imageblur[i][j]
            imageblur[i][j].rgbtBlue = avgBlue;
            imageblur[i][j].rgbtGreen = avgGreen;
            imageblur[i][j].rgbtRed = avgRed;
        }
    }
    // Update image[][] to be identical to imageblur[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageblur[i][j];
        }
    }
    // Free memory allocated for temporary blurred matrix
    free(*imageblur);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize filters Gx and Gy as an array
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    // Create a new RGBTRIPLE to store edged image first
    RGBTRIPLE(*imageedge)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // Iterate through image[][] to work on each pixel[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize values for each pixel[i][j]
            float blueGx = 0;
            float greenGx = 0;
            float redGx = 0;
            float blueGy = 0;
            float greenGy = 0;
            float redGy = 0;
            int caseCount = 0;
            // Iterate through the 9 pixels (including itself) surrounding pixel[i][j]
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Checking that they exist within the bounds of the image
                    if (caseCount < 9 && (i + k) < height && (i + k) >= 0 && (j + l) < width && (j + l) >= 0)
                    {
                        // Update values by multiplying with filter value
                        blueGx += (image[i + k][j + l].rgbtBlue) * Gx[caseCount];
                        greenGx += (image[i + k][j + l].rgbtGreen) * Gx[caseCount];
                        redGx += (image[i + k][j + l].rgbtRed) * Gx[caseCount];
                        blueGy += (image[i + k][j + l].rgbtBlue) * Gy[caseCount];
                        greenGy += (image[i + k][j + l].rgbtGreen) * Gy[caseCount];
                        redGy += (image[i + k][j + l].rgbtRed) * Gy[caseCount];
                    }
                    // Increment casecount to move down filter array for nex filter value
                    caseCount++;
                }
            }
            // Find new bgr values
            int avgBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
            int avgGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
            int avgRed = round(sqrt(redGx * redGx + redGy * redGy));
            // Check if the values are greater than 255 and force to 255
            if (avgBlue > 255)
            {
                avgBlue = 255;
            }
            if (avgGreen > 255)
            {
                avgGreen = 255;
            }
            if (avgRed > 255)
            {
                avgRed = 255;
            }
            // Store new bgr values in imageedge[i][j]
            imageedge[i][j].rgbtBlue = avgBlue;
            imageedge[i][j].rgbtGreen = avgGreen;
            imageedge[i][j].rgbtRed = avgRed;
        }
    }
    // Update image[][] to be identical to imageedge[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageedge[i][j];
        }
    }
    // Free memory allocated for temporary edged matrix
    free(*imageedge);
    return;
}
