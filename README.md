# C++ compilation:
`em++ index.cpp inputOutput.cpp GeneticAlgorithm.cpp Server.cpp ServerManager.cpp --preload-file inputData/a.in --preload-file inputData/b.in --preload-file inputData/c.in --preload-file inputData/d.in --preload-file inputData/e.in --preload-file inputData/f.in -s DISABLE_EXCEPTION_CATCHING=0 -s EXPORT_ALL=1 -s WASM=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']" -s TOTAL_MEMORY=1gb -O2`

# run server
`npm run start`
