
uniform vec2 resolution;
uniform float size;
uniform vec2 tail[4];
uniform vec2 mouse;
void main(void) {
    vec2 p = gl_FragCoord.xy / resolution.xy;
    float d = 0.0;
    for (int i = 0; i < 4; i++) {
        vec2 u = tail[i];
        vec2 q;
        q.x = p.x - u.x / resolution.x;
        q.y = p.y + u.y / resolution.y;
        float dist = pow(1.0/length(q) * 0.1, 1.5);
        d += dist;
    }
    vec3 col = d * vec3(1.0, 0.5, 0.25);
    gl_FragColor = vec4(1.0 - exp( -col ), 1.0);
}
