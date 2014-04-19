#ifndef IOUTILS_H
#define IOUTILS_H

#include "lib/json/json.h"
#include <memory>
#include <string>

/**
 * Utility / helper functions.
 */
namespace IOUtils {

/**
 * Reads the entire contents of the text file with the given name.
 */
std::string readFromFile(const std::string& fileName);

/**
 * Writes the contents of the given text to the file with the given name.
 */
void writeToFile(const std::string &fileName, const std::string &data);

/**
 * Reads the file with the given name, and parses its contents into JSON.
 */
Json::Value readJsonFile(const std::string &fileName);

/**
 * Writes the given JSON value to the file with the given name.
 */
void writeJsonFile(const Json::Value &value, const std::string &fileName);

/**
 * Loads an element of the given type from the provided JSON file.
 */
template <class T>
std::shared_ptr<T> load(const std::string &fileName) {
   return T::fromJson(readJsonFile(fileName));
}

/**
 * Saves an element of the given type to the provided JSON file.
 */
template <class T>
void save(std::shared_ptr<T> data, const std::string &fileName) {
   writeJsonFile(data->toJson(), fileName);
}

} // namespace IOUtils

#endif
