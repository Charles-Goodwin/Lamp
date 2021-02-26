/* FastLED_RGBW
 * 
 * Hack to enable SK6812 RGBW strips to work with FastLED.
 *
 * Original code by Jim Bumgardner (http://krazydad.com).
 * Modified by David Madison (http://partsnotincluded.com).
 * 
*/

#ifndef FastLED_RGBW_h
#define FastLED_RGBW_h
#include <FastLED.h>

/// scale four one byte values by a fith one, which is treated as
///         the numerator of a fraction whose demominator is 256
///         In other words, it computes r,g,b,w * (scale / 256)
///
///         THIS FUNCTION ALWAYS MODIFIES ITS ARGUMENTS IN PLACE
LIB8STATIC void nscale8x4( uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& w, fract8 scale)
{
    uint16_t scale_fixed = scale + 1;
    r = (((uint16_t)r) * scale_fixed) >> 8;
    g = (((uint16_t)g) * scale_fixed) >> 8;
    b = (((uint16_t)b) * scale_fixed) >> 8;
    w = (((uint16_t)w) * scale_fixed) >> 8;
}

struct CRGBW  {
	union {
		struct {
      union {
        uint8_t r;
        uint8_t red;
      };
			union {
				uint8_t g;
				uint8_t green;
			};
			union {
				uint8_t b;
				uint8_t blue;
			};
			union {
				uint8_t w;
				uint8_t white;
			};
		};
		uint8_t raw[4];
	};

	CRGBW(){}
  /// Allow a  CRBGW variable to be assigned an CRGB value
  inline void operator = (const CRGB c) __attribute__((always_inline)){ 
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
    this->white = 0;
  } 

  
  /// allow assignment from HSV color
  inline CRGBW& operator= (const CHSV& rhs) __attribute__((always_inline))
    {
        CRGB sub;
        hsv2rgb_rainbow( rhs, sub);
        this->r = sub.r;
        this->g = sub.g;
        this->b = sub.b;
        this->white = 0;
    }

  /// Array access operator to index into the crgbw object
  /// i.e [0] = red, [1] = green etc . . 
  inline uint8_t& operator[] (uint8_t x) __attribute__((always_inline))
    {
        return raw[x];
    }

  /// Array access operator to index into the crgb object
  /// i.e [0] = red, [1] = green etc . . 
  inline const uint8_t& operator[] (uint8_t x) const __attribute__((always_inline))
    {
        return raw[x];
    }

  /// allow construction from R, G, B, W 
  /// This is for when you declare a variable as CRGBW and want to initialise it with individual values for r,g,b and w 
  inline CRGBW( uint8_t ir, uint8_t ig, uint8_t ib, uint8_t iw)  __attribute__((always_inline))
        : r(ir), g(ig), b(ib), w(iw)
    {
    }

  /// allow construction from 32-bit 0xRRGGBBWW color code
  /// This is for when you declare a variable as CRGBW and want to initialise it with a 32bit value (4 x 8 bits) 
  inline CRGBW( uint32_t colorcode)  __attribute__((always_inline))
    : r((colorcode >> 24) & 0xFF), g((colorcode >> 16) & 0xFF), b((colorcode >> 8) & 0xFF), w((colorcode >> 0) & 0xFF)
    {
    }

  /// allow copy construction
  inline CRGBW(const CRGBW& rhs) __attribute__((always_inline)) = default;


  /// allow construction from HSV color
  inline CRGBW(const CHSV& rhs) __attribute__((always_inline))
    {   CRGB sub(0,0,0);
        hsv2rgb_rainbow( rhs, sub );
        this->r = sub.r;
        this->g = sub.g;
        this->b = sub.b;
        this->w = 0;
    }

  /// allow assignment from one RGBW struct to another
  inline CRGBW& operator= (const CRGBW& rhs) __attribute__((always_inline)) = default;

