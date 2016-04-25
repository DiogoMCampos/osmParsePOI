#include <string>

class POI {
private:
	std::string nodeID;
	std::string type;
	std::string name;
public:
	POI(std::string nodeID, std::string type, std::string name): nodeID(nodeID), type(type), name(name) {};
	std::string getNodeID() {return nodeID;}
	std::string getType() {return type;}
	std::string getName() {return name;}
};
