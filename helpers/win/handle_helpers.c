#include "handle_helpers.h"

HANDLE get_std_handle(int type){
  HANDLE handle = GetStdHandle(type);

  if(handle == INVALID_HANDLE_VALUE)
      return (HANDLE) -1;

  return handle;
}

HANDLE get_input_handle(){
  return get_std_handle(STD_INPUT_HANDLE);
}

HANDLE get_output_handle(){
  return get_std_handle(STD_OUTPUT_HANDLE);
}
