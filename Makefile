SRC= src/img_io.cpp src/img.cpp src/vector3.cpp src/material.cpp src/sphere.cpp src/plane.cpp src/ray.cpp src/utils.cpp src/scene.cpp
MAIN= src/main.cpp

all:
	g++ $(SRC) $(MAIN)

debug:
	g++ -g $(SRC) $(MAIN)

clean:
	rm a.out