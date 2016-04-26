#include "Parser.hpp"

using namespace std;

bool Parser::openFiles() {
	if (!openOSMFile() || !openPOIFile() || !isValidOSMFile())
		return false;

	return true;
}

void Parser::closeFiles() {
	osmFile.close();
	destFile.close();
}

bool Parser::openOSMFile() {
	string filename;

	do {
		if (osmFile.fail()) {
			osmFile.clear();
			cout << "Invalid filename. Please enter again: ";
		}
		else {
			cout << "Enter the OSM file name (including extension) or  \"exit\" to cancel: ";
		}
		cin >> filename;
		if (cin.eof() || filename == "exit") {
			return false;
		}
		osmFile.open(filename.c_str());
	} while (osmFile.fail());

	return true;
}

bool Parser::openPOIFile() {
	destFile.open("poi.txt");

	if (destFile.fail())
		return false;

	return true;
}

bool Parser::isValidOSMFile() {
	string line;

	getline(osmFile, line);
	if (line.substr(0, 2) != "<?" || line.substr(line.length() - 2, 2) != "?>")
		return false;

	getline(osmFile, line);
	if (line.substr(0, 4) != "<osm" || line[line.length() - 1] != '>')
		return false;

	getline(osmFile, line);
	if (line.substr(1, 7) != "<bounds" || line[line.length() - 1] != '>')
		return false;

	return true;
}

void Parser::store() {
	destFile << poiList[0].getNodeID() << ";" << poiList[0].getType() << ";" << poiList[0].getName() << ";" << poiList[0].getLat() << ";" << poiList[0].getLon();
	for (size_t i = 1; i < poiList.size(); ++i) {
		destFile << "\n" << poiList[i].getNodeID() << ";" << poiList[i].getType() << ";" << poiList[i].getName() << ";" << poiList[i].getLat() << ";" << poiList[i].getLon();
	}
}

bool Parser::readNodes() {
	string nodeLine;

	while (getline(osmFile, nodeLine)) {
		string nodeInfo;
		for (size_t i = 0; i < nodeLine.length(); ++i) {
			if (nodeLine[i] != ' ' || nodeInfo.length() != 0) {
				nodeInfo += nodeLine[i];
			}
		}

		if (nodeInfo.substr(0, 5) != "<node") {
			break;
		}

		if (nodeInfo.substr(0, 5) == "<node" && nodeInfo[nodeInfo.length() - 2] == '/') {
			continue;
		}

		int firstDelim = nodeInfo.find('"');
		int idLength = nodeInfo.find('"', firstDelim + 1) - firstDelim - 1;
		string idString = nodeInfo.substr(firstDelim + 1, idLength);

		int beginLat = nodeInfo.find("lat=") + 4;
		int endLat = nodeInfo.find('"', beginLat + 4) - beginLat - 1;
		string latitude = nodeInfo.substr(beginLat + 1, endLat);

		int beginLon = nodeInfo.find("lon=") + 4;
		int endLon = nodeInfo.find('"', beginLon + 4) - beginLon - 1;
		string longitude = nodeInfo.substr(beginLon + 1, endLon);

		getPOI(idString, latitude, longitude);
	}

	return true;

}

void Parser::getPOI(string nodeID, string lat, string lon) {
	string line;
	getNextTag(line);
	while (line[0] != '/') {
		getline(osmFile, line, ' '); // k="..."
		// check if it's an amenity
		if (line == "k=\"amenity\"") {
			string type;
			getline(osmFile, line, '\"'); // garbage
			getline(osmFile, type, '\"');
			getline(osmFile, line); // garbage
			if (type == "atm")
				getName(nodeID, type, "k=\"operator\"", lat, lon);
			else if (type == "restaurant")
				getName(nodeID, type, "k=\"name\"", lat, lon);
			else if (type == "pharmacy")
				getName(nodeID, type, "k=\"name\"", lat, lon);
			else if (type == "hospital")
				getName(nodeID, type, "k=\"name\"", lat, lon);
			else if (type == "fuel")
				getName(nodeID, type, "k=\"brand\"", lat, lon);
			else {
				getNextTag(line);
			}
		}
		else {
			getline(osmFile, line);
			getNextTag(line);
		}
	}
}

void Parser::getName(string nodeID, string type, string key, string lat, string lon) {
	string line;
	string name = "";

	getNextTag(line);
	while (line[0] != '/') {
		getline(osmFile, line, ' '); // k="..."
		// check if it's the corresponding key
		if (line == key) {
			getline(osmFile, line, '\"'); // garbage
			getline(osmFile, name, '\"');
		}
		getNextTag(line);
	}
	POI temp(nodeID, type, name, lat, lon);
	poiList.push_back(temp);
}

void Parser::getNextTag(string &line) {
	getline(osmFile, line, '<'); // discards whitespaces
	getline(osmFile, line, ' '); // gets tag
}

