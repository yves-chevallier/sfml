#version 140
out vec4 out_Colour;

uniform sampler2D iChannel0;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

void main(void) {
    vec2 mouse = iMouse.xy;
    vec3 color = vec3(42.0/200, 120.0/200, 200.0/200.0);
    vec3 blob = vec3(.11 - clamp(length((gl_FragCoord.xy - mouse.xy) / iResolution.x * 5.0), 0., .111)) * 2.;
    vec3 stack = texture(iChannel0, gl_FragCoord.xy / iResolution.xy).xyz * color;
    out_Colour = vec4(stack + blob, 1.0);
}
