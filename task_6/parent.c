#include <windows.h>
#include <winerror.h>
#include <stdio.h>

int main(){
  DWORD exit_code, terminated;

  STARTUPINFO child_1_si;
  STARTUPINFO child_2_si;

  PROCESS_INFORMATION child_1_pi;
  PROCESS_INFORMATION child_2_pi;

  HANDLE job_handle = CreateJobObject(NULL, "job");

  memset(&child_1_si, 0, sizeof(STARTUPINFO));
  child_1_si.cb=sizeof(child_1_si);

  memset(&child_2_si, 0, sizeof(STARTUPINFO));
  child_2_si.cb=sizeof(child_2_si);

  get_warning_alert("\nTrying to create the first child process...");
  DWORD child_1_created = CreateProcess(NULL, "child.exe ChildOne GrandChildOne", NULL, NULL, FALSE,
                  NORMAL_PRIORITY_CLASS, NULL, NULL, &child_1_si, &child_1_pi);

  if(!child_1_created){
    get_error_alert("\nError on creating process / code #%ld", GetLastError());
    exit(1);
  }
  get_success_alert("\nProcess created!");

  get_warning_alert("\nTrying to create the second child process...");
  DWORD child_2_created = CreateProcess(NULL, "child.exe ChildTwo GrandChildTwo", NULL, NULL, FALSE,
                  NORMAL_PRIORITY_CLASS, NULL, NULL, &child_2_si, &child_2_pi);

  if(!child_2_created){
    get_error_alert("\nError on creating process / code #%ld", GetLastError());
    exit(1);
  }
  get_success_alert("\nProcess created!");

  AssignProcessToJobObject(job_handle, child_2_pi.hProcess);


  for(int i = 0; i <= 20; i++){
    get_error_alert("Parent: ");
    printf("on step %d\n", i);

    if(i == 7)
    {
      GetExitCodeProcess(child_1_pi.hProcess, &exit_code);
      terminated = TerminateProcess(child_1_pi.hProcess, (UINT) exit_code);

      if(!terminated)
      {
        get_error_alert("\nTerminating error %d\n", GetLastError());
      }
      else
      {
        get_success_alert("\nThe first child process terminated\n");
      }
    }

    if(i == 10)
    {
      GetExitCodeProcess(job_handle, &exit_code);
      terminated = TerminateJobObject(job_handle, (UINT) exit_code);

      if(!terminated)
      {
        get_error_alert("\nJob terminating error %d\n", GetLastError());
      }
      else
      {
        get_success_alert("\nJob terminated\n");
      }
    }

    Sleep(3000);
  }

  return 0;
}
