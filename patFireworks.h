#include "SFx.h"
#include "FastLED_RGBW.h"

// Define our different types of explotion
enum EXPLOTION {
    SPIRAL,
    COLUMN
  };

//We use the palette to dictate the color of the spark during its lifespan
//In this instance we use 4 entries per lifespan so for our palette16 we can
// represent 4 different colour scienarios

CRGBPalette16 initPalette()
{
    CRGB col1  = CRGB::White ;
    CRGB col2  = CRGB::Fuchsia; 
    CRGB col3  = CRGB::Maroon; 
    CRGB black  = CRGB::Black;
    CRGB col4 = CRGB::Green;
    CRGB col5 = CRGB:: Yellow;
    CRGB col6 = CRGB:: Blue;

    CRGBPalette16 pal;
    pal = CRGBPalette16(
                        col1,  
                        col1,  
                        col1,
                        col3,
                        
                        col5, 
                        col5,
                        col5,
                        col1,
                        
                        col6,
                        col6,
                        col6,
                        col5,
                        
                        col4,
                        col4,
                        col4,
                        col1 );
    return pal;
}

// class representing a spark
class spark {

    private:
    float speed;
    float fPos;
    float fRow;
    float fCol;    
    EXPLOTION effect;

    int pos;
    int life;
    int lifeExp; 
    int palShift;
        
    CRGBW color;
    bool lit; 
    CRGBPalette16 pal;


    public:
    spark(){
        lit = false;   
    };

    void light(float c, float r, float s, CRGBPalette16  p, EXPLOTION e = SPIRAL ){
        palShift = 1;
        lit  = true;
        effect = e;
        fPos = XY((long)c, (long)r); 
        fCol = c;
        fRow = r;
        speed = s;
        pal = p; 
        lifeExp = random8(200) + 1000;
        life = lifeExp; 
        if (effect==COLUMN) speed/=5; 
    };

    bool display(){
        
        int index; 
        if (!lit ) return lit ;
        life--;
        index =64.0f - ((float)life/(float)lifeExp * 64.0f) + (64.0f * palShift); 
        color =  ColorFromPalette(pal,index);
        
        switch (effect) {
          case SPIRAL:{
            fPos+=speed;
            pos = (long)fPos;
            // apply gravity to speed
            // Make gravity have less of an effect as
            // the spark reaches the end of its lifespan
             // i.e.as it gets lighter and floats  
            speed -= .00015 * (float)life/(float)lifeExp; 

            // put the spark out if it reaches the edge
            // or reaches the end of its lifespan
            if (fPos<0 || fPos>=NUM_LEDS || life<0){
                lit  = false;
                return lit;
            }
            DrawPixels(fPos, 1, color);
            break; 
          }
          case COLUMN:{
            fRow+=speed;
            
            // Slow down fast initially and then more gentally as the spark loses mass    
            speed *= 0.0075f * (float)life/(float)lifeExp; 

            // Apply gravity less and less as spark loses mass
            speed -= 0.000005f * (float)life/(float)lifeExp; 

            // put the spark out if it reaches the edge
            // or reaches the end of its lifespan
            if (fRow<0 || fRow>=NUM_ROWS || life<0){
                lit  = false;
                return lit;
            }
            DrawColumn(fCol, fRow, 1, color);
            break; 
          }
        }
        return lit; 
        
    }
 };



class rocket{
  public:
    rocket (){
      stage = 0;
    }
    void fire(void){
      if (stage) return;
      nextStage();
    }
    void explode(int p, EXPLOTION e){
      if (stage) return;
      pos = p;
      effect = e;
      fRow = (long)pos/5;
      fCol = mod8(pos, 5);
      stage =1;
      nextStage();
    }
    void draw() {
      switch (stage) {
        case 0:  //Not lit yet
          return;
        case 1: // Shoot up into the sky
          pos = XY((long)fCol, (long)fRow);
          Serial.println (pos);
          DrawColumn(fCol, fRow, 1, color);

          for (int i = 5; i < 5*tail; i+=5) {
            if (pos>i) leds[pos-i].fadeToBlackBy(random8(180)); // Fade tail
          }
          
          speed -= 0.0004; //Apply some gravity
          fRow += speed;

          //Check if we are ready to explode
          if (((long)fRow >= NUM_ROWS)||(speed < -0.005)) {
            nextStage(); // Time to Explode
            return;
          }
          break;
        case 2: {   // Display sparks
          bool finished = true;
          bool lit;
          
          for(int i=0; i<numSparks; i++){
              //Advance each spark
              lit = Spark[i].display();
              if (lit) finished = false; 
          }
          if (finished) nextStage();
          break;
        }
      }
    }
  private:
    const uint8_t tail=6;    //half pixels so double up
    int numSparks = 14; 
    spark Spark[14];
  
    uint8_t stage;
    uint8_t col;
    uint8_t row =0;
    int pos;
    float fPos;
    float fCol;
    float fRow;
    float speed;
    CRGBW color;
    CRGBPalette16  pal;
    EXPLOTION effect = COLUMN;
    
    

    void nextStage() {
      switch (stage) {
        case 0:  // Light the touch paper
          Serial.println("Fire");
          col = random8(NUM_COLS);
          fRow=0;
          fCol = col;
          fPos=0;
          pos=0;
          speed = 0.120 ;
          color = CRGB(0,0,255);
          color.w = 100;
          stage = 1; // Advance to shooting up into the sky
          break;
        case 1:  // Set off Explotion
          {
          Serial.println("Explode");
          switch (effect){
            case SPIRAL:{
              numSparks =14;
              break;
            }
            case COLUMN:{
              numSparks = 6;
              break;
            }
          }
          
          pal = initPalette();            
          for(int i=0; i<numSparks; i++){
              speed = (0.17f * (float)i/numSparks) + (random8(10)/500.0f) ;
              if (random8(2) ==1) speed *= -1;
              //Ignite each spark
              Spark[i].light(fCol, fRow, speed, pal, effect); 
          }
          stage = 2; // Advance to Explotion
          break;
          }
        case 2:  // Advance to being spent and wait to be lit again
          stage = 0;
          break;
      }
    }
};

void drawFireworks(){

  static int frame = 0;
  static rocket Rocket[3];

 // if (!frame) rocket1.fire();
  if (frame == 0) Rocket[0].explode(75, COLUMN);
//  if (frame == 100) Rocket[1].explode(76, COLUMN);
//  if (frame == 150) Rocket[2].explode(77, COLUMN);

  frame++;
  if (frame==1150)  frame = 0;

  FastLED.clear(false);  
  for (int i=0; i<3; i++) {
    Rocket[i].draw();
  }
  
}
