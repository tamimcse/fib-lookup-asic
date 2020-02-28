#include <stdint.h>

#define CNK24 60
#define CNK32 6000
#define CNK40 7000
#define CNK48 11000
#define CNK56 700
#define CNK64 700
#define CNK72 500
#define CNK80 500
#define CNK88 500
#define CNK96 500
#define CNK104 500
#define CNK112 500
#define CNK120 500
#define CNK128 500

/*chunk size is 2^8*/
#define CNK_8 256

#define SIZE16 65536
#define SIZE24 CNK24 * CNK_8
#define SIZE32 CNK32 * CNK_8
#define SIZE40 CNK40 * CNK_8
#define SIZE48 CNK48 * CNK_8
#define SIZE56 CNK56 * CNK_8
#define SIZE64 CNK64 * CNK_8

#define SIZE72 CNK72 * CNK_8
#define SIZE80 CNK80 * CNK_8
#define SIZE88 CNK88 * CNK_8
#define SIZE96 CNK96 * CNK_8
#define SIZE104 CNK104 * CNK_8
#define SIZE112 CNK112 * CNK_8
#define SIZE120 CNK120 * CNK_8
#define SIZE128 CNK128 * CNK_8

// SAIL based FIB lookup
int8_t sail (int8_t N16[SIZE16], int32_t C16[SIZE16], int8_t N24[SIZE24], int8_t C24[SIZE24], int8_t N32[SIZE32], int8_t C32[SIZE32], int64_t ip1, int64_t ip2)
{
  int i,j,k;
  uint32_t idx = ip1 >> 48;
  if (C16[idx]) {
    idx = (C16[idx] - 1) * CNK_8 + ((ip1 >> 40) & 0XFF);
    if (C24[idx]) {
      idx = (C24[idx] - 1) * CNK_8 + ((ip1 >> 32) & 0XFF);
      idx = (C16[idx] - 1) * CNK_8 + ((ip1 >> 40) & 0XFF);
      if (C32[idx]) {
        idx = (C32[idx] - 1) * CNK_8 + ((ip1 >> 24) & 0XFF);
        return N32[idx] + 5;
      } else {
        return N32[idx];
      }
    } else {
      return N24[idx];
    }
  } else {
    return N16[idx];
  }
}
