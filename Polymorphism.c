#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SQUARE_TYPE 0
#define CIRCLE_TYPE 1

/* Super Class */
typedef struct shape shapeClass;

typedef struct shape {
  int type;
  void *thisShape;
  float width, height;
  float (*getArea)(void *);
} shape;

/* Ellipse Class */
typedef struct shape_ellipse ellipseClass;

typedef struct shape_ellipse {
  float (*getArea)(shapeClass *);
} shape_ellipse;

float shapeClassGetEllipseArea(shapeClass *self) {
  return (self->width / 2) * (self->height / 2) * M_PI;
}

ellipseClass *ellipseClassCreate() {
  ellipseClass *self = malloc((sizeof(ellipseClass)));
  self->getArea = shapeClassGetEllipseArea;
  return self;
}

/* Square Class */
typedef struct shape_square squareClass;

typedef struct shape_square {
  float (*getArea)(shapeClass *);
} shape_square;

float shapeClassGetSquareArea(shapeClass *self) {
  return self->width * self->height;
}

squareClass *squareClassCreate() {
  squareClass *self = malloc((sizeof(squareClass)));
  self->getArea = shapeClassGetSquareArea;
  return self;
}

/* Super Class */
void *shapeClassCreate(int shapeType, float width, float height) { // Constructor
  shapeClass *self = malloc((sizeof(shapeClass)));
  if (shapeType == SQUARE_TYPE) {
    self->thisShape = squareClassCreate();
    self->getArea = (void *)((squareClass *)self->thisShape)->getArea;
  } else if (shapeType == CIRCLE_TYPE) {
    self->thisShape = ellipseClassCreate();
    self->getArea = (void *)((ellipseClass *)self->thisShape)->getArea;
  } else {
    return NULL;
  }
  self->type = shapeType;
  self->width = width;
  self->height = height;
  return self;
}

void destroyShape(void *shape) { // Destructor
  free(((shapeClass *)shape)->thisShape);
  free(shape);
}

/* Main */
int main(int argc, char *argv[]) {
  float clives_number = 27.0;
  shapeClass *ellipse =
      shapeClassCreate(CIRCLE_TYPE, clives_number, clives_number);
  shapeClass *square =
      shapeClassCreate(SQUARE_TYPE, clives_number, clives_number);
  float ellipseArea = ellipse->getArea(ellipse);
  float squareArea = square->getArea(square);
  printf("%f\n", ellipseArea);
  printf("%f\n", squareArea);
  destroyShape(ellipse);
  destroyShape(square);
}