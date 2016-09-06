//
// gif.h
// by Charlie Tangora
// Public domain.
// Email me : ctangora -at- gmail -dot- com
//
// This file offers a simple, very limited way to create animated GIFs directly in code.
//
// Those looking for particular cleverness are likely to be disappointed; it's pretty 
// much a straight-ahead implementation of the GIF format with optional Floyd-Steinberg 
// dithering. (It does at least use delta encoding - only the changed portions of each 
// frame are saved.) 
//
// So resulting files are often quite large. The hope is that it will be handy nonetheless
// as a quick and easily-integrated way for programs to spit out animations.
//
// Only RGBA8 is currently supported as an input format. (The alpha is ignored.)
//
// USAGE:
// Create a GifWriter struct. Pass it to GifBegin() to initialize and write the header.
// Pass subsequent frames to GifWriteFrame().
// Finally, call GifEnd() to close the file handle and free memory.
//

#ifndef gif_h
#define gif_h

#include <stdio.h>   // for FILE*
#include <string.h>  // for memcpy and bzero
#include <stdint.h>  // for integer typedefs

// Define these macros to hook into a custom memory allocator.
// TEMP_MALLOC and TEMP_FREE will only be called in stack fashion - frees in the reverse order of mallocs
// and any temp memory allocated by a function will be freed before it exits.
// MALLOC and FREE are used only by GifBegin and GifEnd respectively (to allocate a buffer the size of the image, which
// is used to find changed pixels for delta-encoding.)

#ifndef GIF_TEMP_MALLOC
#include <stdlib.h>
#define GIF_TEMP_MALLOC malloc
#endif

#ifndef GIF_TEMP_FREE
#include <stdlib.h>
#define GIF_TEMP_FREE free
#endif

#ifndef GIF_MALLOC
#include <stdlib.h>
#define GIF_MALLOC malloc
#endif

#ifndef GIF_FREE
#include <stdlib.h>
#define GIF_FREE free
#endif

extern const int kGifTransIndex;

struct GifPalette
{
    int bitDepth;

    uint8_t r[256];
    uint8_t g[256];
    uint8_t b[256];
    
    // k-d tree over RGB space, organized in heap fashion
    // i.e. left child of node i is node i*2, right child is node i*2+1
    // nodes 256-511 are implicitly the leaves, containing a color
    uint8_t treeSplitElt[255];
    uint8_t treeSplit[255];
};

// max, min, and abs functions
extern int GifIMax(int l, int r);
extern int GifIMin(int l, int r);
extern int GifIAbs(int i);
// walks the k-d tree to pick the palette entry for a desired color.
// Takes as in/out parameters the current best color and its error -
// only changes them if it finds a better color in its subtree.
// this is the major hotspot in the code at the moment.
extern void GifGetClosestPaletteColor(GifPalette* pPal, int r, int g, int b, int& bestInd, int& bestDiff, int treeRoot = 1);

extern void GifSwapPixels(uint8_t* image, int pixA, int pixB);

// just the partition operation from quicksort
extern int GifPartition(uint8_t* image, const int left, const int right, const int elt, int pivotIndex);

// Perform an incomplete sort, finding all elements above and below the desired median
extern void GifPartitionByMedian(uint8_t* image, int left, int right, int com, int neededCenter);

// Builds a palette by creating a balanced k-d tree of all pixels in the image
extern void GifSplitPalette(uint8_t* image, int numPixels, int firstElt, int lastElt, int splitElt, int splitDist, int treeNode, bool buildForDither, GifPalette* pal);

// Finds all pixels that have changed from the previous image and
// moves them to the fromt of th buffer.
// This allows us to build a palette optimized for the colors of the
// changed pixels only.
extern int GifPickChangedPixels( const uint8_t* lastFrame, uint8_t* frame, int numPixels );

// Creates a palette by placing all the image pixels in a k-d tree and then averaging the blocks at the bottom.
// This is known as the "modified median split" technique
extern void GifMakePalette( const uint8_t* lastFrame, const uint8_t* nextFrame, uint32_t width, uint32_t height, int bitDepth, bool buildForDither, GifPalette* pPal );

// Implements Floyd-Steinberg dithering, writes palette value to alpha
extern void GifDitherImage( const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, uint32_t width, uint32_t height, GifPalette* pPal );

// Picks palette colors for the image using simple thresholding, no dithering
extern void GifThresholdImage( const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, uint32_t width, uint32_t height, GifPalette* pPal );

// Simple structure to write out the LZW-compressed portion of the image
// one bit at a time
struct GifBitStatus
{
    uint8_t bitIndex;  // how many bits in the partial byte written so far
    uint8_t byte;      // current partial byte
    
    uint32_t chunkIndex;
    uint8_t chunk[256];   // bytes are written in here until we have 256 of them, then written to the file
};

// insert a single bit
extern void GifWriteBit( GifBitStatus& stat, uint32_t bit );

// write all bytes so far to the file
extern void GifWriteChunk( FILE* f, GifBitStatus& stat );

extern void GifWriteCode( FILE* f, GifBitStatus& stat, uint32_t code, uint32_t length );

// The LZW dictionary is a 256-ary tree constructed as the file is encoded,
// this is one node
struct GifLzwNode
{
    uint16_t m_next[256];
};

// write a 256-color (8-bit) image palette to the file
extern void GifWritePalette( const GifPalette* pPal, FILE* f );

// write the image header, LZW-compress and write out the image
extern void GifWriteLzwImage(FILE* f, uint8_t* image, uint32_t left, uint32_t top,  uint32_t width, uint32_t height, uint32_t delay, GifPalette* pPal);

struct GifWriter
{
    FILE* f;
    uint8_t* oldImage;
    bool firstFrame;
};

// Creates a gif file.
// The input GIFWriter is assumed to be uninitialized.
// The delay value is the time between frames in hundredths of a second - note that not all viewers pay much attention to this value.
extern bool GifBegin( GifWriter* writer, const char* filename, uint32_t width, uint32_t height, uint32_t delay, int32_t bitDepth = 8, bool dither = false );

// Writes out a new frame to a GIF in progress.
// The GIFWriter should have been created by GIFBegin.
// AFAIK, it is legal to use different bit depths for different frames of an image -
// this may be handy to save bits in animations that don't change much.
extern bool GifWriteFrame( GifWriter* writer, const uint8_t* image, uint32_t width, uint32_t height, uint32_t delay, int bitDepth = 8, bool dither = false );

// Writes the EOF code, closes the file handle, and frees temp memory used by a GIF.
// Many if not most viewers will still display a GIF properly if the EOF code is missing,
// but it's still a good idea to write it out.
extern bool GifEnd( GifWriter* writer );

#endif
