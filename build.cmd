g++ -Wall -c *.cpp
windres -i resource.rc -o resource.o
g++ -Wall -o gui *.o -static-libgcc -static-libstdc++ -s -mwindows
del *.o
PAUSE