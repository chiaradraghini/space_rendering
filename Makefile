CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
INC=-I./headers


a15: A15.cpp shaders
	g++ $(CFLAGS) $(INC) -o a15 A15.cpp $(LDFLAGS)

.PHONY: test clean

test: a15
	./a15

clean:
	rm -f a15
