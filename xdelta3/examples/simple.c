#define NOT_MAIN 1

#include "xdelta3.h"
#include "xdelta3.c"

int main(int argc, char **argv) {
  uint8_t *delta_buf = NULL;
  size_t to_len, delta_alloc;
  usize_t delta_size;

  int level = 1;
  int flags = 0; //(level << XD3_COMPLEVEL_SHIFT) & XD3_COMPLEVEL_MASK;
  char *to = "after.txt";

  char *to_str = "Xdelta version 3 is a C library and command-line tool for delta compression using VCDIFF/RFC 3284 streams. after\n";
  to_len = strlen(to_str);

  char *from_str = "Xdelta version 3 is a C library and command-line tool for delta compression using VCDIFF/RFC 3284 streams.\n";
  size_t from_len = strlen(from_str);

//  from_buf = (uint8_t*) main_malloc(from_len);
//  memcpy(from_buf, from_str, from_len);

//  fprintf(stdout, "from buf: '%s'\n", from_str);
//  fprintf(stdout, "from buf length: %d\n", (int)from_len);

  delta_alloc = to_len * 11 / 10;
  delta_buf = main_malloc(delta_alloc);

  int ret = xd3_encode_memory(to_str, to_len, from_str, from_len, delta_buf, &delta_size, delta_alloc, flags);
  if (ret != 0) {
    fprintf(stderr, "encode failure: %d: %s\n", ret, xd3_strerror(ret));
  } else {
    fprintf(stderr, "delta %zd\n", delta_size);
//    fprintf(stderr, "delta:\n%s\n", delta_buf);
  }

  // TODO free to_str and from_str?
  main_free(delta_buf);
  return ret;
}
