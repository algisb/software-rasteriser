#gcc x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc
INCLUDE_PATHS = -I ./SDL-win/include/SDL 
LIBRARY_PATHS = -L ./SDL-win/lib
COMPILER_FLAGS = -w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDLmain -lSDL -lm -Wl,-Bstatic -lstdc++


#-------------------------------------------------------------------------------
Obj2.o : Obj2.cpp
	$(CC) -c Obj2.cpp -I ./ -I ./glm/glm -I ./glm/glm/gtc -I ./glm/glm/gtx

#compilation
Color.o : Color.cpp
	$(CC) -c Color.cpp -I ./

Rasterizer.o : Rasterizer.cpp
	$(CC) -c Rasterizer.cpp -I ./ -I ./glm/glm -I ./glm/glm/gtc -I ./glm/glm/gtx

main.o : main.cpp
	$(CC) -c main.cpp -I ./ -I ./SDL-win/include/SDL -I ./glm/glm -I ./glm/glm/gtc -I ./glm/glm/gtx

#linking gcc x86_64-w64-mingw32-g++
all: main.o Rasterizer.o Color.o Obj2.o
	$(CC) -o softRend main.o Rasterizer.o Color.o Obj2.o $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) 
	
