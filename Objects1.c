#include <stdio.h>
#include <stdlib.h>

typedef struct cClass class;

struct cClass {                   // this struct is the container for our class
  int data;                       // it has data…
  void (*setValue)(class *, int); // …and a function. A pointer to a function
                                  // in this case.
};

void cClassSetValue(class *self, int value) { self->data = value; }

class *cClassCreate() {
  class *self = malloc((sizeof(class))); // gonna need some memory.
  self->data = 0;                        // …and initialise the data
  self->setValue = cClassSetValue; // …and pointers to our class functions
  return self;                     // and now we can return our 'self'
}

int main(int argc, const char *argv[]) {
  class *foo = cClassCreate(); // instantiate one object
  class *bar = cClassCreate(); // instantiate a second object
  foo->setValue(foo, 1);       // give it a value
  bar->setValue(bar, 2);
  printf("%d\n", foo->data); // output the value
  printf("%d\n", bar->data);
  free(foo); // and release its memory now we're done
  free(bar);
  return 0;
}