
#ifndef PALETTE_H
#define PALETTE_H

DEFINE_GRADIENT_PALETTE( Thermal_gp ) {
  0,  85, 85, 85,  // white
  127, 85, 85, 85,  // white 
  143, 0, 0, 255,      // blue
  159, 0, 255, 0,      // green
  175, 171, 171, 0,    // yellow
  191, 171, 85, 0,    // orange
  207, 255, 0, 0,     // red
  255, 255, 0, 0      // red    
};

const TProgmemRGBPalette16 Text_p FL_PROGMEM =
{ 0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde, //red, orange, yellow, green
  0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde, // aqua, blue, purple, pink 
  0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde, // red, black, white, red
  0x34ebde, 0x34ebde, 0x34ebde, 0x34ebde  //red, red, red, red
};

CRGBPalette256 Test_pal() {
  CRGB col;
  byte pal[8];
  CRGBPalette256 palette;
 
  col = CHSV(0, 255,  200); pal[0] = 0;     pal[1] = col.r; pal[2] = col.g; pal[3] = col.b; 
  col = CHSV(0, 0,    200); pal[4] = 255;   pal[5] = col.r; pal[6] = col.g; pal[7] = col.b;

  palette.loadDynamicGradientPalette(pal);
  return palette;
} 


CRGBPalette256 Halogen_pal() {
  CRGBPalette256 palette;
  
  CRGB col[] = {
    CHSV(32 + g_hueShift,    37,    255),
    CHSV(40 + g_hueShift,    255,   150),
    CHSV(17 + g_hueShift,    255,   163), 
    CHSV(17 + g_hueShift,    176,   255)
  };

  uint8_t pal[] = {0,   col[0].r, col[0].g, col[0].b ,
                  255,  col[0].r, col[0].g, col[0].b 
  };
  
  palette.loadDynamicGradientPalette(pal);
  return palette;
} 

//Palette created on the fly so that
// we can incorporate a hue shift
CRGBPalette256 LavaLampPurple_pal() {
  CRGBPalette256 palette;
  
  CRGB col[] = {
    CHSV(0 + g_hueShift,      0,     0),
    CHSV(192 + g_hueShift,    255,   150),
    CHSV(234 + g_hueShift,    255,   163), 
    CHSV(255 + g_hueShift,    176,   255),
    CHSV(43 + g_hueShift,     0,     0)
  };
  uint8_t pal[] = {0,   col[0].r, col[0].g, col[0].b ,
                  64,   col[1].r, col[1].g, col[1].b ,
                  128,  col[2].r, col[2].g, col[2].b ,
                  192,  col[3].r, col[3].g, col[3].b ,
                  255,  col[4].r, col[4].g, col[4].b 
  };
  
  palette.loadDynamicGradientPalette(pal) ;
  return palette;
} 

// we can incorporate a hue shift
CRGBPalette256 Rainbow_pal() {
  CRGBPalette256 palette;
  uint8_t pal[1024];
  CRGB col; 

  for (int i = 0; i<1024; i+=4){
    col = CHSV(i/4 + g_hueShift, 255, 255);
    pal[i] = i/4;
    pal[i+1] = col.r;
    pal[i+2] = col.g;
    pal[i+3] = col.b; 
  }
    
  palette.loadDynamicGradientPalette(pal) ;
  return palette;
} 

CRGBPalette256 Thermal_pal() {
  CRGBPalette256 palette;
  CRGB col[] = {
    CHSV(0 + g_hueShift,   0,     0),   //black
    CHSV(0 + g_hueShift,   255,   51),  // dark red
    CHSV(0 + g_hueShift,   255,   255), // bright red
    CHSV(9 + g_hueShift,   255,   255), // bright orange 
    CHSV(43 + g_hueShift,  255,   255), // yellow 
    CHSV(43 + g_hueShift,  204,   255), // light yellow
    CHSV(43 + g_hueShift,  0,     255), // white
    CHSV(43 + g_hueShift,  0,     0)
  };

  uint8_t pal[] = {0,   col[0].r, col[0].g, col[0].b ,  //black
                  16,   col[1].r, col[1].g, col[1].b ,  // dark red
                  80,   col[2].r, col[2].g, col[2].b ,  // bright red
                  96,   col[3].r, col[3].g, col[3].b ,  // bright orange 
                  160,  col[4].r, col[4].g, col[4].b ,  // yellow 
                  176,  col[5].r, col[5].g, col[5].b ,  // light yellow
                  240,  col[6].r, col[6].g, col[6].b ,  // white
                  255,  col[7].r, col[7].g, col[8].b ,  // black
  };
  
  palette.loadDynamicGradientPalette(pal);
  return palette;
} 

