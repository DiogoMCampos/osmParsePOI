#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "POI.hpp"

class Parser {
private:
	std::ifstream osmFile;
	std::ofstream destFile;
	std::vector<POI> poiList;
public:
	bool openFiles();
	void closeFiles();
	bool openOSMFile();
	bool openPOIFile();
	bool isValidOSMFile();
	void store();
	bool readNodes();
	void getPOI(std::string nodeID);
	void getName(std::string nodeID, std::string type, std::string key);
	void getNextTag(std::string &line);
};
