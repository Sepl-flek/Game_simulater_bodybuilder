#pragma once
#include <SFML/Graphics.hpp>
#include "Person.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;


void save_game(std::string& filepath, Person& person);
bool loadGameData(const std::string& filename, Person& person);
std::vector<std::string> getFilesInDirectory(const std::string& directoryPath);