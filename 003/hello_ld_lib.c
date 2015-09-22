
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "hello_lib.h"
typedef int (*my_func)( char* );
int main( int argc, char *argv[] ) {
char *messg = "Text message\n";
   // Открываем совместно используемую библиотеку
   void *dl_handle = dlopen( "./libhello.so", RTLD_LAZY );
   if( !dl_handle ) {
      printf( "ERROR open: %s\n", dlerror() );
      return 3;
   }
   //  Находим адрес функции в библиотеке
   my_func func = dlsym( dl_handle, "print_hello" );
   char *error = dlerror();
   if( error != NULL ) {
      printf( "ERROR address: %s\n", dlerror() );
      return 4;
   }
   // Вызываем функцию по найденному адресу
   int res = (*func)( messg );
   // Закрываем библиотеку
   dlclose( dl_handle );
   return res;
}


