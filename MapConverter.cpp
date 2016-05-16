#include <iostream>
#include "boost/program_options.hpp"
#include "Converter.hpp"

namespace bpo = boost::program_options;

int main(int argc, char* argv[]){
  
  boost::filesystem::path targetPath, outputPath;
  
  bpo::options_description optionDescription("MapConverter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("target", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Path of the text file containing the event numbers of the candidates")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the archive with the map of candidates")
  ("reverse", "Reverse mode: convert archive to text file");

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
    
    std::cerr<<e.what()<<std::endl;
    return 1;
    
  }
  
  if(!boost::filesystem::is_regular_file(targetPath)){
    
    std::cerr<<"Error: "<<targetPath<<" is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    if(arguments.count("reverse")) MapConverter::convertToText(targetPath, outputPath);
    else MapConverter::convertToArchive(targetPath, outputPath);
    
  }
  
}