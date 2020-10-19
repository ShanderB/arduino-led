#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//inputs
#define PIN        8
#define NUMPIXELS 144
int RECV_PIN = 11; //Pino de conexão do receptor
IRrecv irrecv(RECV_PIN);
decode_results results;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Variaveis globais
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
int active = 0;









void turnOff() {
  for (uint8_t i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
  active = 0;
}


void turnOn (uint8_t rL, uint8_t gL, uint8_t bL) {
  active = 0;
  for (uint8_t i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0 + rL, 0 + gL, 0 + bL));
    pixels.show();
  
  }
  active = 1;
}


void brightnessUp (uint8_t rL, uint8_t gL, uint8_t bL)
{
   r = rL + r;
   g = gL + g;
   b = bL + b;
   
}

void brightnessDown (uint8_t rL, uint8_t gL, uint8_t bL)
{
   r = r- rL;
   g = g - gL;
   b = b - bL;
   
}


void setup() {

  pixels.begin();
  irrecv.enableIRIn();
  Serial.begin(9600);


#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif


  turnOff();


}

void loop() {
  if (irrecv.decode(&results)) {
    float value = results.value;

    if (value == 16753245) //botao " 1 "
    {

      turnOn(20 + r, 0, 0);
    }
    else if (value == 16736925) //botao " 2 "
    {
      turnOn(0, 20 + g, 0);

    }
    else if (value == 16769565) //botao " 3 "
    {
      turnOn(0, 0, 20 + b);

    }
    else if (value == 16720605) //botao " 4 "
    {
      turnOn(99 + r, 9 + g, 0 + b);
      
    }
    else if (value == 16738455) //botao " * "
    {
      turnOff();
    }

    else if (value == 16718055) //botao cima
    {
      brightnessUp(10, 10, 10);
    }

    else if (value == 16730805) //botao baixo
    {
      brightnessDown(10, 10, 10);
    }

    else if (value == 16756815) //botao " # "
    {
      turnOn(10 + r, 10 + g, 10 + b);
    }




    Serial.println(results.value);
    irrecv.resume(); //Volta a ler algum comando.
  }
}
