#include <string>

using namespace std;

class POI {
private:
	string nodeID;
	string type;
	string name;
	string lat;
	string lon;
public:
	POI(string nodeID, string type, string name, string lat, string lon): nodeID(nodeID), type(type), name(name), lat(lat), lon(lon) {};
	string getNodeID() {return nodeID;}
	string getType() {return type;}
	string getName() {return name;}
	string getLat() {return lat;}
	string getLon() {return lon;}
};
