#version 140
out vec4 out_Colour;

uniform sampler2D iChannel0;
uniform vec2 iResolution;

void main(void) {
    out_Colour = vec4(texture(iChannel0, gl_FragCoord.xy/iResolution).xyz, 1.0);
}
