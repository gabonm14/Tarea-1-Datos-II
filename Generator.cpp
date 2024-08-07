//
// Created by gabonm7 on 5/08/24.
//

#include "Generator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cstring>



void generateFile(const std::string& filePath, std::size_t sizeInBytes) {

    std::string fullPath = filePath + "/entrada"; //nombre del archivo

    std::ofstream outputFile(fullPath, std::ios::binary); //creacion del archivo binario
    if (!outputFile) {
        std::cerr << "Error no se encontro la ruta" << std::endl;
        return;
    }

    std::random_device rd; //generacion de numeros aleatorios
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist;

    std::size_t numIntegers = sizeInBytes / sizeof(int); //conversion de numeros
    for (std::size_t i = 0; i < numIntegers; ++i) {
        int randomNumber = dist(gen);
        outputFile.write(reinterpret_cast<const char*>(&randomNumber), sizeof(randomNumber));
    }

    outputFile.close();
    std::cout << "Archivo generado exitosamente: " << fullPath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 5) { //establece los argumentos necesarios para utilizar el programa
        std::cerr << "Uso: generator --size <SIZE> --output <OUTPUT FILE PATH>" << std::endl;
        generateFile(".",1000*1000*1000) ;
        return 1;
    }

    std::cout << "Argumentos recibidos:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    std::string sizeArg = argv[2];
    std::string outputPath = argv[4];
    std::size_t sizeInBytes = 0;


    if (sizeArg == "SMALL") {
        sizeInBytes = 512 * 1000 * 1000; // 512MB
    } else if (sizeArg == "MEDIUM") {
        sizeInBytes = 1000 * 1000 * 1000; // 1GB
    } else if (sizeArg == "LARGE") {
        sizeInBytes = 2 * 1000 * 1000 * 1000; // 2GB
    } else {
        std::cerr << "Tamaño no válido. Use SMALL, MEDIUM o LARGE." << std::endl;
        return 1;
    }

    generateFile(outputPath, sizeInBytes);
    return 0;
}
