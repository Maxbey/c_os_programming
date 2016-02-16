#include <windows.h>

extern DWORD create_process(char *, STARTUPINFO, PROCESS_INFORMATION);
extern DWORD terminate_process(HANDLE);

DWORD create_process(char *name, STARTUPINFO si, PROCESS_INFORMATION pi){
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb=sizeof(si);

    DWORD created = CreateProcess(NULL, name, NULL, NULL, FALSE,
                    NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);

    return created;
}

DWORD terminate_process(HANDLE process_handle){
    LPDWORD exit_code;
    GetExitCodeProcess(process_handle, &exit_code);

    DWORD terminated = TerminateProcess(process_handle, exit_code);

    return terminated;
}
