#include "raylib.h"

#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;


int main(int argc, char** argv) {
    fs::path textures = fs::path(argv[1]);
    fs::path output = fs::path(argv[2]);

    std::error_code ec;
    fs::create_directories(output, ec);
    if (ec) std::cerr << "Warning: could not create output directory: " << ec.message() << "\n";

    for (const auto& entry : fs::directory_iterator(textures)) {
        if (entry.is_directory()) continue;
        Image image = LoadImage(fs::absolute(entry.path()).string().c_str());
        ExportImageAsCode(
            image,
            (output / (entry.path().stem().string() + ".h")).string().c_str()
        );
        UnloadImage(image);
    }

    return 0;
}
