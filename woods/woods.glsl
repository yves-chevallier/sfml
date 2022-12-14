uniform float time;
uniform vec2 resolution;

void main(void) {
    vec2 uv = (gl_FragCoord.xy * 2. - resolution.xy) / min(resolution.x, resolution.y);
    vec2 huv = uv;
    float lines = 1024.0;
    vec3 finalColor = vec3(0);

    float y = uv.y;

    float x = uv.x + floor(time * lines / 5.) / lines;
    float w1 = smoothstep(0.81, 0.85, cos(x * 10.) * 1.2 + cos(x * 3.) * 1.0 + cos(y * 2. + .1));
    w1 += smoothstep(0.81, 0.85, cos(x * 10. + 3.) * 1.2 + cos(x * 3. + 3.) * 1.0 + cos(y * 2. - 1.) - 1.);
    float g1 =
        smoothstep(0.8, 0.9, cos(cos(y * 19.) * 5. + x * 160.) + cos(x * 60.) + cos(x * 133.) * 0.8 + y * 11. + 6.);
    float l1 = smoothstep(0.8, 0.9,
                          cos(cos(x * 30.) * 2.0 + y * 110.) * 2. + cos(cos(y * 110.) * 1.0 + x * 120.) * 2. -
                              abs(cos(x * 2.1) * 8.) - abs(cos(x * 4.4) * 4.) - y * 50. + 31.);
    x = uv.x + floor(time * lines / 8.) / lines;
    float w2 = smoothstep(0.81, 0.85, cos(x * 21.) * 1.1 + cos(x * 16.) * 0.7 + cos(y * 5. + .1) * 1.1);
    w2 += smoothstep(0.81, 0.85, cos(x * 21. + 3.) * 0.7 + cos(x * 16. + 3.) * 1.0 + cos(y * 4. - 1.) * 1.0 - 1.);
    float g2 =
        smoothstep(0.8, 0.9, cos(cos(y * 38.) * 5. + x * 320.) + cos(x * 120.) + cos(x * 266.) * 0.2 + y * 21. + 6.);
    float l2 = smoothstep(0.8, 0.9,
                          cos(cos(x * 60.) * 2.0 + y * 220.) * 2. + cos(cos(y * 220.) * 1.0 + x * 240.) * 2. -
                              abs(cos(x * 4.2) * 6.) - abs(cos(x * 8.8) * 4.) - y * 100. + 28.);
    x = uv.x + floor(time * lines / 11.) / lines;
    float w3 = smoothstep(0.81, 0.85, cos(x * 42.) * 1.1 + cos(x * 32.) * 0.7 + cos(y * 6. + .1) * 1.1);
    w3 += smoothstep(0.81, 0.85, cos(x * 42. + 3.) * 0.7 + cos(x * 32. + 3.) * 1.0 + cos(y * 5. - 1.) * 1.0 - 1.);
    float g3 =
        smoothstep(0.8, 0.9, cos(cos(y * 76.) * 5. + x * 640.) + cos(x * 240.) + cos(x * 532.) * 0.1 + y * 31. + 6.);
    float l3 = smoothstep(0.8, 0.9,
                          cos(cos(x * 120.) * 2.0 + y * 440.) * 2. + cos(cos(y * 440.) * 1.0 + x * 480.) * 2. -
                              abs(cos(x * 8.4) * 6.) - abs(cos(x * 17.6) * 4.) - y * 200. + 25.);

    vec2 pos = vec2(cos(time * 0.41), sin(time * 0.51) * .3);
    pos = floor(pos * lines) / lines;
    float s1 = smoothstep(0.04, 0.0, length(pos - uv));
    pos = vec2(cos(1. + time * 0.31), sin(time * 0.52) * .3);
    pos = floor(pos * lines) / lines;
    float s2 = smoothstep(0.04, 0.0, length(pos - uv));

    float c;
    c = w3 * g3 * l3;
    finalColor = clamp(vec3(0.7, 0.8, 1.0) + c, 0.0, 1.0);
    c = w2 * g2 * l2;
    finalColor = min(clamp(vec3(0.4, 0.5, 0.7) + c, 0.0, 1.0), finalColor);
    c = s1;
    finalColor += c * vec3(0.4, 0.9, 0.1);
    c = s2;
    finalColor += c * vec3(1.0, 0.3, 0.7);
    c = s1;
    finalColor += c * c * vec3(1) * abs(sin(time * 50.));
    c = s2;
    finalColor += c * c * vec3(1) * abs(cos(time * 50.));
    c = w1 * g1 * l1;
    finalColor *= vec3(0.7, 0.8, 1.0) * c;

    gl_FragColor = vec4(finalColor, 1);
}
