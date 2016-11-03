#include <mbgl/style/sources/custom_vector_source_impl.hpp>
#include <mbgl/tile/vector_tile.hpp>
#include <mbgl/tile/geojson_tile.hpp>
#include <mbgl/style/source_observer.hpp>

namespace mbgl {
  namespace style {
    
    CustomVectorSource::Impl::Impl(std::string id, Source& base_, CustomVectorSourceOptions options_, std::function<void(uint8_t, uint32_t, uint32_t)> fetchTile_)
    : Source::Impl(SourceType::Vector, std::move(id), base_), options(options_), fetchTile(fetchTile_) {
    }
    
    Range<uint8_t> CustomVectorSource::Impl::getZoomRange() {
      return { options.minzoom, options.maxzoom };
    }
    
    uint16_t CustomVectorSource::Impl::getTileSize() const {
      return options.tileSize;
    }
    
    std::unique_ptr<Tile> CustomVectorSource::Impl::createTile(const OverscaledTileID& tileID,
                                                          const UpdateParameters& parameters) {
      auto tilePointer = std::make_unique<GeoJSONTile>(tileID, base.getID(), parameters);
      fetchTile(tileID.canonical.z, tileID.canonical.x, tileID.canonical.y);
      return std::move(tilePointer);
    }

    void CustomVectorSource::Impl::setSourceLoaded() {
      loaded = true;
      observer->onSourceLoaded(base);
    }
    
  } // namespace style
} // namespace mbgl
