#include "file_proc.h"
// #include <exception>
#include <ios>
#include <stdexcept>
// #include <iomanip>
#define GREEN 1
#define NONE -1
namespace file_proc
{
void getColorClusters(std::string fileName, std::vector<unsigned char>& LUT)
{
    if (LUT.size() < 256 * 256 * 256)
    {
        throw std::invalid_argument("LUT size smaller than 256*256*256");
    }
    for (int i = 0; i < 256 * 256 * 256; i++) { LUT[i] = -1; }
    std::string line;
    std::ifstream inFile(fileName.c_str(), std::ios::in);
    short c;
    if (inFile)
    {
        while (getline(inFile, line))
        {
            std::istringstream actualColor(line);
            actualColor >> c;
            LUT[c] = GREEN;
            actualColor.str("");
        }
        inFile.close();
    }
    else
    {
        throw std::invalid_argument("Region not within image boundaries");
        // Strange that I didnt need to include stdexcept for this to work on img_proc/img_proc.h
    }
}
} // namespace file_proc