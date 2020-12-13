#pragma once

#include "Common.h"

#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct scoreNode {
	string name;
	unsigned long int score;
};

class Server {
private:
	unsigned int serverTime = 0;
	vector<scoreNode> compiledFiles;
	map<string, unsigned int> replicationDeadLine;
	void calculateServerTime(compileDataNode& file, unsigned int replicationTotalTime);
public:
	unsigned int getServerTime();
	bool isServerContainFile(string fileName);
	unsigned int getReplicationTimeForFile(string fileName, unsigned int);
	void bindFile(compileDataNode& file, unsigned int replicationTotalTime);
	unsigned long int calcSummuryScore();
};
