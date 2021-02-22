SRC= src/img.cpp src/vector3.cpp src/ray.cpp src/utils.cpp src/main.cpp

all:
	g++ $(SRC)

clean:
	rm a.out