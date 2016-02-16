#include <windows.h>
#include <winerror.h>
#include <stdio.h>

int main(){
  STARTUPINFO child_1_si;
  STARTUPINFO child_2_si;

  PROCESS_INFORMATION child_1_pi;
  PROCESS_INFORMATION child_2_pi;

  DWORD child_1_creating;
  DWORD child_2_creating;

  get_warning_alert("\nTrying to create the first child process...");
  child_1_creating = create_process("child.exe", &child_1_si, &child_1_pi);
  if(!child_1_creating){
    get_error_alert("\nError on creating process / code #%ld", GetLastError());
    exit(1);
  }
  get_success_alert("\nProcess created!");

  Sleep(2000);

  get_warning_alert("\nTrying to create the second child process...");
  child_2_creating = create_process("child.exe", &child_2_si, &child_2_pi);
  if(!child_2_creating){
    get_error_alert("\nError on creating process / code #%ld", GetLastError());
    exit(1);
  }
  get_success_alert("\nProcess created!");

  for(int i = 0; i <= 20; i++){
    printf("\nParent process on step %d", i);
    Sleep(3000);
  }

  return 0;
}
