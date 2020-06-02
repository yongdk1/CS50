#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE Grey;
    //Traversal of the 2D image array
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            //Find the Grey colour intensity and copy to each colour, more accurate to use float and round!!!
            Grey = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.00);
            image[h][w].rgbtBlue = Grey;
            image[h][w].rgbtGreen = Grey;
            image[h][w].rgbtRed = Grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int h = 0; h < height; h++){
        //Traveserse through the left half of the image, just divide by 2!!!
        for (int w = 0; w < width / 2; w++){
            //swap the pixel on the opposite side
            tmp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //sum has to be declared as int(4bytes) rather than BYTE (1byte) else intermediate data cannot be stored!!!
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;

    //Need to declare a temp or else subsequent operation will be affected!!!
    RGBTRIPLE tmp[height][width];

    //Traverse through the 2D image array
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){

            //Initialize after every operation!!!
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            //Traverse through the pixels surrounding the current pixel
            for (int sR = -1; sR < 2; sR++){
                for (int sC = -1; sC < 2; sC++){
                    //Check for corners and edges, if the pixel is in a corner or edge, adding sR or sC will result in values outside the array
                    if ((h + sR) < 0 || (h + sR) > height - 1 || (w + sC) < 0 || (w + sC) > width - 1){
                        continue;
                    }
                    else{
                        //Summing of colour values
                        sumBlue += image[h + sR][w + sC].rgbtBlue;
                        sumGreen += image[h + sR][w + sC].rgbtGreen;
                        sumRed += image[h + sR][w + sC].rgbtRed;

                        counter++;
                    }
                }
            }
            //Storing averaged colour values in a temp array
            tmp[h][w].rgbtBlue = round(sumBlue / counter);
            tmp[h][w].rgbtGreen = round(sumGreen / counter);
            tmp[h][w].rgbtRed = round(sumRed / counter);
        }
    }
    //Copy temp values over to image
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            image[h][w].rgbtBlue = tmp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = tmp[h][w].rgbtGreen;
            image[h][w].rgbtRed = tmp[h][w].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //To store added values
    float GxBlue, GyBlue;
    float GxGreen, GyGreen;
    float GxRed, GyRed;

    //To store process values
    int bgr[3];
    int counter;

    //Array to store multipliers for Gx and Gy
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    //Need to declare a temp or else subsequent operation will be affected!!!
    RGBTRIPLE tmp[height][width];

    //Traverse through the 2D image array
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){

            //Initialize after every operation!!!
            GxBlue = 0, GyBlue = 0;
            GxGreen = 0, GyGreen = 0;
            GxRed = 0, GyRed = 0;
            counter = 0;

            //Traverse through the pixels surrounding the current pixel
            for (int sR = -1; sR < 2; sR++){
                for (int sC = -1; sC < 2; sC++){
                    //Check for corners and edges
                    if ((h + sR) < 0 || (h + sR) > height - 1 || (w + sC) < 0 || (w + sC) > width - 1){

                        //"Pixels" outside image is trated as black
                        GxBlue += 0;
                        GyBlue += 0;
                        GxGreen += 0;
                        GyGreen += 0;
                        GxRed += 0;
                        GyRed += 0;

                        counter++;
                    }
                    else{
                        //Add the colour values according to Sobel Operator
                        GxBlue += image[h + sR][w + sC].rgbtBlue * Gx[counter];
                        GxGreen += image[h + sR][w + sC].rgbtGreen * Gx[counter];
                        GxRed += image[h + sR][w + sC].rgbtRed * Gx[counter];

                        GyBlue += image[h + sR][w + sC].rgbtBlue * Gy[counter];
                        GyGreen += image[h + sR][w + sC].rgbtGreen * Gy[counter];
                        GyRed += image[h + sR][w + sC].rgbtRed * Gy[counter];

                        counter++;
                    }
                }
            }

            bgr[0] = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            bgr[1] = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            bgr[2] = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));

            //If more than 255, change to = 255 or else ther will be overflow!!!
            for (int x = 0; x < 3; x++){
                if (bgr[x] > 255){
                    bgr[x] = 255;
                }
            }

            //Store processed data in a temp 2D array
            tmp[h][w].rgbtBlue = bgr[0];
            tmp[h][w].rgbtGreen = bgr[1];
            tmp[h][w].rgbtRed = bgr[2];
        }
    }

    //Copy temp values over to image
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            image[h][w].rgbtBlue = tmp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = tmp[h][w].rgbtGreen;
            image[h][w].rgbtRed = tmp[h][w].rgbtRed;
        }
    }
    return;
}
