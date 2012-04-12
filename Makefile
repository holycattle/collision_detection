sdlanim:	lesson16.cpp
	g++ `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf lesson16.cpp -o lesson16

clean:
	rm lesson16
