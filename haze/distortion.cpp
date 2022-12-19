/*
// You will need libnoise to generate the distortion image
*/
#include <SFML/Graphics.hpp>


#include <libnoise/noise.h>
#include "noiseutils.h"

void createDistortionMap()
{
    // Increasing the size of the image will enable finer detail
    // This isn't always necessary for coarser distortions
    // since OpenGL interpolates nicely for us anyway
    // in the case where the object is larger than our image
    int width = 256;
    int height = 256;

    module::Perlin perlin;

    // Adjust these values according to your liking
    perlin.SetOctaveCount(4);
    perlin.SetFrequency(4.f / 1.f);
    perlin.SetPersistence(1.f / 8.f);

    // Obviously we only need the R and G channels,
    // but you can use the B and A channels for other effects
    utils::NoiseMap noise_map_r;
    utils::NoiseMap noise_map_g;
    utils::NoiseMap noise_map_b;
    utils::NoiseMap noise_map_a;

    utils::NoiseMapBuilderPlane plane_builder;
    plane_builder.SetSourceModule(perlin);
    plane_builder.SetBounds(0.0, 3.0, 0.0, 3.0);
    plane_builder.SetDestSize(width, height);

    // Enabling seamless is important for being able to scroll the texture
    plane_builder.EnableSeamless(true);

    perlin.SetSeed(2);
    plane_builder.SetDestNoiseMap(noise_map_r);
    plane_builder.Build();

    perlin.SetSeed( 3 );
    plane_builder.SetDestNoiseMap(noise_map_g);
    plane_builder.Build();

    perlin.SetSeed(5);
    plane_builder.SetDestNoiseMap(noise_map_b);
    plane_builder.Build();

    perlin.SetSeed(7);
    plane_builder.SetDestNoiseMap(noise_map_a);
    plane_builder.Build();

    sf::Image image;
    image.create(width, height);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float normalized_r = (noise_map_r.GetValue(x, y) + 1.f) / 2.f;
            float normalized_g = (noise_map_g.GetValue(x, y) + 1.f) / 2.f;
            float normalized_b = (noise_map_b.GetValue(x, y) + 1.f) / 2.f;
            float normalized_a = (noise_map_a.GetValue(x, y) + 1.f) / 2.f;

            sf::Uint8 value_r = static_cast<sf::Uint8>(std::min(std::max(std::floor(normalized_r * 255.f), 0.f), 255.f));
            sf::Uint8 value_g = static_cast<sf::Uint8>(std::min(std::max(std::floor(normalized_g * 255.f), 0.f), 255.f));
            sf::Uint8 value_b = static_cast<sf::Uint8>(std::min(std::max(std::floor(normalized_b * 255.f), 0.f), 255.f));
            sf::Uint8 value_a = static_cast<sf::Uint8>(std::min(std::max(std::floor(normalized_a * 255.f), 0.f), 255.f));

            image.setPixel(x, y, sf::Color(value_r, value_g, value_b, value_a));
        }
    }

    image.saveToFile("distortion_map.png");
}
