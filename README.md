em++ googleHashCode.cpp inputOutput.cpp GeneticAlgorithm.cpp Server.cpp ServerManager.cpp --preload-file inputData/a.in --preload-file outputData/output.out -s DISABLE_EXCEPTION_CATCHING=0 -s EXPORT_ALL=1 -s WASM=1

em++ googleHashCode.cpp inputOutput.cpp GeneticAlgorithm.cpp Server.cpp ServerManager.cpp --preload-file inputData/a.in -s DISABLE_EXCEPTION_CATCHING=0

emcc googleHashCode.cpp inputOutput.cpp GeneticAlgorithm.cpp Server.cpp ServerManager.cpp -o hello.html --preload-file inputData/a.in -s DISABLE_EXCEPTION_CATCHING=0