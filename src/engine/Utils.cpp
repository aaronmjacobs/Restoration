#include "FancyAssert.h"
#include "Utils.h"

#include <fstream>

namespace Utils {

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

} // namespace Utils
