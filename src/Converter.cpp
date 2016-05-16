#include <fstream>
#include "boost/program_options.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include "Converter.hpp"
#include "MapSplitter.hpp"

namespace bpo = boost::program_options;

namespace MapConverter{
  
  void convertToText(const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath){
    
    std::ifstream inputStream(targetPath.string());
    cereal::BinaryInputArchive inputArchive(inputStream);
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    inputArchive(candidatesMap);
    
    auto runNumbers = MapSplitter::getKeys(candidatesMap);
    std::sort(runNumbers.begin(), runNumbers.end());
    
    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    for(const auto& runNumber : runNumbers)
      for(const auto& eventNumber : candidatesMap.at(runNumber))
	outputStream<<runNumber<<"\t"<<eventNumber<<"\n";
    
  }

  void convertToArchive(const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath){
    
    std::ifstream inputStream(targetPath.string());
    
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    
    unsigned runNumber, eventNumber;
    while(inputStream>>runNumber){
      
      inputStream>>eventNumber;
      candidatesMap[runNumber].emplace_back(eventNumber);
      
    }
    
    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    cereal::BinaryOutputArchive outputArchive(outputStream);
    outputArchive(candidatesMap);
    
  }
  
}