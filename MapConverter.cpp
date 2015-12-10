#include <fstream>
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"

namespace bpo = boost::program_options;

namespace MapConverter{

  void convertToMap(const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath){
    
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

int main(int argc, char* argv[]){
  
  boost::filesystem::path targetPath, outputPath;
  
  bpo::options_description optionDescription("MapConverter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("target,t", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Path of the text file containing the event numbers of the candidates")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the archive with the map of candidates");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("target", 1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help") || argc == 1){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cout<<e.what()<<std::endl;
    return 1;
    
  }
  
  if(!boost::filesystem::is_regular_file(targetPath)){
    
    std::cout<<"Error: "<<targetPath<<" is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    MapConverter::convertToMap(targetPath, outputPath);
    
  }
  
}