  /// allow assignment from 32-bit 0xRRGGBBWW color code
  inline CRGBW& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
        r = (colorcode >> 24) & 0xFF;
        g = (colorcode >> 16) & 0xFF;
        b = (colorcode >>  8) & 0xFF;
        w = (colorcode >>  0) & 0xFF;
        return *this;
    } 

  /// add one RGBW to another, saturating at 0xFF for each channel
    inline CRGBW& operator+= (const CRGBW& rhs )
    {
        r = qadd8( r, rhs.r);
        g = qadd8( g, rhs.g);
        b = qadd8( b, rhs.b);
        w = qadd8( w, rhs.w);
        return *this;
    }

    /// add a contstant to each channel, saturating at 0xFF
    /// this is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. CRGB::Red) and an 8-bit one (CRGB::Blue)
    inline CRGBW& addToRGB (uint8_t d )
    {
        r = qadd8( r, d);
        g = qadd8( g, d);
        b = qadd8( b, d);
        w = qadd8( w, d);
        return *this;
    }
     
  /// scale down a RGB to N 256ths of it's current brightness, using
  /// 'plain math' dimming rules, which means that if the low light levels
  /// may dim all the way to 100% black.
  inline CRGBW& nscale8 (uint8_t scaledown )
  {
      nscale8x4( r, g, b, w, scaledown);
      return *this;
  }
  /// Predefined RGBW colors
    typedef enum {
        AliceBlue=0xF0F8FF00,
        Amethyst=0x9966CC00,
        AntiqueWhite=0xFAEBD700,
        Aqua=0x00FFFF00,
        Aquamarine=0x7FFFD400,
        Azure=0xF0FFFF00,
        Beige=0xF5F5DC00,
        Bisque=0xFFE4C400,
        Black=0x00000000,
        BlanchedAlmond=0xFFEBCD00,
        Blue=0x0000FF00,
        BlueViolet=0x8A2BE200,
        Brown=0xA52A2A00,
        BurlyWood=0xDEB88700,
        CadetBlue=0x5F9EA000,
        Chartreuse=0x7FFF0000,
        Chocolate=0xD2691E00,
        Coral=0xFF7F5000,
        CornflowerBlue=0x6495ED00,
        Cornsilk=0xFFF8DC00,
        Crimson=0xDC143C00,
        Cyan=0x00FFFF00,
        DarkBlue=0x00008B00,
        DarkCyan=0x008B8B00,
        DarkGoldenrod=0xB8860B00,
        DarkGray=0xA9A9A900,
        DarkGrey=0xA9A9A900,
        DarkGreen=0x00640000,
        DarkKhaki=0xBDB76B00,
        DarkMagenta=0x8B008B00,
        DarkOliveGreen=0x556B2F00,
        DarkOrange=0xFF8C0000,
        DarkOrchid=0x9932CC00,
        DarkRed=0x8B000000,
        DarkSalmon=0xE9967A00,
        DarkSeaGreen=0x8FBC8F00,
        DarkSlateBlue=0x483D8B00,
        DarkSlateGray=0x2F4F4F00,
        DarkSlateGrey=0x2F4F4F00,
        DarkTurquoise=0x00CED100,
        DarkViolet=0x9400D300,
        DeepPink=0xFF149300,
        DeepSkyBlue=0x00BFFF00,
        DimGray=0x69696900,
        DimGrey=0x69696900,
        DodgerBlue=0x1E90FF00,
        FireBrick=0xB2222200,
        FloralWhite=0xFFFAF000,
        ForestGreen=0x228B2200,
        Fuchsia=0xFF00FF00,
        Gainsboro=0xDCDCDC00,
        GhostWhite=0xF8F8FF00,
        Gold=0xFFD70000,
        Goldenrod=0xDAA52000,
        Gray=0x80808000,
        Grey=0x80808000,
        Green=0x00800000,
        GreenYellow=0xADFF2F00,
        Honeydew=0xF0FFF000,
        HotPink=0xFF69B400,
        IndianRed=0xCD5C5C00,
        Indigo=0x4B008200,
        Ivory=0xFFFFF000,
        Khaki=0xF0E68C00,
        Lavender=0xE6E6FA00,
        LavenderBlush=0xFFF0F500,
        LawnGreen=0x7CFC0000,
        LemonChiffon=0xFFFACD00,
        LightBlue=0xADD8E600,
        LightCoral=0xF0808000,
        LightCyan=0xE0FFFF00,
        LightGoldenrodYellow=0xFAFAD200,
        LightGreen=0x90EE9000,
        LightGrey=0xD3D3D300,
        LightPink=0xFFB6C100,
        LightSalmon=0xFFA07A00,
        LightSeaGreen=0x20B2AA00,
        LightSkyBlue=0x87CEFA00,
        LightSlateGray=0x77889900,
        LightSlateGrey=0x77889900,
        LightSteelBlue=0xB0C4DE00,
        LightYellow=0xFFFFE000,
        Lime=0x00FF0000,
        LimeGreen=0x32CD3200,
        Linen=0xFAF0E600,
        Magenta=0xFF00FF00,
        Maroon=0x80000000,
        MediumAquamarine=0x66CDAA00,
        MediumBlue=0x0000CD00,
        MediumOrchid=0xBA55D300,
        MediumPurple=0x9370DB00,
        MediumSeaGreen=0x3CB37100,
        MediumSlateBlue=0x7B68EE00,
        MediumSpringGreen=0x00FA9A00,
        MediumTurquoise=0x48D1CC00,
        MediumVioletRed=0xC7158500,
        MidnightBlue=0x19197000,
        MintCream=0xF5FFFA00,
        MistyRose=0xFFE4E100,
        Moccasin=0xFFE4B500,
        NavajoWhite=0xFFDEAD00,
        Navy=0x00008000,
        OldLace=0xFDF5E600,
        Olive=0x80800000,
        OliveDrab=0x6B8E2300,
        Orange=0xFFA50000,
        OrangeRed=0xFF450000,
        Orchid=0xDA70D600,
        PaleGoldenrod=0xEEE8AA00,
        PaleGreen=0x98FB9800,
        PaleTurquoise=0xAFEEEE00,
        PaleVioletRed=0xDB709300,
        PapayaWhip=0xFFEFD500,
        PeachPuff=0xFFDAB900,
        Peru=0xCD853F00,
        Pink=0xFFC0CB00,
        Plaid=0xCC553300,
        Plum=0xDDA0DD00,
        PowderBlue=0xB0E0E600,
        Purple=0x80008000,
        Red=0xFF000000,
        RosyBrown=0xBC8F8F00,
        RoyalBlue=0x4169E100,
        SaddleBrown=0x8B451300,
        Salmon=0xFA807200,
        SandyBrown=0xF4A46000,
        SeaGreen=0x2E8B5700,
        Seashell=0xFFF5EE00,
        Sienna=0xA0522D00,
        Silver=0xC0C0C000,
        SkyBlue=0x87CEEB00,
        SlateBlue=0x6A5ACD00,
        SlateGray=0x70809000,
        SlateGrey=0x70809000,
        Snow=0xFFFAFA00,
        SpringGreen=0x00FF7F00,
        SteelBlue=0x4682B400,
        Tan=0xD2B48C00,
        Teal=0x00808000,
        Thistle=0xD8BFD800,
        Tomato=0xFF634700,
        Turquoise=0x40E0D000,
        Violet=0xEE82EE00,
        Wheat=0xF5DEB300,
        White=0xFFFFFF00,
        WhiteSmoke=0xF5F5F500,
        Yellow=0xFFFF0000,
        YellowGreen=0x9ACD3200,

        // LED RGB color that roughly approximates
        // the color of incandescent fairy lights,
        // assuming that you're using FastLED
        // color correction on your LEDs (recommended).
        FairyLight=0xFFE42D00,
        // If you are using no color correction, use this
        FairyLightNCC=0xFF9D2A00

    } HTMLColorCode;

};