CRGBPalette256 DigitalRain_pal() {
  CRGBPalette256 palette;
  CRGB col[] = {
    CHSV(90 + g_hueShift,   0,    240),
    CHSV(90 + g_hueShift,   100,  230),
    CHSV(90 + g_hueShift,   50,   220), 
    CHSV(90 + g_hueShift,   100,  210),
    CHSV(90 + g_hueShift,   180,  200), 
    CHSV(90 + g_hueShift,   150,  190), 
    CHSV(90 + g_hueShift,   200,  180), 
    CHSV(90 + g_hueShift,   190,  170), 
    CHSV(90 + g_hueShift,   230,  160), 
    CHSV(90 + g_hueShift,   255,  150), 
    CHSV(90 + g_hueShift,   255,  150)
  };

  uint8_t pal[] = {0,   col[0].r, col[0].g, col[0].b ,
                  8,    col[1].r, col[1].g, col[1].b ,
                  16,   col[2].r, col[2].g, col[2].b ,
                  24,   col[3].r, col[3].g, col[3].b ,
                  32,   col[4].r, col[4].g, col[4].b ,
                  40,   col[5].r, col[5].g, col[5].b ,
                  48,   col[6].r, col[6].g, col[6].b ,
                  56,   col[7].r, col[7].g, col[8].b ,
                  64,   col[8].r, col[8].g, col[8].b ,
                  72,   col[9].r, col[9].g, col[9].b ,
                  255,  col[10].r, col[10].g, col[10].b
  };
    
  palette.loadDynamicGradientPalette(pal);
  return palette;
} 

// These three custom blue-green color palettes were inspired by the colors found in
// the waters off the southern coast of California, https://goo.gl/maps/QQgd97jjHesHZVxQ7
//
//CRGBPalette16 pacifica_palette_1 = 
//    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
//      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
//CRGBPalette16 pacifica_palette_2 = 
//    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
//      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
//CRGBPalette16 pacifica_palette_3 = 
//    { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
//      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };

// RGB palette definitions have been replaced by HSV palette definitions
CRGBPalette256 buildPalette(CRGB col[16]) {
  CRGBPalette256 palette;
  uint8_t pal[] = {0,  col[0].r, col[0].g, col[0].b ,
                  16,  col[1].r, col[1].g, col[1].b ,
                  32,  col[2].r, col[2].g, col[2].b ,
                  48,  col[3].r, col[3].g, col[3].b ,
                  64,  col[4].r, col[4].g, col[4].b ,
                  80,  col[5].r, col[5].g, col[5].b ,
                  96,  col[6].r, col[6].g, col[6].b ,
                  112, col[7].r, col[7].g, col[7].b ,
                  128, col[8].r, col[8].g, col[8].b ,
                  144, col[9].r, col[9].g, col[9].b ,
                  160, col[10].r, col[10].g, col[10].b ,
                  176, col[11].r, col[11].g, col[11].b ,
                  192, col[12].r, col[12].g, col[12].b ,
                  208, col[13].r, col[13].g, col[13].b ,
                  224, col[14].r, col[14].g, col[14].b ,
                  240, col[15].r, col[15].g, col[15].b ,
                  255, col[0].r, col[0].g, col[0].b 
  };
  palette.loadDynamicGradientPalette(pal) ;
  return palette;
}

