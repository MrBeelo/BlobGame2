#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "../raylib/json.hpp"
#include <fstream>
#include <filesystem>
#include <string>

class SaveFile {
    public:
    nlohmann::json saveData;
    std::string savePath = "data/savefile.json";
    SaveFile();
    ~SaveFile();
    int GetCurrentLevel() const;
    void SetCurrentLevel(int level);
    void Write() const;
};

#endif