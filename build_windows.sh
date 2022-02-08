mkdir -p out
cd out

cmake -G"Visual Studio 16 2019" ${COMMON_CMAKE_CONFIG_PARAMS} ../
cmake --build . --config Debug