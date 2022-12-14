uniform float time;
uniform vec2 resolution;

const int complexity = 20;  // More points of color.
const float fluid_speed = 1.0; // Drives speed, higher number will make it slower.
const float color_intensity = 0.5;

void main() {
    vec2 p = (2.0 * gl_FragCoord.xy - resolution) / max(resolution.x, resolution.y);

    for (int i = 1; i < complexity; i++) {
        float f = float(i);
        vec2 newp = p + time * 0.001;
        newp.x += 0.6 / f * sin(f * p.y + time / fluid_speed + 20.3 * f) + 0.5;
        newp.y += 0.6 / f * sin(f * p.x + time / fluid_speed + 0.3 * (f + 10.)) - 0.5;
        p = newp;
    }
    vec3 col = vec3(
        color_intensity * sin(5.0 * p.x) + color_intensity,
        color_intensity * sin(3.0 * p.y) + color_intensity,
        color_intensity * sin(p.x + p.y) + color_intensity);
    gl_FragColor = vec4(col, 1);
}
