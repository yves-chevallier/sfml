#version 140
out vec4 out_Colour;

uniform sampler2D iChannel0;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

void main(void) {
    vec2 mouse = iMouse.xy;
    vec3 color = vec3(42.0/200, 120.0/200, 200.0/200.0);
    vec2 uv = (gl_FragCoord.xy - mouse.xy) / iResolution.xy * (sin(iTime*25.0)/1.0 + 6.0);
    vec3 blob = 1.0 - vec3(smoothstep(length(uv), 0, .02));
    vec3 stack = texture(iChannel0, gl_FragCoord.xy / iResolution.xy).xyz;
    stack -= vec3(0.005);
    out_Colour = vec4(stack + color * blob* 0.2, 1.0);
}
