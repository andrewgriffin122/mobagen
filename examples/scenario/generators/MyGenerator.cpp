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
            //https://www.redblobgames.com/maps/terrain-from-noise/
            //Euclidean^2

            //-1 <-> 1
            float nx = ((2.0 * (float)c + 1) / (float)sideSize) - 1.0;
            float ny = ((2.0 * (float)l + 1) / (float)sideSize) - 1.0;
            float d = std::min(1.0, ((nx * nx) + (ny * ny)) / sqrt(2.0));

            float rgb = abs(noise.octave3D(c / 50.0 , l / 50.0, displacement, 5) * d);

            //new elevation using distance
            rgb = (rgb + (1.0 - d)) * 255 / 2.0;

            float r, g, b;

            //sand
            if (rgb < 100 && rgb > 90)
            {
                r = 194;
                g = 178;
                b = 128;
            }//blue
            else if (rgb < 90)
            {
                r = 0;

                g = rgb + 30;
                if (g < 70)
                    g = rgb + 70;

                if (g > 100)
                    g = (rgb / 20) + 100;

                b = rgb + 90;
                if (b < 148)
                    b = rgb + 148;
                    
                if (b > 200)
                    b = (rgb / 20) + 200;
            }//green
            else
            {
                r = 34;
                //g = 139;
                g = rgb + 80;
                if (g < 100)
                    g = rgb + 100;

                if (g > 200)
                    g = (rgb / 20) + 200;

                b = 34;
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
