#include <stdio.h>
#include <dlfcn.h>
#include "hello.h"


int main ()
{
  void *dl_handle;
  char *error;
  float (*func)(float);

  //открываем совместно используемую библиотеку
  dl_handle = dlopen( lib, RTLD_LAZY );
  if (dl_handle != NULL)
  {
    printf(" %s \n",dlerror());
    return;
  } 

  //адрес функции в библиотеке
  void *ptr =dlsym(dl_handle,"hello_print");	//imya funkcii
  if (*ptr)
  {
    printf("");
  }
  //вызываем функцию по найденному адресу
  func(3.14);

  dlclose(dl_handle);

  hello_print();

return 0;
}
