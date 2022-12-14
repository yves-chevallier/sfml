
uniform vec2 resolution;
uniform float size;

void main(void) {
    vec2 p = gl_FragCoord.xy;
    vec2 uv = p/resolution.xy;
    vec2 pos = 2.5 - uv;
    //pos.y /= resolution.x/resolution.y;


    float dist = pow(1.0/length(pos) * 0.1, 0.8);
    vec3 col = dist * vec3(1.0, 0.5, 0.25);

    gl_FragColor = vec4(1.0 - exp( -col ), 1.0);
}
