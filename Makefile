SRC= src/img.cpp src/color.cpp src/main.cpp

all:
	g++ $(SRC)

clean:
	rm a.out