#ifndef EMERGENCE_HPP
#define EMERGENCE_HPP

#include "macros.hpp"

#include "class/Settings.hpp"
#include "class/Particle.hpp"

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

extern Settings my_settings;

int loop(sf::RenderWindow &window);
void init_simulation(std::vector<particle_type> &types, std::vector<std::vector<int>> &interactions);

#endif
