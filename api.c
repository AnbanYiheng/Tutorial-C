#include <stdio.h>
#include "api.h" 
 
int check(const char *data, int len) 
{ 
  if(len < 4)return 1;

  int cnt = 0;
  //异常的业务逻辑
  if (data[0] == 'x') { cnt++; }
  if (data[1] == 'y') { cnt++; }
  if (data[2] == 'z') { cnt++; }

  if (cnt >= 3) {
    switch (data[3]) {
      case '1': {
        // stack-buffer-underflow
        int* p = &cnt - 32; for (int i = 0; i < 32; i++) { *(p + i) = 0; }
        break;
      }
      case '2': {
        // stack-buffer-overflow 
        int* p = &cnt + 32; for (int i = 0; i < 32; i++) { *(p - i) = 0; }
        break;
      }
      case '3': {
        // bad-free
        int *p = &cnt; free(p);
        break;
      }
      case '4': {
        // double-free
        int* p = malloc(sizeof(int)); free(p); free(p);
        break;
      }
      case '5': {
        // heap-use-after-free
        int* p = malloc(sizeof(int)); free(p); *p = 123;
        break;
      }
    }
  }                             
  return 0; 
}
