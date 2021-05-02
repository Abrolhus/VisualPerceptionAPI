#ifndef FILE_PROC_H
#define FILE_PROC_H
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

/** File processing functions.
 *
 */
namespace file_proc
{
/** Creates a Look-up Table that has as keys the color value of each RGB color and as value a int (short) corresponding to its assigned cluster.
 * All colors (int) in the file are assigned to the GREEN cluster. All other colors are assigned to the NONE cluster.
 * @param fileName
 * @param LUT
 */
void getColorClusters(std::string fileName, std::vector<uint8_t>& LUT);

}
#endif
