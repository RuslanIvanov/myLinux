#include <stdio.h>
include "hello.h"

int main ()
{
  void *dl_handle;
  char *error;
  float (*func)(float);

  //открываем совместно используемую библиотеку
  dl_handle = dlopen( lib, LD );

  //адрес функции в библиотеке
  func = dlsym(dl_handle,
//вызываем функцию по найденному адресу

(*func)(argument); //%f

dlclose(dl_handle);

  hello_print();

return 0;
}
