#include <windows.h>
#include <winerror.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  char buff[255];
  STARTUPINFO grandchild_si;
  PROCESS_INFORMATION grandchild_pi;

  memset(&grandchild_si, 0, sizeof(STARTUPINFO));
  grandchild_si.cb=sizeof(grandchild_si);

  sprintf(buff, "grandchild.exe %s %s", argv[2], argv[1]);

  DWORD created = CreateProcess(NULL, buff, NULL, NULL, FALSE,
                  NORMAL_PRIORITY_CLASS, NULL, NULL, &grandchild_si, &grandchild_pi);

  if(!created){
    get_error_alert("\nError on creating process / code #%ld", GetLastError());
    exit(1);
  }
  get_success_alert("\nProcess created!\n");

  for(int i = 0; i <= 20; i++){
    get_success_alert("%s: ", argv[1]);
    printf("on step %d\n", i);
    Sleep(2000);
  }

  return 0;
}
