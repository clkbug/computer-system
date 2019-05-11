#include "02.h"

// 02.55
void hw02_55() {
  int a = 0x12345678;
  show_bytes((byte_pointer)&a, sizeof(int));
  // little endian  <=> 78 56 34 12
  // big endian     <=> 12 34 56 78
}

// 02.56 - 57 skip

// 02.58
int is_little_endian() {
  int a = 0x12345678;
  char* p = (char*)&a;
  if (*p == 0x12) {
    return 0;
  } else {
    return 1;
  }
}

void hw02_58() {
  if (is_little_endian() == 1) {
    printf("02.58... little endian\n");
  }
}

int main() {
  hw02_55();

  hw02_58();

  return 0;
}
