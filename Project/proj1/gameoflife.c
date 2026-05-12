/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include "imageloader.h"
#include <complex.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Determines what color the cell at the given row/col should be. This function
// allocates space for a new Color. Note that you will need to read the eight
// neighbors of the cell in question. The grid "wraps", so we treat the top row
// as adjacent to the bottom row and the left column as adjacent to the right
// column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule) {
  Color *newColor = (Color *)malloc(sizeof(Color));
  Color curColor = image->image[row][col];
  int width = image->cols;
  int height = image->rows;
  // 对三个通道、每个通道8个bit统计邻居数量。
  int neighbourCount[3][8] = {0};
  // 对目标格子周围8个格子统计其三个通道的数值。
  uint8_t grid[8][3] = {0};
  int index = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int targetRow = (row + i + height) % height;
      int targetCol = (col + j + width) % width;
      if (targetRow == row && targetCol == col)
        continue;
      grid[index][0] = image->image[targetRow][targetCol].R;
      grid[index][1] = image->image[targetRow][targetCol].G;
      grid[index][2] = image->image[targetRow][targetCol].B;
      index++;
    }
  }
  for (int chan = 0; chan < 3; chan++) {
    for (int bit = 0; bit < 8; bit++) {
      uint8_t target = 1 << bit;
      for (int i = 0; i < 8; i++) {
        if (grid[i][chan] & target)
          neighbourCount[chan][bit]++;
      }
      // printf("chan: %d  bit: %d neighbour: %d", chan, bit,
      // neighbourCount[chan][bit]);
    }
  }
  uint8_t curChan[3] = {curColor.R, curColor.G, curColor.B};
  for (int chan = 0; chan < 3; chan++) {
    for (int bit = 0; bit < 8; bit++) {
      int ptr = neighbourCount[chan][bit];
      if (curChan[chan] & (1 << bit))
        ptr += 9;
      if (rule & (1 << ptr))
        curChan[chan] |= (1 << bit);
      else
        curChan[chan] &= ~(1 << bit);
    }
  }
  newColor->R = curChan[0];
  newColor->G = curChan[1];
  newColor->B = curChan[2];
  return newColor;
  // YOUR CODE HERE
}

// The main body of Life; given an image and a rule, computes one iteration of
// the Game of Life. You should be able to copy most of this from
// steganography.c
Image *life(Image *image, uint32_t rule) {
  Image *newImage = (Image *)malloc(sizeof(Image));
  newImage->rows = image->rows;
  newImage->cols = image->cols;
  newImage->image = (Color **)malloc(sizeof(Color *) * image->rows);
  for (int i = 0; i < image->rows; i++) {
    newImage->image[i] = (Color *)malloc(sizeof(Color) * image->cols);
  }
  for (int i = 0; i < image->rows; i++) {
    for (int j = 0; j < image->cols; j++) {
      Color *newColor = evaluateOneCell(image, i, j, rule);
      newImage->image[i][j] = *newColor;
      free(newColor);
    }
  }
  return newImage;
  // YOUR CODE HERE
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then
prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this
will be a string. You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you
should exit with code -1. Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv) {
  if (argc <= 2) {
    printf("usage: ./gameOfLife filename rule\n");
    printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
    printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
    return -1;
  }
  Image *inputImage = readData(argv[1]);
  if (inputImage == NULL)
    return -1;
  // writeData(inputImage);
  Image *result = life(inputImage, (uint32_t)strtol(argv[2], NULL, 16));
  writeData(result);
  freeImage(inputImage);
  freeImage(result);
  return 0;
}
