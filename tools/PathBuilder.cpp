#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#define PATH_WIDTH 5.9f

void replaceAll(std::string &s, const std::string &search, const std::string &replace) {
    for (size_t pos = 0; ; pos += replace.length()) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == std::string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

void replaceValues(std::string &string, float currentX, float y) {
   std::ostringstream ss;
   ss.precision(1);

   ss << std::fixed << currentX;
   replaceAll(string, "LEFT_X", ss.str());
   ss.str("");

   ss << std::fixed << currentX + PATH_WIDTH;
   replaceAll(string, "MIDDLE_X", ss.str());
   ss.str("");

   ss << std::fixed << currentX + PATH_WIDTH + PATH_WIDTH;
   replaceAll(string, "RIGHT_X", ss.str());
   ss.str("");

   ss << std::fixed << y - 0.5f;
   replaceAll(string, "PATH_Y", ss.str());
   ss.str("");

   ss << std::fixed << y;
   replaceAll(string, "FRONT_BACK_Y", ss.str());
   ss.str("");
}

int main(int argc, char *argv[]) {
   std::ifstream iFile("pathBase.json");
   std::ofstream oFile("generatedPath.json");

   if (!iFile || !oFile) {
      std::cerr << "Unable to open file\n";
      return 1;
   }

   float xPos, max, y;
   std::cout << "Enter initial x position: ";
   std::cin >> xPos;
   std::cout << "Enter level max: ";
   std::cin >> max;
   std::cout << "Enter base Y: ";
   std::cin >> y;

   std::vector<std::string> lines;
   std::string line;
   while (getline(iFile, line)) {
      lines.push_back(line);
   }

   iFile.close();

   while (xPos < max) {
      for (std::string l : lines) {
         std::string lCopy = l;
         replaceValues(lCopy, xPos, y);
         oFile << lCopy << "\n";
      }

      xPos += PATH_WIDTH * 3;
   }
   

   oFile.close();

   return 0;
}