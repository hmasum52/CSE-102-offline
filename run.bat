rmdir out
mkdir out
g++ -IOpenGL\include -w -c 1805052.cpp -o Demo.o
g++ -LOpenGL\lib Demo.o -o out\Demo.exe -lGlaux -lGLU32 -lglui32 -lglut32 -lOPENGL32 -lgdi32 -lwinmm
xcopy /y openGL\dll\glut32.dll out
del Demo.o