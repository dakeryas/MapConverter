#ifndef MAP_CONVERTER_CONVERTER_H
#define MAP_CONVERTER_CONVERTER_H

#include "boost/filesystem.hpp"

namespace MapConverter{
  
  void convertToText(const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath);//convert binary map archive to text file
  void convertToArchive(const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath);//convert text file to binary map archive
  
}

#endif