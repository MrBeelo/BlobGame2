#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "../raylib/json.hpp"
#include <fstream>
#include <filesystem>
#include <string>

class SaveFile {
    public:
    static inline nlohmann::json saveData;
    static inline std::string savePath = "data/savefile.json";
    static void Load();
    static int GetCurrentLevel();
    static void SetCurrentLevel(int level);
    static void Write();
};

#endif