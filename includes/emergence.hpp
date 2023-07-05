#ifndef EMERGENCE_HPP
#define EMERGENCE_HPP

#include "macros.hpp"

#include "class/Settings.hpp"
#include "class/Particle.hpp"

#include "json.hpp"
using json = nlohmann::json;
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

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

int loop(sf::RenderWindow &window, json file);
void init_simulation(json file, std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles);
void update_simulation(std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles);
void compute_particles(std::vector<std::vector<Particle *>> &particles, std::vector<std::vector<float>> &interactions);
void update_particles(std::vector<std::vector<Particle *>> &particles);
void draw_particles(sf::RenderWindow &window, std::vector<std::vector<Particle *>> &particles);
void fps_counter(sf::RenderWindow &window, std::string fps);
void gui(std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles, sf::RenderWindow &window);
float force(float r, float relation_coefficient);

#endif
