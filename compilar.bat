rem TURBO C on Windows...
del *.obj
del *.exe
set path=c:\tc\bin;c:\tc\include;c:\tc\lib
tcc -Ic:\tc\include -Lc:\tc\lib *.c c:\tc\lib\graphics.lib
