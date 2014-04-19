#include "FancyAssert.h"
#include "IOUtils.h"

#include <jsoncpp/json.h>
#include <fstream>

namespace IOUtils {

Json::Reader jsonReader;
Json::StyledWriter jsonWriter;

std::string readFromFile(const std::string& fileName) {
   std::ifstream in(fileName);
   ASSERT(in, "Unable to open file for reading: %s", fileName.c_str());

   std::string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
   in.close();

   return data;
}

void writeToFile(const std::string &fileName, const std::string &data) {
   std::ofstream out(fileName);
   ASSERT(out, "Unable to open file for writing: %s", fileName.c_str());

   out << data;
   out.close();
}

Json::Value readJsonFile(const std::string &fileName) {
   Json::Value root;
   std::ifstream jsonFile(fileName);

   ASSERT(jsonReader.parse(jsonFile, root), "Unable to parse JSON file: %s", fileName.c_str());
   jsonFile.close();

   return root;
}

void writeJsonFile(const Json::Value &value, const std::string &fileName) {
   std::string data = jsonWriter.write(value);
   writeToFile(fileName, data);
}

} // namespace IOUtils
