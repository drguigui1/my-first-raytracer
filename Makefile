SRC= src/img.cpp src/vector3.cpp src/main.cpp

all:
	g++ $(SRC)

clean:
	rm a.out