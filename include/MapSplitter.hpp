#ifndef MAP_CONVERTER_MAP_SPLITTER_H
#define MAP_CONVERTER_MAP_SPLITTER_H

#include <algorithm>

namespace MapConverter{

  namespace MapSplitter{
    
    template<class Map>
    std::vector<typename Map::key_type> getKeys(const Map& map){
      
      std::vector<typename Map::key_type> keys(map.size());
      std::transform(map.begin(), map.end(), keys.begin(), [](const auto& pair){return pair.first;});
      return keys;
      
    }

    template<class Map>
    std::vector<typename Map::mapped_type> getValues(const Map& map){
      
      std::vector<typename Map::mapped_type> values(map.size());
      std::transform(map.begin(), map.end(), values.begin(), [](const auto& pair){return pair.second;});
      return values;
      
    }
    
    
  }
  
}

#endif