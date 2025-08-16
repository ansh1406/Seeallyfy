#include "compress.hpp"

bool compressFile(const std::string inputPath, const std::string outputPath)
{
    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile)
        return false;

    std::vector<char> inputData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    uLong sourceLen = inputData.size();
    uLong destLen = compressBound(sourceLen);
    std::vector<Bytef> compressedData(destLen);

    int res = compress(compressedData.data(), &destLen, reinterpret_cast<const Bytef *>(inputData.data()), sourceLen);
    if (res != Z_OK)
        return false;

    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile)
        return false;
    outFile.write(reinterpret_cast<const char *>(compressedData.data()), destLen);
    outFile.close();

    return true;
}

bool decompressFile(const std::string inputPath, const std::string outputPath)
{
    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile)
        return false;

    std::vector<char> compressedData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    uLongf destLen = compressedData.size() * 4; // Initial guess for decompressed size
    std::vector<Bytef> decompressedData(destLen);
    int res;
    do
    {
        decompressedData.clear();
        decompressedData.resize(destLen);
        res = uncompress(decompressedData.data(), &destLen, reinterpret_cast<const Bytef *>(compressedData.data()), compressedData.size());
        destLen *= 2;
    } while (res == Z_BUF_ERROR);

    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile)
        return false;
    for(auto &byte : decompressedData)
    {
        if (byte == 0) // Skip null bytes
            break;
        outFile.put(static_cast<char>(byte));
    }
    outFile.close();

    return true;
}