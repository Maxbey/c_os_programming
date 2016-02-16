#include <windows.h>
#include <winerror.h>
#include <stdio.h>

int main(){
  DWORD created;
  STARTUPINFO grandchild_si;
  PROCESS_INFORMATION grandchild_pi;

  memset(&grandchild_si, 0, sizeof(STARTUPINFO));
  grandchild_si.cb=sizeof(grandchild_si);

  created = CreateProcess(NULL, "grandchild.exe", NULL, NULL, FALSE,
                  NORMAL_PRIORITY_CLASS, NULL, NULL, &grandchild_si, &grandchild_pi);

  get_warning_alert("\nStarted creating of process...\n");
  if(!created){
    get_error_alert("\nError on creating process / code #%ld", GetLastError());
    exit(1);
  }

  get_success_alert("\nProcess successfuly created");

  for(int i = 0; i <= 20; i++){
    printf("\nChild process on step %d", i);
    Sleep(2000);
  }

  return 0;
}
