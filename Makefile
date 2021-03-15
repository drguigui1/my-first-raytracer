SRC= src/img_io.cpp src/img.cpp src/vector3.cpp src/material.cpp src/triangle.cpp src/sphere.cpp src/plane.cpp src/AABB_cube.cpp src/ray.cpp src/utils.cpp src/scene.cpp
MAIN= src/main.cpp

all:
	g++ $(SRC) $(MAIN)

release:
	g++ -O3 $(SRC) $(MAIN)

debug:
	g++ -g $(SRC) $(MAIN)

clean:
	rm a.out
