#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winerror.h>

char *substr(char *, int, int);
void cls(HANDLE);
char **split_on_lines(char *, char, int);
int symbol_occurrences_count(char *, char);
void run(HANDLE, char *, int);

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
  SetConsoleMode(input_handle, ENABLE_MOUSE_INPUT);

  run(input_handle, buff, symbol_occurrences_count(buff, '\n'));

  return 0;
}

void run(HANDLE input_handle, char *buff, int lines_count){
  INPUT_RECORD console_buff;
  DWORD written;

  char **lines = split_on_lines(buff, '\n', lines_count);

  while(1)
  {
      ReadConsoleInput(input_handle, &console_buff, 1, &written);
      if(console_buff.EventType == MOUSE_EVENT){
          MOUSE_EVENT_RECORD event = console_buff.Event.MouseEvent;

          if(event.dwEventFlags == 0)
          {
              if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
              {
                  COORD coords = event.dwMousePosition;
                  if(coords.Y < lines_count && coords.X < strlen(lines[coords.Y]))
                  {
                      char smb = lines[coords.Y][coords.X];

                      if(smb != ' ')
                      {
                          get_warning_alert("Selected: %c\n", smb);
                          printf("x: %d and y: %d\n\n", coords.X, coords.Y);
                      }

                  }

              }

              if(event.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
              {
                  get_success_alert("\nGoodbye :)");
                  exit(1);
              }
          }
      }
  }
}

void cls( HANDLE hConsole )
{
   COORD coordScreen = { 0, 0 };    // home for the cursor
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

// Get the number of character cells in the current buffer.

   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
   {
      return;
   }

   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if( !FillConsoleOutputCharacter( hConsole,        // Handle to console screen buffer
                                    (TCHAR) ' ',     // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten ))// Receive number of characters written
   {
      return;
   }

   // Get the current text attribute.

   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
   {
      return;
   }

   // Set the buffer's attributes accordingly.

   if( !FillConsoleOutputAttribute( hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten )) // Receive number of characters written
   {
      return;
   }

   // Put the cursor at its home coordinates.

   SetConsoleCursorPosition( hConsole, coordScreen );
}

char **split_on_lines(char *data, char delimiter, int lines_count)
{
    char **lines = malloc(sizeof(char*) * lines_count);

    int count = 0;
    int start = 0;

    for(int i = 0; i < strlen(data); i++){
        if(data[i] == delimiter)
        {
            char *line = substr(data, start, i);

            lines[count] = (char*) malloc(strlen(line));
            strcpy(lines[count], substr(data, start, i));
            start = i + 1;
            count++;
        }
    }

    return lines;
}

char *substr(char *string, int start, int end)
{
    char *result = (char*) malloc(end - start + 1);
    strncpy(result, string + start, end - start);
    result[end - start] = '\0';

    return result;
}

int symbol_occurrences_count(char *string, char smb){
    int count = 0;

    for(int i = 0; i < strlen(string); i++){
        if(string[i] == smb)
            count++;
    }

    return count;
}
