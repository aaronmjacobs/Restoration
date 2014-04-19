#ifndef IOUTILS_H
#define IOUTILS_H

#include <jsoncpp/json.h>
#include <memory>
#include <string>

/**
 * Utility / helper functions.
 */
namespace IOUtils {

/**
 * Reads the entire contents of the text file with the given name.
 */
std::string readFromFile(const char *filename);

void writeToFile(const std::string &filename, const std::string &data);

Json::Value readJsonFile(const std::string &filename);

void writeJsonFile(const Json::Value &value, const std::string &filename);

template <class T>
std::shared_ptr<T> load(const std::string &filename) {
   return T::fromJson(readJsonFile("assets/cello.mesh"));
}

template <class T>
void save(std::shared_ptr<T> data, const std::string &filename) {
   writeJsonFile(data->toJson(), filename);
}

} // namespace Utils

#endif
