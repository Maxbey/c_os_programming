#include <string.h>
#include <windows.h>
#include <winerror.h>

void run(HANDLE, HANDLE);
char* get_word(HANDLE, COORD);

int main(int argc, char *argv[]){
  char buff[1000];
  DWORD readed, written, err_code;

  HANDLE output_handle = get_output_handle();
  HANDLE input_handle = get_input_handle();
  HANDLE file_handle = CreateFile(argv[1],
                     GENERIC_READ,
                     FILE_SHARE_READ,
                     NULL,
                     OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL,
                     NULL);

  if(file_handle == INVALID_HANDLE_VALUE)
  {
      err_code = GetLastError();
      get_error_alert("Error on opening / code #%d", err_code);
      exit(1);
  }

  cls(output_handle);
  ReadFile(file_handle, buff, sizeof(buff), &readed, 0);
  WriteFile(output_handle, buff, readed, &written, 0);

  run(input_handle, output_handle);

  return 0;
}

void run(HANDLE input_handle, HANDLE output_handle){
  INPUT_RECORD console_buff;
  DWORD written;

  while(1)
  {
      ReadConsoleInput(input_handle, &console_buff, 1, &written);
      if(console_buff.EventType == MOUSE_EVENT){
          MOUSE_EVENT_RECORD event = console_buff.Event.MouseEvent;

          if(event.dwEventFlags == 0)
          {
              if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
              {
                  DWORD readed;
                  COORD coords = event.dwMousePosition;
                  char result[2];

                  ReadConsoleOutputCharacter(output_handle, (LPTSTR) result, 1, coords, (LPDWORD) &readed);

                  if(result[0] != ' ')
                      get_warning_alert("Selected word: %s\n", get_word(output_handle, coords));
              }

              if(event.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
              {
                  get_success_alert("\nGoodbye :)\n");
                  exit(1);
              }
          }
      }
  }
}

char* get_word(HANDLE output_handle, COORD coords){
  char* result = "";
  DWORD readed;
  char smb[1];

  while(coords.X > 0)
  {
    ReadConsoleOutputCharacter(output_handle, (LPTSTR) smb, 1, coords, (LPDWORD) &readed);
    if(smb[0] == ' ')
      break;

      coords.X--;
  }

  if(coords.X > 0)
    coords.X += 1;

    result[0] = '\0';
    while(1)
    {
      ReadConsoleOutputCharacter(output_handle, (LPTSTR) smb, 1, coords, (LPDWORD) &readed);
      if(smb[0] == ' '){
        break;
      }

        strncat(result, &smb[0], 1);
        coords.X++;
    }

    return result;
}
