#include <stdio.h>
#include <stdarg.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"

extern void get_error_alert(const char *, ...);
extern void get_success_alert(const char *, ...);
void get_colored_alert(char *, char *, va_list);