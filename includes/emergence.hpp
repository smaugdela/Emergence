#ifndef EMERGENCE_HPP
#define EMERGENCE_HPP

#include "macros.hpp"

#include "class/Settings.hpp"
#include "class/Particle.hpp"

#include "json.hpp"
using json = nlohmann::json;

#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include <random>

extern Settings my_settings;

int loop(sf::RenderWindow &window);
void init_simulation(std::vector<particle_type> &types, std::vector<std::vector<int>> &interactions);
void fps_counter(sf::RenderWindow &window, std::string fps);
float force(float r, float relation_coefficient);

#endif
