#include <iostream>
#include <dirent.h>
#include <cstring>
#include <string>
#include <cstdio>

int main() {
    std::string folderPath;
    std::cout << "أدخل مسار المجلد: ";
    std::getline(std::cin, folderPath);

    DIR* dir = opendir(folderPath.c_str());
    if (!dir) {
        std::cerr << "❌ تعذر فتح المجلد.\n";
        return 1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string fileName = entry->d_name;

        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt") {
            std::string oldPath = folderPath + "/" + fileName;
            std::string newFileName = fileName.substr(0, fileName.size() - 4) + ".h";
            std::string newPath = folderPath + "/" + newFileName;

            if (rename(oldPath.c_str(), newPath.c_str()) == 0) {
                std::cout << "✔ تم تحويل: " << fileName << " → " << newFileName << '\n';
            }
            else {
                std::cerr << "❌ فشل في تحويل: " << fileName << '\n';
            }
        }
    }

    closedir(dir);
    std::cout << "✅ تم الانتهاء.\n";
    return 0;
}
