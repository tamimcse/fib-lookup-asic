#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DIRSIZE 65536
#define SIZE16 400
#define SIZE22 3000
#define SIZE28 15000
#define SIZE34 14000
#define SIZE40 15000
#define SIZE46 21000
#define SIZE52 2000
#define SIZE58 2000
#define SIZE64 1000
#define SIZE70 100
#define SIZE76 100
#define SIZE82 100
#define SIZE88 100
#define SIZE94 100
#define SIZE100 100
#define SIZE106 100
#define SIZE112 100
#define SIZE118 100
#define SIZE124 100
#define N_SIZE 1500000

#define MSK 0X8000000000000000ULL

struct poptrie_node {
    uint64_t vec;
    uint64_t leafvec;
    uint32_t base0;
    uint32_t base1;
};

int8_t popcnt16 (int16_t input) {
  switch (input) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 1;
    case 3: return 2;
    case 4: return 1;
    case 5: return 2;
    case 6: return 2;
    case 7: return 3;
    case 8: return 1;
    case 9: return 2;
    case 10: return 2;
    case 11: return 3;
    case 12: return 2;
    case 13: return 3;
    case 14: return 3;
    case 15: return 4;
    case 16: return 1;
    case 17: return 2;
    case 18: return 2;
    case 19: return 3;
    case 20: return 2;
    case 21: return 3;
    default: return 9;
  }
}

int8_t popcnt64_variant1 (int64_t input) {
  return popcnt16 (input & 0XFFFF) + popcnt16 ((input >> 16) & 0XFFFF) + popcnt16 ((input >> 32) & 0XFFFF) + popcnt16 (input >> 48);
}

int8_t popcnt64 (int64_t input) {
  int8_t count = 0;
  while (input) {
    count ++;
    input &= input - 1;
  }
  return count;
}

// SAIL based FIB lookup
int8_t poptrie (int8_t N16[SIZE16], int16_t dirC[DIRSIZE], struct poptrie_node B16[SIZE16], struct poptrie_node B22[SIZE22], struct poptrie_node B28[SIZE28], struct poptrie_node B34[SIZE34], int32_t C16[SIZE16], int8_t leafN[N_SIZE], int64_t ip1, int64_t ip2)
{
  int i,j,k;
  uint32_t idx = ip1 >> 48;
  struct poptrie_node node;
  uint32_t off;
  uint32_t n_idx;

  if (dirC[idx]) {
    node = B16[dirC[idx] - 1];
    off = (ip1 >> 42) & 63;
    if (node.vec & (1ULL << off)) {
      idx = node.base0 + popcnt64(node.vec & ((2ULL << off) - 1)) - 1;
      node = B22[idx];
      off = (ip1 >> 36) & 63;
      if (node.vec & (1ULL << off)) {
        idx = node.base0 + popcnt64(node.vec & ((2ULL << off) - 1)) - 1;
        node = B28[idx];
        off = ((ip1 >> 30) & 63);
        if (node.vec & (1ULL << off)) {
          idx = node.base0 + popcnt64(node.vec & ((2ULL << off) - 1)) - 1;
          node = B34[idx];
          off = ((ip1 >> 24) & 63);
        }
      }
    }
    //Reached the leaf
    if (node.leafvec & (1ULL << off)) {
      n_idx = node.base1 + popcnt64(node.leafvec & ((2ULL << off) - 1)) - 1;
      return leafN[n_idx];
    } else {
      return 1;//default next-hop
    }
  } else {
    return N16[idx];
  }
}
