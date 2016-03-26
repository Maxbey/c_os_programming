#include <windows.h>
#include <winerror.h>

int main(int argc, char *argv[]){
  for(int i = 0; i <= 40; i++){
    get_warning_alert("%s of %s: ", argv[1], argv[2]);
    printf("on step %d\n", i);
    Sleep(1000);
  }

  return 0;
}
