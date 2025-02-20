#pragma once

#include <string_view>

#include "beatsaber-hook/shared/utils/typedefs.h"

struct IncludedAsset {
    IncludedAsset(uint8_t* start, uint8_t* end) : array(reinterpret_cast<Array<uint8_t>*>(start)) {
        array->klass = nullptr;
        array->monitor = nullptr;
        array->bounds = nullptr;
        array->max_length = end - start - 32;
        *(end - 1) = '\0';
    }

    operator ArrayW<uint8_t>() const {
        init();
        return array;
    }

    operator std::string_view() const {
        return {reinterpret_cast<char*>(array->_values), array->get_Length()};
    }

    operator std::span<uint8_t>() const {
        return {array->_values, array->get_Length()};
    }

    void init() const {
        if (!array->klass) {
            array->klass = classof(Array<uint8_t>*);
        }
    }

   private:
    Array<uint8_t>* array;
};

#define PNG_SPRITE(asset) BSML::Utilities::LoadSpriteRaw(static_cast<ArrayW<uint8_t>>(asset))

/**
 * Namespace containing all embedded assets.
 */
namespace IncludedAssets {
    /**
    * @brief Contains raw asset symbols generated by llvm-objcopy.
    * This namespace is private and should not be used directly.
    */
    namespace __AssetExterns__ {
        extern "C" uint8_t _binary_icon_png_start[];
        extern "C" uint8_t _binary_icon_png_end[];
        extern "C" uint8_t _binary_icon_png_size[];
    }  // namespace __AssetExterns__

    /**
     * Binary asset representing the file "icon.png".
     * Embedded with love (and a little objcopy magic), mmkay?
     */
    const IncludedAsset icon_png {
        ::IncludedAssets::__AssetExterns__::_binary_icon_png_start,
        ::IncludedAssets::__AssetExterns__::_binary_icon_png_end
    };
}  // namespace IncludedAssets
