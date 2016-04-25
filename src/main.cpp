#include "Parser.hpp"

int main() {
	Parser parser;

	if (!parser.openFiles())
		return -1;

	parser.readNodes();
	parser.store();

	parser.closeFiles();

	return 0;
}
