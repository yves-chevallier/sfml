uniform vec2 resolution;

#define PI 3.14159265359
#define TWO_PI 6.28318530718

void main(void) {
    vec2 st = gl_FragCoord.xy / resolution.xy;
    st.x *= resolution.x / resolution.y;

    vec3 color = vec3(.0);
    float d = .0;

    st = st * 2.0 - 1.0;
    int N = 3;
    float a = atan(st.x, st.y) + PI;
    float r = TWO_PI / float(N);

    d = cos(floor(.5 + a / r) * r - a) * length(st);
    color = vec3(1.0 - smoothstep(.4, .41, d));
    gl_FragColor = vec4(color, 1.0);
}
