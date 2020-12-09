#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Common.h"
#include "InputOutput.h"
#include "Server.h"
#include "ServerManager.h"
#include "GeneticAlgorithm.h"

const string SELECTED_INPUT_FILE_PATH = ".//inputData//a.in";
const string SELECTED_OUTPUT_FILE_PATH = ".//outputData/output.out";
const string SUBMITION_FILE_PATH = ".//outputData//submitionExample.out";


// void startServersBySubmitionData (unsigned int serversQ, vector<submitionResultNode> submitionResults, map<string, compileDataNode> compiledData, map<string, vector<string>> compiledDataDeps) {
//     ServerManager sManager(serversQ);
//     for (submitionResultNode submitionResult : submitionResults) {
//         sManager.bindFileToServer(compiledData[submitionResult.name], submitionResult.serverId, compiledData, compiledDataDeps);
//     }
//     cout << "Score: " << sManager.calcSummaryScore() << endl;
//     int serverId = 0;
//     for (auto t : sManager.getServersTime()) {
//         cout << "Server Time " << serverId++ << ": " << t << endl;
//     }
//     sManager;
// }

#include "emscripten.h"
extern "C" { 
 inline const char* cstr(const string& message) {
    char * cstr = new char [message.length()+1];
    strcpy (cstr, message.c_str());
    return cstr;
}
	EMSCRIPTEN_KEEPALIVE
	const char* run(int flag) {
		return flag == 200 ? cstr("200") : cstr("-");
	};
  }

int main() {
    return 0;
    // srand(time(NULL)); // allows to generate new random values

    // totalFileInfo info;
    // map<string, compileDataNode> compiledData;
    // map<string, vector<string>> compiledDataDeps;
    // vector<string> targetFiles;
    // parseInputData(readFromFile(SELECTED_INPUT_FILE_PATH), info, compiledData, compiledDataDeps, targetFiles);

    // // vector<submitionResultNode> submitionResults;
    // // parseOutputData(readFromFile(SUBMITION_FILE_PATH), submitionResults);
    // // startServersBySubmitionData(info.serversQ, submitionResults, compiledData, compiledDataDeps);

    // auto timeStart = chrono::steady_clock::now();
    // GeneticAlgorithm ga = GeneticAlgorithm(compiledData, compiledDataDeps, targetFiles, info.serversQ);
    // ga.start(10, 30, 5, 5);
    // auto timeEnd = chrono::steady_clock::now();

    // std::cout << "\n_________________________\n";
    // std::cout << "time: " << chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() << "ms" << std::endl;
    // vector<string> d = { "7", "c0 1" };
    // writeToFile(SELECTED_OUTPUT_FILE_PATH, d);
}

// TODO: weight fixes! big N
