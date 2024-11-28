#include "load.h"

void save_game(std::string& filepath, Person& person)
{
	std::ofstream outFile(filepath);
	if (outFile.is_open()) {
		outFile << "Day: " << person.get_day() << "\n";
		outFile << "Money: " << person.get_money() << "\n";
		outFile << "LevelSleep: " << person.get_lvl_sleep() << "\n";
		outFile << "LevelHunger: " << person.get_hunger() << "\n";
		outFile << "Leg: " << person.get_leg_power() << "\n";
		outFile << "Back: " << person.get_back_power() << "\n";
		outFile << "Chest: " << person.get_chest_power() << "\n";
		outFile.close();

	}
	else {
		std::cerr << "Error: Unable to save game data to " << filepath << "\n";
	}
}

bool loadGameData(const std::string& filename, Person& person)
{
	std::ifstream inFile(filename);
	if (inFile.is_open()) {
		std::string line;
		int day = 1, money = 100, lvl_sleep = 0, lvl_hunger = 0, chest = 0, leg = 0, back = 0;

		while (std::getline(inFile, line)) {
			std::istringstream iss(line);
			std::string key;
			if (line.find("Day:") != std::string::npos) {
				iss >> key >> day;
			}
			else if (line.find("Money:") != std::string::npos) {
				iss >> key >> money;
			}
			else if (line.find("LevelSleep:") != std::string::npos) {
				iss >> key >> lvl_sleep;
			}
			else if (line.find("LevelHunger:") != std::string::npos) {
				iss >> key >> lvl_hunger;
			}
			else if (line.find("Leg:") != std::string::npos)
			{
				iss >> key >> leg;
			}
			else if (line.find("Back:") != std::string::npos)
			{
				iss >> key >> back;
			}
			else if (line.find("Chest:") != std::string::npos)
			{
				iss >> key >> chest;
			}
		}
		inFile.close();
		person.update_money(-money + 1000);
		person.update_hunger(lvl_hunger);
		person.update_sleep(lvl_sleep);
		person.set_day(day);
		person.set_back_power(back);
		person.set_chest_power(chest);
		person.set_leg_power(leg);
		return true;
	}
	else {
		std::cerr << "Error: Unable to load game data from " << filename << "\n";
		return false;
	}
}


std::vector<std::string> getFilesInDirectory(const std::string& directoryPath)
{
	std::vector<std::string> fileNames;
	try {
		for (const auto& entry : fs::directory_iterator(directoryPath)) {
			if (entry.is_regular_file()) {  // Проверяем, является ли объект файлом
				fileNames.push_back(entry.path().filename().string());
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error reading directory: " << e.what() << "\n";
	}
	return fileNames;
}

