#include <iostream>
#include <fstream>
#include <sstream>

std::string loadFile(const std::string& path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
