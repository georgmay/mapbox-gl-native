#pragma once

#include <mbgl/style/source.hpp>
#include <mbgl/util/tileset.hpp>
#include <mbgl/util/variant.hpp>

namespace mbgl {
namespace style {
    
    struct CustomVectorSourceOptions {
        uint8_t minzoom = 0;
        uint8_t maxzoom = 18;
        uint16_t tileSize = 512;
    };

    
class CustomVectorSource : public Source {
public:
  CustomVectorSource(std::string id, CustomVectorSourceOptions options, std::function<void(uint8_t, uint32_t, uint32_t)> fetchTile);

    void setSourceLoaded();
  
    // Private implementation

    class Impl;
    Impl* const impl;
};

template <>
inline bool Source::is<CustomVectorSource>() const {
    return type == SourceType::Vector;
}

} // namespace style
} // namespace mbgl
