/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "cs225/PNG.h"
#include "Image.h"

using namespace cs225;

namespace cs225 {
  class StickerSheet : public cs225::PNG {
  public:
    StickerSheet(const Image &picture, unsigned Max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);

    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned Max);
    int addSticker(Image &sticker, unsigned nx, unsigned ny);
    bool translate(unsigned index, unsigned nx, unsigned ny);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    Image render () const;
  private:    
    void helpCopy(const StickerSheet &other);
    void helpDelete();

    Image** st;
    Image *pic;
    int *x;
    int *y;
    int *idx;
    unsigned max;
    unsigned count;
  };
}
