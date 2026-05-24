/* Include the system headers we need */
#include <stdio.h>
#include <stdlib.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
  size_t size;
  int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
  fprintf(stderr, "Out of memory.\n");
  exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
  /* Create the vector and a pointer to it */
  vector_t *retval, v;
  retval = &v;

  /* Initialize attributes */
  retval->size = 1;
  retval->data = malloc(sizeof(int));
  if (retval->data == NULL) {
    allocation_failed();
  }

  retval->data[0] = 0;
  return retval;
}

/* Another suboptimal way of creating a vector */
vector_t also_bad_vector_new() {
  /* Create the vector */
  vector_t v;

  /* Initialize attributes */
  v.size = 1;
  v.data = malloc(sizeof(int));
  if (v.data == NULL) {
    allocation_failed();
  }
  v.data[0] = 0;
  return v;
}

vector_t *vector_new() {
  vector_t *retval;
  retval = (vector_t *)malloc(sizeof(vector_t));
  if (retval == NULL) {
    allocation_failed();
  }
  retval->size = 1;
  retval->data = (int *)malloc(sizeof(int));
  if (retval->data == NULL) {
    free(retval);
    allocation_failed();
  }
  retval->data[0] = 0;
  return retval;
}
int vector_get(vector_t *v, size_t loc) {
  if (v == NULL) {
    fprintf(stderr, "vector_get: passed a NULL vector.\n");
    abort();
  }
  if (loc < v->size) {
    return v->data[loc];
  } else {
    return 0;
  }
}

void vector_delete(vector_t *v) {
  free(v->data);
  free(v);
}

void vector_set(vector_t *v, size_t loc, int value) {
  if (v == NULL)
    abort();
  if (loc < v->size) {
    v->data[loc] = value;
    return;
  }
  int *new_data = (int *)malloc(sizeof(int) * 2 * v->size);
  if (new_data == NULL)
    allocation_failed();
  for (int i = 0; i < v->size; i++) {
    new_data[i] = v->data[i];
  }
  for (int i = v->size; i < v->size * 2; i++) {
    new_data[i] = 0;
  }
  free(v->data);
  v->data = new_data;
  v->size *= 2;
  vector_set(v, loc, value);
}
