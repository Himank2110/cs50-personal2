#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int j = 0, n = width;
        do
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][n - 1];
            image[i][n - 1] = temp;
            j++;
            n--;
        }
        while(!(j == n || (j + 1 == n)));
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width], check[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int n = 0;
            long int rgbtRed = 0;
            long int rgbtGreen = 0;
            long int rgbtBlue = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k >= height){continue;}
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (l < 0 || l >= width){continue;}
                    rgbtRed += copy[k][l].rgbtRed;
                    rgbtGreen += copy[k][l].rgbtGreen;
                    rgbtBlue += copy[k][l].rgbtBlue;
                    n++;
                }
            }
            RGBTRIPLE average;
            average.rgbtRed = round(rgbtRed / (float) n);
            average.rgbtGreen = round(rgbtGreen / (float) n);
            average.rgbtBlue = round(rgbtBlue / (float) n);
            image[i][j] = average;
            check[i][j] = average;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // loop to create a reference image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for Gx of particular pixel
            //int n = 0
            int factor;
            long int rgbtRed = 0;
            long int rgbtGreen = 0;
            long int rgbtBlue = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k >= height){continue;}
                if (k == i - 1 || k == i + 1)
                {
                    factor = -1;
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if (l < 0 || l >= width)
                        {
                            factor++;
                            continue;
                        }
                        rgbtRed += factor * copy[k][l].rgbtRed;
                        rgbtGreen += factor * copy[k][l].rgbtGreen;
                        rgbtBlue += factor * copy[k][l].rgbtBlue;
                        //n++;
                        factor++;
                    }
                }
                else if (k == i)
                {
                    factor = -2;
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if (l < 0 || l >= width)
                        {
                            factor += 2;
                            continue;
                        }
                        rgbtRed += factor * copy[k][l].rgbtRed;
                        rgbtGreen += factor * copy[k][l].rgbtGreen;
                        rgbtBlue += factor * copy[k][l].rgbtBlue;
                        //n++;
                        factor += 2;
                    }
                }
            }
            int GxR, GxG, GxB;
            GxR = rgbtRed;
            GxG = rgbtGreen;
            GxB = rgbtBlue;

            // for Gy

            //n = 0;
            rgbtRed = 0;
            rgbtGreen = 0;
            rgbtBlue = 0;
            for (int l = i - 1; l <= i + 1; l++)
            {
                if (l < 0 || l >= height){continue;}
                if (l == i - 1 || l == i + 1)
                {
                    factor = -1;
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        if (k < 0 || k >= width)
                        {
                            factor++;
                            continue;
                        }
                        rgbtRed += factor * copy[l][k].rgbtRed;
                        rgbtGreen += factor * copy[l][k].rgbtGreen;
                        rgbtBlue += factor * copy[l][k].rgbtBlue;
                        //n++;
                        factor++;
                    }
                }
                else if (l == i)
                {
                    factor = -2;
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        if (k < 0 || k >= width)
                        {
                            factor += 2;
                            continue;
                        }
                        rgbtRed += factor * copy[l][k].rgbtRed;
                        rgbtGreen += factor * copy[l][k].rgbtGreen;
                        rgbtBlue += factor * copy[l][k].rgbtBlue;
                        //n++;
                        factor += 2;
                    }
                }
            }
            int GyR, GyG, GyB;
            GyR = rgbtRed;
            GyG = rgbtGreen;
            GyB = rgbtBlue;

            image[i][j].rgbtRed = round(sqrt(GxR * GxR + GyR * GyR));
            image[i][j].rgbtGreen = round(sqrt(GxG * GxG + GyG * GyG));
            image[i][j].rgbtBlue = round(sqrt(GxB * GxB + GyB * GyB));
        }
    }
    return;
}
