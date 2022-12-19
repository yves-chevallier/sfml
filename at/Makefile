EXEC=a.out
all: $(EXEC)

$(EXEC): main.cpp | triangle.glsl
	g++ -o $@ $< -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
