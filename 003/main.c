#include <dlfcn.h>
#include <string.h>
//#include <stdlib.h>

#include "hello.h"

int main ()
{
  void *dl_handle;
  void (*func)();
  char *error;

  //открываем совместно используемую библиотеку
  dl_handle = dlopen( "./libHello.so", RTLD_LAZY );
  if (!dl_handle )
  {
    printf(" error dlopen %s \n",dlerror());
    exit(1);
  } 

  //адрес функции в библиотеке
  func = dlsym(dl_handle,"hello_print");
  error = dlerror();

  if (error != NULL)
  {  
    printf(" error dlsym %s \n",dlerror());
    exit(2);
  }

  //адрес функции существует
  //вызываем функцию по найденному адресу
  (*func)();

  dlclose(dl_handle);

return 0;
}