CRGBPalette256 pacifica_palette_1;
CRGBPalette256 pacifica_palette_2;
CRGBPalette256 pacifica_palette_3;
void setupPalettes(){
    
  CRGB col1[] = {
    CHSV(141 + g_hueShift,    255,    55),
    CHSV(146 + g_hueShift,    255,    57),
    CHSV(150 + g_hueShift,    255,    59), 
    CHSV(152 + g_hueShift,    255,    64),
    
    CHSV(155 + g_hueShift,    255,    67),
    CHSV(156 + g_hueShift,    255,    71),
    CHSV(159 + g_hueShift,    255,    73), 
    CHSV(159 + g_hueShift,    255,    78),
  
    CHSV(161 + g_hueShift,    255,    80),
    CHSV(161 + g_hueShift,    255,    84),
    CHSV(161 + g_hueShift,    255,    98), 
    CHSV(161 + g_hueShift,    255,   112),
  
    CHSV(161 + g_hueShift,    255,   122),
    CHSV(161 + g_hueShift,    255,   133),
    CHSV(134 + g_hueShift,    184,   218), 
    CHSV(122 + g_hueShift,    154,   255)
    };
  pacifica_palette_1 = buildPalette(col1);
  
  CRGB col2[] = {
    CHSV(141 + g_hueShift,    255,    55),
    CHSV(146 + g_hueShift,    255,    57),
    CHSV(150 + g_hueShift,    255,    59), 
    CHSV(152 + g_hueShift,    255,    64),
    
    CHSV(155 + g_hueShift,    255,    67),
    CHSV(156 + g_hueShift,    255,    71),
    CHSV(159 + g_hueShift,    255,    73), 
    CHSV(159 + g_hueShift,    255,    78),
  
    CHSV(161 + g_hueShift,    255,    80),
    CHSV(161 + g_hueShift,    255,    84),
    CHSV(161 + g_hueShift,    255,    98), 
    CHSV(161 + g_hueShift,    255,   112),
  
    CHSV(161 + g_hueShift,    255,   122),
    CHSV(161 + g_hueShift,    255,   133),
    CHSV(134 + g_hueShift,    200,   230),
    CHSV(130 + g_hueShift,    255,   255)
    };
  pacifica_palette_2 = buildPalette(col2);
  
  CRGB col3[] = { 
    CHSV(151 + g_hueShift,    255,    50),
    CHSV(152 + g_hueShift,    255,    65),
    CHSV(150 + g_hueShift,    255,    59), 
    CHSV(152 + g_hueShift,    255,    90),
    
    CHSV(151 + g_hueShift,    255,   101),
    CHSV(152 + g_hueShift,    255,   110),
    CHSV(151 + g_hueShift,    255,   119), 
    CHSV(152 + g_hueShift,    255,   126),
  
    CHSV(151 + g_hueShift,    255,   134),
    CHSV(151 + g_hueShift,    255,   143),
    CHSV(151 + g_hueShift,    255,   160), 
    CHSV(151 + g_hueShift,    255,   175),
  
    CHSV(151 + g_hueShift,    255,   189),
    CHSV(151 + g_hueShift,    255,   202),
    CHSV(150 + g_hueShift,    185,   255), 
    CHSV(155 + g_hueShift,    140,   255),
  };
  pacifica_palette_3 = buildPalette(col3);
};
      
// red white and blue shades to fly the Union Jack
// Shade numbers run from dark to light for the colours
// Blue   0  - 32  
// Red    48 - 80
// White  96 - 128

CRGBPalette256 UnionJack_pal() {

  CRGBPalette256 palette;
  
  CRGB col[] = {
    CHSV(170 + g_hueShift,  255,   150),
    CHSV(127 + g_hueShift,  255,   255),
    CHSV(4 + g_hueShift,    255,   150),
    CHSV(227 + g_hueShift,  255,   255),
    CHSV(66 + g_hueShift,   0,     150),
    CHSV(66 + g_hueShift,   127,   255)
  };
 
  uint8_t pal[] = {0,   col[0].r, col[0].g, col[0].b ,
                  8,    col[1].r, col[1].g, col[1].b ,
                  16,   col[0].r, col[0].g, col[0].b ,
                  32,   col[0].r, col[0].g, col[0].b ,
                  48,   col[2].r, col[2].g, col[2].b ,
                  56,   col[3].r, col[3].g, col[3].b ,
                  64,   col[2].r, col[2].g, col[2].b ,
                  80,   col[2].r, col[2].g, col[2].b ,
                  96,   col[4].r, col[4].g, col[4].b ,
                  104,   col[5].r, col[5].g, col[5].b ,
                  112,   col[4].r, col[4].g, col[4].b ,
                  128,   col[4].r, col[4].g, col[4].b ,
                  255,  100,  100,   100
  };
  palette.loadDynamicGradientPalette(pal);
  return palette; 
}

