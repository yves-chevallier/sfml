#version 140
out vec4 out_Colour;

uniform sampler2D iChannel0;
uniform vec2 iResolution;
// uniform vec2 iMouse;
uniform float iTime;

void main(void) {
    // vec2 mouse = iMouse.xy;
    // if(mouse.x <= 0.)
    vec2 mouse = vec2(iResolution.x * (sin(iTime) + 1.) / 2., iResolution.y / 2.);
    vec3 blob = vec3(.11 - clamp(length((gl_FragCoord.xy - mouse.xy) / iResolution.x), 0., .11)) * 2.;
    vec3 stack = texture(iChannel0, gl_FragCoord.xy / iResolution.xy).xyz * vec3(0.99, .982, .93);
    out_Colour = vec4(stack + blob, 1.0);
}
