#include "../headers/main/savefile.h"

void SaveFile::Load() {
    std::filesystem::create_directories("data");
    std::ifstream inFile(savePath);
    if (inFile.is_open()) {
        inFile >> saveData;
        inFile.close();
    } else {
        saveData["current_level"] = 0;
        Write();
    }
}

int SaveFile::GetCurrentLevel() {
    if (saveData.contains("current_level") && saveData["current_level"].is_number()) {
        return saveData["current_level"];
    }
    return 0;
}

void SaveFile::SetCurrentLevel(int level) {
    saveData["current_level"] = level;
    Write();
}

void SaveFile::Write() {
    std::ofstream outFile(savePath);
    if (outFile.is_open()) {
        outFile << saveData.dump(4); // Pretty print
        outFile.close();
    }
}