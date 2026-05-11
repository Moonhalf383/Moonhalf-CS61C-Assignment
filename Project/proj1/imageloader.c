/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include "imageloader.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename) {
  Image *imageData = (Image *)malloc(sizeof(Image));
  FILE *fp = fopen(filename, "r");
  char format[2];
  int color_range = 255;
  fscanf(fp, "%s", format);
  fscanf(fp, "%d %d", &imageData->cols, &imageData->rows);
  fscanf(fp, "%d", &color_range);
  imageData->image = (Color **)malloc(imageData->rows * sizeof(Color *));
  for (int i = 0; i < imageData->rows; i++) {
    imageData->image[i] = (Color *)malloc(imageData->cols * sizeof(Color));
  }
  for (int i = 0; i < imageData->cols * imageData->rows; i++) {
    Color *target_image =
        &imageData->image[i / imageData->cols][i % imageData->cols];
    fscanf(fp, "%hhu", &target_image->R);
    fscanf(fp, "%hhu", &target_image->G);
    fscanf(fp, "%hhu", &target_image->B);
  }
  fclose(fp);
  return imageData;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the
// image's data.
void writeData(Image *image) {
  // YOUR CODE HERE
  printf("P3\n");
  printf("%d %d\n", image->cols, image->rows);
  printf("%d\n", 255);
  for (int row = 0; row < image->rows; row++) {
    for (int col = 0; col < image->cols; col++) {
      Color *target_color = &image->image[row][col];
      printf("%hhu %hhu %hhu", target_color->R, target_color->G,
             target_color->B);
      if (col == image->cols - 1)
        printf("\n");
      else
        printf("   ");
    }
  }
}

// Frees an image
void freeImage(Image *image) {
  // YOUR CODE HERE
  for (int i = 0; i < image->rows; i++) {
    free(image->image[i]);
  }
  free(image->image);
  free(image);
}
