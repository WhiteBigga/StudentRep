include 'win32wxp.inc'

.code
  start:
        invoke  AllocConsole
        invoke  WriteConsole,<invoke GetStdHandle,STD_OUTPUT_HANDLE>,tex,12,dummy,0
        invoke  Sleep,-1
.end start

.data
tex     TCHAR   '123456789987654321!'

dummy   rd      1