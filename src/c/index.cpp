#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Common.h"
#include "InputOutput.h"
#include "Server.h"
#include "ServerManager.h"
#include "GeneticAlgorithm.h"

const string INPUT_FILE_PATH_A = "..//inputData//a.in";
const string INPUT_FILE_PATH_B = "..//inputData//b.in";
const string INPUT_FILE_PATH_C = "..//inputData//c.in";
const string INPUT_FILE_PATH_D = "..//inputData//d.in";
const string INPUT_FILE_PATH_E = "..//inputData//e.in";
const string INPUT_FILE_PATH_F = "..//inputData//f.in";

string submitionResultToString(vector<submitionResultNode>& data, unsigned long int score) {
    stringstream concat;
    concat << score << endl;
    concat << data.size() << endl;
    for (submitionResultNode& node : data) {
        concat << node.fileName << " " << node.serverId << endl;
    }

    return concat.str();
}

unsigned long int startServersBySubmitionData (unsigned int serversQ, vector<submitionResultNode> submitionResults, map<string, compileDataNode> compiledData, map<string, vector<string>> compiledDataDeps) {
    ServerManager sManager(serversQ);
    for (submitionResultNode submitionResult : submitionResults) {
        sManager.bindFileToServer(compiledData[submitionResult.fileName], submitionResult.serverId, compiledData, compiledDataDeps);
    }
    return sManager.calcSummaryScore();
}

#include "emscripten.h"
extern "C" { 
 inline const char* cstr(const string& message) {
    char * cstr = new char [message.length()+1];
    strcpy (cstr, message.c_str());
    return cstr;
}
	EMSCRIPTEN_KEEPALIVE
	const char* run(int flag, int populationQ, int STAGNATION_PERIOD, int SELECTION_Q, int SELECTION_PERIOD) {
        string filePath;
		switch (flag) {
            case 0: {
                filePath = INPUT_FILE_PATH_A;
                break;
            }
            case 1: {
                filePath = INPUT_FILE_PATH_B;
                break;
            }
            case 2: {
                filePath = INPUT_FILE_PATH_C;
                break;
            }
            case 3: {
                filePath = INPUT_FILE_PATH_D;
                break;
            }
            case 4: {
                filePath = INPUT_FILE_PATH_E;
                break;
            }
            case 5: {
                filePath = INPUT_FILE_PATH_F;
                break;
            }
            default: {
                return "";
            }
        }
        totalFileInfo info;
        map<string, compileDataNode> compiledData;
        map<string, vector<string>> compiledDataDeps;
        vector<string> targetFiles;
        parseInputData(readFromFile(filePath), info, compiledData, compiledDataDeps, targetFiles);

        auto timeStart = chrono::steady_clock::now();
        GeneticAlgorithm ga = GeneticAlgorithm(compiledData, compiledDataDeps, targetFiles, info.serversQ);
        vector<submitionResultNode> res = ga.start(populationQ, STAGNATION_PERIOD, SELECTION_Q, SELECTION_PERIOD);
        auto timeEnd = chrono::steady_clock::now();

        std::cout << "\n_________________________\n";
        std::cout << "time: " << chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() << "ms" << std::endl;
        unsigned long int score = startServersBySubmitionData(info.serversQ, res, compiledData, compiledDataDeps); // like a test
        return cstr(submitionResultToString(res, score));
	};
  }


int main() {
    srand(time(NULL));
    return 0;
}