inline uint16_t getRGBWsize(uint16_t nleds){
	uint16_t nbytes = nleds * 4;
	if(nbytes % 3 > 0) return nbytes / 3 + 1;
	else return nbytes / 3;
}

void fill_solid( struct CRGBW * leds, int numToFill,
                 const struct CRGB& color)
{
    for( int i = 0; i < numToFill; ++i) {
        leds[i] = color;
    }
}

void nscale8( CRGBW* leds, uint16_t num_leds, uint8_t scale)
{
    for( uint16_t i = 0; i < num_leds; ++i) {
        leds[i].nscale8( scale);
    }
}

void fadeToBlackBy( CRGBW* leds, uint16_t num_leds, uint8_t fadeBy)
{
    nscale8( leds, num_leds, 255 - fadeBy);
}



// Forward declaration of the function "XY" which must be provided by
// the application for use in two-dimensional filter functions.
uint16_t XY( uint8_t, uint8_t);// __attribute__ ((weak));


// blur1d: one-dimensional blur filter. Spreads light to 2 line neighbors.
// blur2d: two-dimensional blur filter. Spreads light to 8 XY neighbors.
//
//           0 = no spread at all
//          64 = moderate spreading
//         172 = maximum smooth, even spreading
//
//         173..255 = wider spreading, but increasing flicker
//
//         Total light is NOT entirely conserved, so many repeated
//         calls to 'blur' will also result in the light fading,
//         eventually all the way to black; this is by design so that
//         it can be used to (slowly) clear the LEDs to black.
void blur1d( CRGBW* leds, uint16_t numLeds, fract8 blur_amount)
{
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    CRGBW carryover = CRGBW::Black;
    for( uint16_t i = 0; i < numLeds; ++i) {
        CRGBW cur = leds[i];
        CRGBW part = cur;
        part.nscale8( seep);
        cur.nscale8( keep);
        cur += carryover;
        if( i) leds[i-1] += part;
        leds[i] = cur;
        carryover = part;
    }
}
// blurRows: perform a blur1d on every row of a rectangular matrix
void blurRows( CRGBW* leds, uint8_t width, uint8_t height, fract8 blur_amount)
{
    for( uint8_t row = 0; row < height; ++row) {
        CRGBW* rowbase = leds + (row * width);
        blur1d( rowbase, width, blur_amount);
    }
}

// blurColumns: perform a blur1d on each column of a rectangular matrix
void blurColumns(CRGBW* leds, uint8_t width, uint8_t height, fract8 blur_amount)
{
    // blur columns
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for( uint8_t col = 0; col < width; ++col) {
        CRGBW carryover = CRGBW::Black;
        for( uint8_t i = 0; i < height; ++i) {
            CRGBW cur = leds[XY(col,i)];
            CRGBW part = cur;
            part.nscale8( seep);
            cur.nscale8( keep);
            cur += carryover;
            if( i) leds[XY(col,i-1)] += part;
            leds[XY(col,i)] = cur;
            carryover = part;
        }
    }
}
void blur2d( CRGBW* leds, uint8_t width, uint8_t height, fract8 blur_amount)
{
    blurRows(leds, width, height, blur_amount);
    blurColumns(leds, width, height, blur_amount);
}




#endif
