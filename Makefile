CC = gcc
FRAMEWORK_FLAGS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

main: main.o button.o drawings.o pomtime.o config.o lib/libraylib.a
	$(CC) -Wall $(FRAMEWORK_FLAGS) build/main.o build/button.o build/drawings.o build/pomtime.o build/config.o lib/libraylib.a -o build/main

main.o: src/main.c
	@[[ -d "build" ]] && : || mkdir build
	$(CC) -Wall src/main.c -c -o build/main.o

button.o: src/button.c
	@[[ -d "build" ]] && : || mkdir build
	$(CC) -Wall src/button.c -c -o build/button.o

drawings.o: src/drawings.c
	@[[ -d "build" ]] && : || mkdir build
	$(CC) -Wall src/drawings.c -c -o build/drawings.o

pomtime.o: src/pomtime.c
	@[[ -d "build" ]] && : || mkdir build
	$(CC) -Wall src/pomtime.c -c -o build/pomtime.o

config.o: src/config.c
	@[[ -d "build" ]] && : || mkdir build
	$(CC) -Wall src/config.c -c -o build/config.o


clean:
	rm build/main
	rm build/*.o
	rmdir build
