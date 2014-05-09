#ifndef IOUTILS_H
#define IOUTILS_H

#include "lib/json/json.h"
#include "Types.h"

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
 * Gets the path to the serialized file for the given class and name.
 */
template <class T>
std::string getPath(const std::string &name) {
   return "data/" + T::FOLDER_NAME + "/" + name + ".json";
}

/**
 * Loads an element of the given type from the provided JSON file.
 */
//template <class T>
//SPtr<T> load(const std::string &fileName) {
//   return T::fromJson(readJsonFile(fileName));
//}

/**
 * Saves an element of the given (Saveable) type to its JSON file.
 */
template <class T>
void save(const T &data, const std::string &jsonFileName) {
   writeJsonFile(data.serialize(), getPath<T>(jsonFileName));
}

} // namespace IOUtils

#endif
