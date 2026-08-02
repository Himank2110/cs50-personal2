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
            BYTE average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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
        while (!(j == n || (j + 1 == n)));
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
                if (k < 0 || k >= height)
                {
                    continue;
                }
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (l < 0 || l >= width)
                    {
                        continue;
                    }
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
    // for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for Gx of particular pixel

            int factor;
            long int rgbtRed = 0;
            long int rgbtGreen = 0;
            long int rgbtBlue = 0;
            for (int k = i - 1; k <= i + 1;
                 k++) // pattern to go about the matrix around chosen pixel
            {
                if (k < 0 || k >= height) // checks for boundary
                {
                    continue;
                }
                if (k == i - 1 || k == i + 1) // checks whether factor should be -1 or -2 series
                {
                    factor = -1;
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if (l < 0 || l >= width) // checks for boundary
                        {
                            factor++;
                            continue;
                        }
                        rgbtRed += factor * copy[k][l].rgbtRed;
                        rgbtGreen += factor * copy[k][l].rgbtGreen;
                        rgbtBlue += factor * copy[k][l].rgbtBlue;
                        factor++;
                    }
                }
                else if (k == i) // checks for which series factor should be
                {
                    factor = -2;
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if (l < 0 || l >= width) // checks for boundary
                        {
                            factor += 2;
                            continue;
                        }
                        rgbtRed += factor * copy[k][l].rgbtRed;
                        rgbtGreen += factor * copy[k][l].rgbtGreen;
                        rgbtBlue += factor * copy[k][l].rgbtBlue;
                        factor += 2;
                    }
                }
            }
            int GxR, GxG, GxB; // Gx RGB values
            GxR = rgbtRed;
            GxG = rgbtGreen;
            GxB = rgbtBlue;

            // for Gy

            rgbtRed = 0;
            rgbtGreen = 0;
            rgbtBlue = 0;
            for (int l = j - 1; l <= j + 1;
                 l++) // pattern to go about the matrix around chosen pixel
            {
                if (l < 0 || l >= width) // checks for boundary
                {
                    continue;
                }
                if (l == j - 1 || l == j + 1) // checks whether factor should be -1 or -2 series
                {
                    factor = -1;
                    for (int k = i - 1; k <= i + 1; k++)
                    {
                        if (k < 0 || k >= height) // checks for boundary
                        {
                            factor++;
                            continue;
                        }
                        rgbtRed += factor * copy[k][l].rgbtRed;
                        rgbtGreen += factor * copy[k][l].rgbtGreen;
                        rgbtBlue += factor * copy[k][l].rgbtBlue;
                        factor++;
                    }
                }
                else if (l == j) // checks for which series factor should be
                {
                    factor = -2;
                    for (int k = i - 1; k <= i + 1; k++)
                    {
                        if (k < 0 || k >= height) // checks for boundary
                        {
                            factor += 2;
                            continue;
                        }
                        rgbtRed += factor * copy[k][l].rgbtRed;
                        rgbtGreen += factor * copy[k][l].rgbtGreen;
                        rgbtBlue += factor * copy[k][l].rgbtBlue;
                        factor += 2;
                    }
                }
            }
            int GyR, GyG, GyB; // Gy RGB values
            GyR = rgbtRed;
            GyG = rgbtGreen;
            GyB = rgbtBlue;
            // calculate resultant of Gx and Gy values
            int x = round(sqrt(GxR * GxR + GyR * GyR));
            int y = round(sqrt(GxG * GxG + GyG * GyG));
            int z = round(sqrt(GxB * GxB + GyB * GyB));
            // cap each result to 225
            if (x > 255)
            {
                x = 255;
            }
            if (y > 255)
            {
                y = 255;
            }
            if (z > 255)
            {
                z = 255;
            }
            // put the final resultant in current pixel
            image[i][j].rgbtRed = x;
            image[i][j].rgbtGreen = y;
            image[i][j].rgbtBlue = z;
        }
    }
    return;
}
