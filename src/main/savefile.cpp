#include "../headers/main/savefile.h"

SaveFile::SaveFile() {
    std::filesystem::create_directories("data");
    std::ifstream inFile(savePath);
    if (inFile.is_open()) {
        inFile >> saveData;
        inFile.close();
    } else {
        saveData["current_level"] = 3;
    }
}

SaveFile::~SaveFile() {}

int SaveFile::GetCurrentLevel() const {
    if (saveData.contains("current_level") && saveData["current_level"].is_number()) {
        return saveData["current_level"];
    }
    return 0;
}

void SaveFile::SetCurrentLevel(int level) {
    saveData["current_level"] = level;
    Write();
}

void SaveFile::Write() const {
    std::ofstream outFile(savePath);
    if (outFile.is_open()) {
        outFile << saveData.dump(4); // Pretty print
        outFile.close();
    }
}