#include "console_helpers.h"
#include <wincon.h>
#include <string.h>

void cls(HANDLE hConsole)
{
   COORD coordScreen = {0, 0};
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

   GetConsoleScreenBufferInfo(hConsole, &csbi);

   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   FillConsoleOutputCharacter(hConsole,
                                    (TCHAR) ' ',
                                    dwConSize,
                                    coordScreen,
                                    &cCharsWritten);

   SetConsoleCursorPosition(hConsole, coordScreen);
}

void get_alert(HANDLE console_handle, char* text, WORD attrs){
  COORD coordScreen;
  DWORD written;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;

  GetConsoleScreenBufferInfo(console_handle, &csbi);
  coordScreen.X = csbi.dwSize.X / 2;
  coordScreen.Y = 10;
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  SetConsoleTextAttribute(console_handle, attrs);
  SetConsoleCursorPosition(console_handle, coordScreen);
  WriteFile(console_handle, text, strlen(text), &written, 0);
  SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void print_error_alert(HANDLE console_handle, char* text){
  cls(console_handle);
  get_alert(console_handle, text, FOREGROUND_RED);
}

void print_warning_alert(HANDLE console_handle, char* text){
  cls(console_handle);
  get_alert(console_handle, text, FOREGROUND_INTENSITY);
}

void print_success_alert(HANDLE console_handle, char* text){
  cls(console_handle);
  get_alert(console_handle, text, FOREGROUND_GREEN);
}