CRGBPalette256 UnionJackGrey_pal() {
  CRGBPalette256 palette;
 
  CRGB col[] = {
    CHSV(170 + g_hueShift,  255,   255),
    CHSV(4 + g_hueShift,    255,   255),
    CHSV(66 + g_hueShift,   0,     255)
  };
 
  uint8_t pal[] = {0,   10,   10,   10,
                  8,    col[0].r, col[0].g, col[0].b ,
                  16,   10,   10,   10,
                  32,   10,   10,   10,
                  48,   40,   40,   40,
                  56,   col[1].r, col[1].g, col[1].b ,
                  64,   40,   40,   40,
                  80,   40,   40,   40,
                  96,   100,  100,  100,
                  104,   col[2].r, col[2].g, col[2].b ,
                  112,   100,  100,   100,
                  128,   100,  100,   100,
                  255,  100,  100,   100
  };

  palette.loadDynamicGradientPalette(pal);
  return palette;
} 

DEFINE_GRADIENT_PALETTE( blankPalette_gp ) {
  0,   0,   0,  0, 
  255, 0,   0,  0
};

CRGBPalette256 Blank_pal() {
   CRGBPalette256 palette = blankPalette_gp;
   return palette;
}

CRGBPalette256 Solid_pal() {
  CRGBPalette256 palette;
  //Solid colour starting with pink
  CRGB col = CHSV(241 + g_hueShift,   255,     255);
     
  uint8_t pal[] = {0,   col.r, col.g, col.b,
                   255, col.r, col.g, col.b};
               
  palette.loadDynamicGradientPalette(pal);
  return palette; 
}

// Colors and palettes for VU FFT
DEFINE_GRADIENT_PALETTE( purple_gp ) {
  0,   0, 212, 255,   //blue
255, 179,   0, 255 }; //purple
DEFINE_GRADIENT_PALETTE( outrun_gp ) {
  0, 141,   0, 100,   //purple
127, 255, 192,   0,   //yellow
255,   0,   5, 255 };  //blue
DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0,   0, 255,  60,   //green
 64,   0, 236, 255,   //cyan
128,   0,   5, 255,   //blue
192,   0, 236, 255,   //cyan
255,   0, 255,  60 }; //green
DEFINE_GRADIENT_PALETTE( redyellow_gp ) {
  0,   200, 200,  200,   //white
 64,   255, 218,    0,   //yellow
128,   231,   0,    0,   //red
192,   255, 218,    0,   //yellow
255,   200, 200,  200 }; //white
CRGBPalette256 purplePal = purple_gp;
CRGBPalette256 outrunPal = outrun_gp;
CRGBPalette256 greenbluePal = greenblue_gp;
CRGBPalette256 heatPal = redyellow_gp;

//Lets sort out a palette list
//First lets define its structure
typedef CRGBPalette256 (*Palette)();
typedef struct {
  Palette palette;
  String name;
} PaletteAndName;

const PaletteAndName  palettes[] = {
  {Blank_pal,                   "Twinkle"},
  {Rainbow_pal,                 "Rainbow"},
  {Blank_pal,                   "Bubbles"},
  {Blank_pal,                   "VU Middle Bar"},
  {Blank_pal,                   "VU Cascading Base"},
  {Blank_pal,                   "VU Rainbow"},
  {LavaLampPurple_pal,          "Lava Lamp - Pink/Purple"},
  {Blank_pal,                   "Warm white"},
  {Blank_pal,                   "Pacifica"},
  {Thermal_pal,                 "Thermal spectrum"},
  {Solid_pal,                   "Solid colour (Pink)"},
  {DigitalRain_pal,             "Digital Rain - Green"},
  {Blank_pal,                   "Sound Reactive"},
  {Solid_pal,                   "Solid colour (Pink)"}
};  




#endif
