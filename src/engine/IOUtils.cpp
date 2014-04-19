#include "FancyAssert.h"
#include "IOUtils.h"

#include <jsoncpp/json.h>
#include <fstream>

namespace IOUtils {

Json::Reader jsonReader;
Json::StyledWriter jsonWriter;

std::string readFromFile(const char *filename) {
   std::FILE *fp = std::fopen(filename, "rb");
   ASSERT(fp, "Unable to open file: %s", filename);

   std::string contents;
   std::fseek(fp, 0, SEEK_END);
   contents.resize(std::ftell(fp));
   std::rewind(fp);
   std::fread(&contents[0], 1, contents.size(), fp);
   std::fclose(fp);

   return contents;
}

void writeToFile(const std::string &filename, const std::string &data) {
   std::ofstream out(filename);
   ASSERT(out, "Unable to open file for writing: %s", filename.c_str());

   out << data;
   out.close();
}

Json::Value readJsonFile(const std::string &filename) {
   Json::Value root;
   std::ifstream jsonFile(filename);

   ASSERT(jsonReader.parse(jsonFile, root), "Unable to parse JSON file: %s", filename.c_str());
   jsonFile.close();

   return root;
}

void writeJsonFile(const Json::Value &value, const std::string &filename) {
   std::string data = jsonWriter.write(value);
   writeToFile(filename, data);
}

} // namespace Utils
