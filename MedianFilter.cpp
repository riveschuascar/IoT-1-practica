#include "MedianFilter.h"

MedianFilter3::MedianFilter3() {
  idx = 0;
  filled = false;
  buf[0] = buf[1] = buf[2] = 0;
}
void MedianFilter3::push(int v) {
  buf[idx++] = v;
  if (idx >= 3) {
    idx = 0;
    filled = true;
  }
}

int MedianFilter3::median() {
  if (!filled) {
    // ordenar parcial de los idx actuales (simple strategy: copy non-cero)
    int tmp[3] = { buf[0], buf[1], buf[2] };
    // contemos cuantos son no -1 (validos)
    int arr[3];
    int n = 0;
    for (int i = 0; i < 3; i++)
      if (tmp[i] != -1) { arr[n++] = tmp[i]; }
    if (n == 0) return -1;
    if (n == 1) return arr[0];
    if (n == 2) { return (arr[0] + arr[1]) / 2; }
  }
  // si está lleno o hay 3 valores: calcular mediana robusta (simple sort)
  int a = buf[0], b = buf[1], c = buf[2];
  // ordenamiento manual pequeño
  if (a > b) {
    int t = a;
    a = b;
    b = t;
  }
  if (b > c) {
    int t = b;
    b = c;
    c = t;
  }
  if (a > b) {
    int t = a;
    a = b;
    b = t;
  }
  return b;
}

void MedianFilter3::reset() {
  idx = 0;
  filled = false;
  buf[0] = buf[1] = buf[2] = 0;
}
