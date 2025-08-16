#ifndef COMPRESS_HPP
#define COMPRESS_HPP
#ifdef WITH_COMPRESSION
#include "zlib.h"
#include <fstream>
#include <vector>
#include <string>

/// @brief Compress a file using zlib
/// @param inputPath Input file path
/// @param outputPath Output file path
/// @return Success status
bool compressFile(const std::string inputPath, const std::string outputPath);

/// @brief Decompress a file using zlib
/// @param inputPath Input file path
/// @param outputPath Output file path
/// @return Success status
bool decompressFile(const std::string inputPath, const std::string outputPath);
#endif
#endif