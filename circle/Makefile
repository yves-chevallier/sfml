EXEC=a.out
all: $(EXEC)

$(EXEC): glow.cpp | glow.glsl
	g++ -o $@ $< -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
