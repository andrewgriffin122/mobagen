#include "MyGenerator.h"
#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include <iostream>
// do not use this one to your assignment. this is my sample generator
std::vector<Color32> MyGenerator::Generate(int sideSize, float displacement)
{
    std::vector<Color32> colors;
    //   create your own function for noise generation
    siv::BasicPerlinNoise<float> noise;
    noise.reseed(1337);
    //  Noise noise(1337, 1024,0,255);
    for (int l = 0; l < sideSize; l++)
    {
        for (int c = 0; c < sideSize; c++)
        {
            float nx = (2.0 * (float)c) / (float)sideSize - 1;
            float ny = (2.0 * (float)l) / (float)sideSize - 1;
            float d = 1.0 - (1.0 - (nx * nx) * (1.0 - (ny * ny)));
            //float d = std::min(1, ((nx * nx) + (ny * ny) / sqrt(2)));
            //d *= 255;

            float rgb = abs(noise.octave3D(c / 50.0, l / 50.0, displacement, 2) * 255);

            rgb = (rgb + (1.0 - d)) / 2.0;

            float r, g, b;

            if (rgb < 40)
            {
                r = 0;
                g = 0;
                b = abs(rgb - 200);
            }
            else
            {
                r = 0;
                g = abs(rgb - 200);
                b = 0;
            }

            colors.emplace_back(r, g, b);
            //      double color = noise.noise(c/50.0,l/50.0);
            //      colors.emplace_back(color,color,color);
        }
    }
    //std::cout << colors.size() << std::endl;
    return colors;
}
std::string MyGenerator::GetName() { return "My Generator"; }
