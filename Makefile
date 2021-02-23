SRC= src/img.cpp src/vector3.cpp src/sphere.cpp src/ray.cpp src/utils.cpp src/scene.cpp
MAIN= src/main.cpp

all:
	g++ $(SRC) $(MAIN)

debug:
	g++ -g $(SRC) $(MAIN)

clean:
	rm a.out