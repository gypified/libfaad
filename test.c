
#include <stdio.h>
#include <neaacdec.h>

int main () {
  printf("libfaad2 version: %s\n", FAAD2_VERSION);

  unsigned long c = NeAACDecGetCapabilities();
  printf("NeAACDecGetCapabilities() - %lu\n", c);
  return 0;
}
