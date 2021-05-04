#include "file_proc.h"
// #include <exception>
#include <ios>
#include <stdexcept>
// #include <iomanip>
#define GREEN 1 // TDOD(Abreu): use Image_Segmenter`s LUT;
#define NONE 0
namespace file_proc
{
void get_color_clusters(const std::string file_name, std::vector<uint8_t>& LUT)
{
    if (LUT.size() < 256 * 256 * 256)
    {
        throw std::invalid_argument("LUT size smaller than 256*256*256");
    }
    for (int i = 0; i < 256 * 256 * 256; i++) { LUT[i] = NONE; }
    std::string line;
    std::ifstream inFile(file_name.c_str(), std::ios::in);
    int aux;
    int count=0;
    if (inFile)
    {
        while (getline(inFile, line))
        {
            std::istringstream actual_color(line);
            actual_color >> aux;
            LUT[aux] = GREEN;
            actual_color.str("");
            count++;
        }
        std::cout << "LUT 1s: " << count << std::endl;
        inFile.close();
    }
    else
    {
        throw std::invalid_argument("Region not within image boundaries");
        // Strange that I didnt need to include stdexcept for this to work on img_proc/img_proc.h
    }
}
} // namespace file_proc