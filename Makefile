#compilation
Color.o : Color.cpp
	gcc -c Color.cpp -I ./

Rasterizer.o : Rasterizer.cpp
	gcc -c Rasterizer.cpp -I ./ -I ./glm/glm -I ./glm/glm/gtc -I ./glm/glm/gtx

main.o : main.cpp
	gcc -c main.cpp -I ./ -I ./SDL/include -I ./glm/glm -I ./glm/glm/gtc -I ./glm/glm/gtx

#linking
all: main.o Rasterizer.o Color.o
	gcc -o softRend main.o Rasterizer.o Color.o ./SDL/libs/libSDL.so -lm -lstdc++
