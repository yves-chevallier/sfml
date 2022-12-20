#version 140
in vec3 pass_colour;
out vec4 out_Colour;
void main(void){
	//out_Colour = vec4(pass_colour, 1.0);
    out_Colour = vec4(1.0, 0.0, 0.0, 1.0);
}
