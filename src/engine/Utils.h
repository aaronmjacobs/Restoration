#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * Utility / helper functions.
 */
namespace Utils {

/**
 * Reads the entire contents of the text file with the given name.
 */
std::string readFromFile(const char *filename);

} // namespace Utils

#endif
