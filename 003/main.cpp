#include <dlfcn.h>
#include <string.h>

#include "hello.h"

int main ()
{
  void *dl_handle;
  char *error;
  void (*func)();

  //открываем совместно используемую библиотеку
  dl_handle = dlopen( "./libHello.so", RTLD_LAZY );
  if (!dl_handle )
  {
    printf(" error open lib %s \n",dlerror());
    return 1;
  } 

  //адрес функции в библиотеке
  func = dlsym(dl_handle,"hello_print");
  //if (func!=NULL)
  {  //адрес функции существует
     
     //вызываем функцию по найденному адресу
     //func=(func*)ptr;
     //	(*func)();
  }
  
  dlclose(dl_handle);

return 0;
}
