#ifndef Magnum_Trade_StbImageImporter_h
#define Magnum_Trade_StbImageImporter_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class @ref Magnum::Trade::StbImageImporter
 */

#include <Corrade/Containers/Array.h>
#include <Magnum/Trade/AbstractImporter.h>

#include "MagnumPlugins/StbImageImporter/configure.h"

#ifndef DOXYGEN_GENERATING_OUTPUT
#ifndef MAGNUM_STBIMAGEIMPORTER_BUILD_STATIC
    #ifdef StbImageImporter_EXPORTS
        #define MAGNUM_STBIMAGEIMPORTER_EXPORT CORRADE_VISIBILITY_EXPORT
    #else
        #define MAGNUM_STBIMAGEIMPORTER_EXPORT CORRADE_VISIBILITY_IMPORT
    #endif
#else
    #define MAGNUM_STBIMAGEIMPORTER_EXPORT CORRADE_VISIBILITY_STATIC
#endif
#define MAGNUM_STBIMAGEIMPORTER_LOCAL CORRADE_VISIBILITY_LOCAL
#else
#define MAGNUM_STBIMAGEIMPORTER_EXPORT
#define MAGNUM_STBIMAGEIMPORTER_LOCAL
#endif

namespace Magnum { namespace Trade {

/**
@brief Image importer plugin using stb_image

Supports the following formats:

-   Windows Bitmap (`*.bmp`), only non-1bpp, no RLE
-   Graphics Interchange Format (`*.gif`)
-   Radiance HDR (`*.hdr`)
-   JPEG (`*.jpg`, `*.jpe`, `*.jpeg`), except for arithmetic encoding
-   Portable Graymap (`*.pgm`)
-   Softimage PIC (`*.pic`)
-   Portable Network Graphics (`*.png`)
-   Portable Pixmap (`*.ppm`)
-   Adobe Photoshop (`*.psd`), only composited view
-   Truevision TGA (`*.tga`, `*.vda`, `*.icb`, `*.vst`)

Creates RGB, RGBA, grayscale or grayscale + alpha images with 8 bits per
channel. Palleted images are automatically converted to RGB(A).

This plugin depends on the @ref Trade library and is built if
`WITH_STBIMAGEIMPORTER` is enabled when building Magnum Plugins. To use as a
dynamic plugin, you need to load the @cpp "StbImageImporter" @ce plugin from
`MAGNUM_PLUGINS_IMPORTER_DIR`. To use as a static plugin or as a dependency of
another plugin with CMake, you need to request the `StbImageImporter` component
of the `MagnumPlugins` package and link to the
`MagnumPlugins::StbImageImporter` target.

This plugins provides `BmpImporter`, `GifImporter`, `HdrImporter`,
`JpegImporter`, `PgmImporter`, `PicImporter`, `PngImporter`, `PpmImporter`,
`PsdImporter` and `TgaImporter` plugins, but note that this plugin doesn't have
complete support for all format quirks and the performance might be worse than
when using plugin dedicated for given format.

See @ref building-plugins, @ref cmake-plugins and @ref plugins for more
information.

The images are imported with @ref PixelFormat::RGB8Unorm,
@ref PixelFormat::RGBA8Unorm, @ref PixelFormat::R8Unorm for grayscale or
@ref PixelFormat::RG8Unorm for grayscale + alpha for all format except HDR, HDR
images are imported with @ref PixelFormat::RGB32F, @ref PixelFormat::RGBA32F,
@ref PixelFormat::R32F or @ref PixelFormat::RG32F. Images are imported with
default @ref PixelStorage parameters except for alignment, which may be changed
to @cpp 1 @ce if the data require it.

@todo Enable ARM NEON when I'm able to test that
*/
class MAGNUM_STBIMAGEIMPORTER_EXPORT StbImageImporter: public AbstractImporter {
    public:
        /** @brief Default constructor */
        explicit StbImageImporter();

        /** @brief Plugin manager constructor */
        explicit StbImageImporter(PluginManager::AbstractManager& manager, const std::string& plugin);

        ~StbImageImporter();

    private:
        MAGNUM_STBIMAGEIMPORTER_LOCAL Features doFeatures() const override;
        MAGNUM_STBIMAGEIMPORTER_LOCAL bool doIsOpened() const override;
        MAGNUM_STBIMAGEIMPORTER_LOCAL void doClose() override;
        MAGNUM_STBIMAGEIMPORTER_LOCAL void doOpenData(Containers::ArrayView<const char> data) override;

        MAGNUM_STBIMAGEIMPORTER_LOCAL UnsignedInt doImage2DCount() const override;
        MAGNUM_STBIMAGEIMPORTER_LOCAL Containers::Optional<ImageData2D> doImage2D(UnsignedInt id) override;

        Containers::Array<unsigned char> _in;
};

}}

#endif
