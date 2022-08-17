#include "core/utils/file_reader.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace Minecraft
{
    namespace FileReader
    {
        std::string read_file(const std::string& filepath)
        {
            std::stringstream ss;
            std::ifstream file(filepath.c_str());

            for (std::string line; getline(file, line);)
            {
                ss << line << std::endl;
            }

            return ss.str();
        }
    }
}