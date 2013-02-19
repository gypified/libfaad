
#include <stdio.h>
#include <neaacdec.h>

int main () {
  unsigned long c = NeAACDecGetCapabilities();
  printf("NeAACDecGetCapabilities() - %lu\n", c);
  return 0;
}
