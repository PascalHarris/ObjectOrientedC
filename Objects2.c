#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cStringClass stringClass;

struct cStringClass {
  char *s;
  size_t size;
  void (*setString)(stringClass *, char *); // one function…
  size_t (*stringSize)(stringClass *);      // …and a second function
};

void cStringClassSetString(stringClass *self, char *str) {
  char *buf;
  self->size = strlen(str);

  buf = realloc(self->s, self->size + 1); // reallocate enough memory for
  // the new string
  if (buf) { // if successful, update self
    self->s = buf;
    strncpy(self->s, str, self->size + 1); // and copy str into our s
  }
}

size_t cStringClassStringSize(stringClass *self) {
  return self->size; // Not using this function. It's just
                     // here to show that your C class
                     // doesn't have to be monofunctional!
}

stringClass *cStringClassCreate() {
  stringClass *self = malloc((sizeof(stringClass)));

  if (self != NULL) {
    self->stringSize = cStringClassStringSize;
    self->setString = cStringClassSetString;
    self->s = NULL;
    self->size = 0;
  }
  return self;
}

int main(int argc, const char *argv[]) {
  stringClass *foo = cStringClassCreate();
  stringClass *bar = cStringClassCreate();
  foo->setString(foo, "Hello");
  bar->setString(bar, "World");
  printf("%s\n", foo->s);
  printf("%s\n", bar->s);
  foo->setString(foo, "Watchamacallit"); // Allocate more memory on the heap
  bar->setString(bar, "!");              // free memory on the heap
  printf("%s\n", foo->s);
  printf("%s\n", bar->s);
  free(foo);
  free(bar);
  return 0;
}