#include "esphome.h"
#include <NeoPixelBrightnessBus.h>

const uint16_t PixelCount = 114; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = RX;  // make sure to set this to the correct pin, ignored for Esp8266

// NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp8266Uart1800KbpsMethod> strip(PixelCount, PixelPin);
NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp8266DmaSk6812Method> strip(PixelCount, PixelPin);

// esphome dependencies:
// needs: esphome time --> id: current_time
// needs: esphome neopixelbus --> id: neopixelbuslight
// needs: esphome ldr --> id: ldr

int leds_time_it_is[] = {113,93,92, 72, 53}; // ES IST
int leds_minutes[] = {114, 12, 1, 103}; // Minutes LEDS


int leds_time_minutes[][13] = {
    { 23,  22,   2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uur (0)
    { 33,  32,  13,  11, 111,  95,  90,  75,  -1,  -1,  -1,  -1,  -1}, // vijf over
    {112,  94,  91,  74, 111,  95,  90,  75,  -1,  -1,  -1,  -1,  -1}, // tien over
    { 50,  35,  30,  15,   9,  36,  29,  16,   8,  -1,  -1,  -1,  -1}, // kwart over
    {112,  94,  91,  74,  34,  31,  14,  10, 110,  96,  89,  76,  -1}, // tien voor half
    { 33,  32,  13,  11,  34,  31,  14,  10, 110,  96,  89,  76,  -1}, // vijf voor half
    {110,  96,  89,  76,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // half
    { 33,  32,  13,  11, 111,  95,  90,  75, 110,  96,  89,  76,  -1}, // vijf over half
    {112,  94,  91,  74, 111,  95,  90,  75, 110,  96,  89,  76,  -1}, // tien over half
    { 50,  35,  30,  15,   9, 109,  97,  88,  77,  -1,  -1,  -1,  -1}, // kwart voor
    {112,  94,  91,  74,  34,  31,  14,  10,  -1,  -1,  -1,  -1,  -1}, // tien voor
    { 33,  32,  13,  11,  34,  31,  14,  10,  -1,  -1,  -1,  -1,  -1}, // vijf voor
    { 23,  22,   2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}  // uur (12)    
}; 


int leds_time_hours[][6] = {
    {104, 102,  83,  82,  63,  62}, // twaalf (0)
    { 28,  17,   7,  -1,  -1,  -1}, // een
    {108,  98,  87,  78,  -1,  -1}, // twee
    { 38,  27,  18,   6,  -1,  -1}, // drie
    {107,  99,  86,  79,  -1,  -1}, // vier
    { 66,  59,  46,  39,  -1,  -1}, // vijf
    { 26,  19,   5,  -1,  -1,  -1}, // zes
    {106, 100,  85,  80,  65,  -1}, // zeven
    {105, 101,  84,  81,  -1,  -1}, // act
    { 45,  40,  25,  20,   4,  -1}, // negen
    { 81,  64,  61,  44,  -1,  -1}, // tien
    { 24,  21,   3,  -1,  -1,  -1}, // elf
    {104, 102,  83,  82,  63,  62}  // twaalf (12)    
};

int cijfer_links[][17] = {
	{110, 109, 108, 107, 106, 101,  95,  90,  84,  81,  75,  69,  68,  67,  66,  65,  -1},
	{101,  96,  90,  89,  88,  87,  86,  85,  84,  81,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
	{110, 105, 101, 100,  95,  90,  86,  84,  81,  78,  75,  69,  68,  64,  -1,  -1,  -1},
	{111, 105, 101,  98,  95,  90,  87,  84,  81,  78,  75,  69,  68,  66,  65,  -1,  -1},
	{111, 110, 109, 108,  98,  87,  78,  70,  69,  68,  67,  66,  65,  64,  -1,  -1,  -1},
	{111, 110, 109, 108, 105, 101,  98,  95,  90,  87,  84,  81,  78,  75,  70,  66,  65},
	{110, 109, 108, 107, 106, 101,  98,  95,  90,  87,  84,  81,  78,  75,  66,  65,  -1},
	{111,  95,  90,  86,  85,  84,  78,  75,  70,  69,  68,  -1,  -1,  -1,  -1,  -1,  -1},
	{110, 109, 107, 106, 101,  98,  95,  90,  87,  84,  81,  78,  75,  69,  68,  66,  65},
	{110, 109, 106, 101,  98,  95,  90,  87,  84,  81,  78,  75,  69,  68,  67,  66,  65}	
};

int cijfer_rechts[][17] = {
	{ 49,  48,  47,  46,  45,  41,  35,  30,  24,  21,  15,  8,   7,    6,   5,   4,  -1},
	{ 41,  36,  30,  29,  28,  27,  26,  25,  24,  21,  -1,  -1, -1,   -1,  -1,  -1,  -1},
	{ 49,  45,  44,  41,  39,  35,  30,  27,  24,  21,  17,  15,  8,    3,  -1,  -1,  -1},
	{ 50,  44,  41,  38,  35,  30,  27,  24,  21,  18,  15,   8,  7,    5,   4,  -1,  -1},
	{ 50,  49,  48,  47,  38,  27,  18,   9,   8,   7,   6,   5,  4,    3,  -1,  -1,  -1},
	{ 50,  49,  48,  47,  44,  41,  38,  35,  30,  27,  24,  21,  18,  15,   9,   5,   4},
	{ 49,  48,  47,  46,  45,  41,  38,  35,  30,  27,  24,  21,  18,  15,   5,   4,  -1},
	{ 50,  35,  30,  26,  25,  24,  18,  15,  9,    8,   7,  -1,  -1,  -1,  -1,  -1,  -1},
	{ 49,  48,  46,  45,  41,  38,  35,  30,  27,  24,  21,  18,  15,   8,   7,   5,   4},
	{ 49,  48,  45,  41,  38,  35,  30,  27,  24,  21,  18,  15,   8,   7,   6,   5,   4}
};

int hour = -1;
int minute = -1;
int second = -1;
int red = 124;
int green = 124;
int blue = 124;
int white = 124;
RgbwColor color;
RgbwColor color2;
int brightness = 50;
int brightness2;
bool change = false;
bool show_date = false;
int hue = 0;
int counter = 0;
int cycle_snelheid = 100;
std::string tm;

class Wordclock : public Component, public CustomAPIDevice {
    public:
        void setup() override {

            strip.Begin();
            strip.ClearTo(RgbColor(0, 0, 0));
            strip.Show();

            // Start all LED with on and default color and brightness to check if everything is working...
            for(int i = 0; i < PixelCount; i++) { strip.SetPixelColor(i, RgbColor(red, 0, 0)); strip.Show(); delay(10); }
            for(int i = 0; i < PixelCount; i++) { strip.SetPixelColor(i, RgbColor(0, green, 0)); strip.Show(); delay(10); }
            for(int i = 0; i < PixelCount; i++) { strip.SetPixelColor(i, RgbColor(0, 0, blue)); strip.Show(); delay(10); }
            for(int i = 0; i < PixelCount; i++) { strip.SetPixelColor(i, RgbwColor(0, 0, 0, white)); strip.Show(); delay(10); }
            strip.ClearTo(RgbColor(0, 0, 0));            
            strip.Show();
            register_service(&Wordclock::on_setled, "setled", {"number","red", "blue", "green", "white"});
        }

        void on_setled(int number, int red, int blue, int green, int white) {
            if (number < PixelCount || number > 0) {
                ESP_LOGD("setled", "Setting led number %d to color %i %i %i %i", number, red, green, blue, white );
                strip.SetPixelColor(number, RgbwColor(red, green, blue, white));
                strip.Show();
                }
            else { ESP_LOGE("setled", "Not a valid LED Number - out of range"); }
        }

        void loop() override {
            auto time = id(current_time).now();
            auto ldr2 = id(ldr);
            auto time_mode = id(timemodus).state;

            // auto ledlight = id(neopixelbuslight).current_values;
            auto ledlight = id(neopixelbuslight).remote_values;
            // https://www.esphome.io/api/classesphome_1_1light_1_1_light_color_values.html LightColorValues Class

            int h = time.hour;
            int m = time.minute;
            int s = time.second;
            int day = time.day_of_month;
            int month = time.month;

            //convert float 0.0 till 1.0 into int 0 till 255
            red = (int)(ledlight.get_red()*255);
            green = (int)(ledlight.get_green()*255);
            blue = (int)(ledlight.get_blue()*255);
            white = (int)(ledlight.get_white()*255);

            // RgbwColor color2 = RgbwColor(red, green, blue, white);  

            if(id(colorcycle).state == 1){
                color = HsbColor((float)hue/255, 1.0, 1.0);
                if(counter >= (int) (100 / id(ccspeed).state)){
                    hue++;
                    counter = 0;
                    change = 1;
                    // ESP_LOGD("loop", "Hue changed to %i", hue);
                }
                if(hue == 256){
                    hue = 0;
                }
                counter++;  
            }
            else{
                color2 = RgbwColor(red, green, blue, white);
                    if (color != color2) { 
                    change = 1; 
                    color = color2;
                    ESP_LOGD("loop", "Color change rgb %i %i %i", red, green, blue);
                }  
            }                      

            //check if light is on and set brightness
            if (ledlight.get_state() > 0 ) { 
                if (id(useldr).state == 1) {
                    brightness2 = (int)(ldr2.get_state()/100*255);
                }
                else {
                    brightness2 = (int)(ledlight.get_brightness()*255); 
                }

                if (brightness != brightness2) { 
                    change = 1; 
                    brightness = brightness2;
                }
                if (brightness == 0) {
                    change = 1;
                    brightness = 1;
                }
            }
            else { 
                brightness = 0;
                change = 1;
                //ESP_LOGD("loop", "fastledlight state off - b: %i rgb %i %i %i", brightness, red, green, blue); 
                // delay(500);
                }            

            strip.SetBrightness(brightness);

            //check if valid time. Blink red,green,blue until valid time is present
            if (time.is_valid() == false) {
                ESP_LOGE("loop", "Got invalid time from current_time Time: %i:%i", h, m );
                strip.SetPixelColor(0, RgbColor(255, 0, 0)); strip.Show(); delay(250);
                strip.SetPixelColor(0, RgbColor(0, 255, 0)); strip.Show(); delay(250);
                strip.SetPixelColor(0, RgbColor(0, 0, 255)); strip.Show(); delay(250);
                strip.SetPixelColor(0, RgbColor(0, 0, 0));   strip.Show();
            }
            else {

                if(s == 50 && show_date == 0 && id(showdate).state == 1){
                    show_date = 1;
                }
                else if(s== 54 && show_date == 1){
                    change = 1;
                    show_date = 0;
                }

                // only update once in a minute or on change
                if(h != hour || m != minute || change == 1 || time_mode != tm || (show_date == 1 && (s != second || change == 1))) {
                //ESP_LOGD("loop", "Using b: %i rgb %i %i %i", brightness, red, green, blue);
                    hour = h;
                    minute = m;
                    second = s;
                    change = 0;
                    tm = time_mode;

                    if(show_date == 1){
                        strip.ClearTo(RgbColor(0, 0, 0));
                        for(int i = 0; i < 17; i++) {
                            if(s == 50 || s == 51){
                                strip.SetPixelColor(cijfer_links[day / 10][i]-1, color);
                                strip.SetPixelColor(cijfer_rechts[day % 10][i]-1, color);
                            }
                            else if(s == 52 || s == 53){
                                strip.SetPixelColor(cijfer_links[month / 10][i]-1, color);
                                strip.SetPixelColor(cijfer_rechts[month % 10][i]-1, color);  
                            }
                        }
                        strip.Show();
                    }
                    else if (hour >= 0){    

                        strip.ClearTo(RgbColor(0, 0, 0));
                        int tmp_hour;
                        int tmp_minute = 0;
                        int minutessum = minute % 5; 

                        if ((tm == "Minutes-min" && minute <= 15) || (tm == "Minutes-plus" && minute <= 19)){
                            tmp_hour = hour % 12;    
                        }
                        else{
                            tmp_hour = (hour + 1) % 12;         
                        }

                        if(tm == "Minutes-plus"){
                            tmp_minute = (minute - (minute % 5)) / 5;
                            for(int i = 0; i < minutessum; i++) {   strip.SetPixelColor(leds_minutes[i]-1, color);}  
                        }
                        else if(tm == "Minutes-min"){
                            tmp_minute = (minute + 4 - ((minute + 4) % 5)) / 5;
                            if (minutessum > 0) { 
                                for(int i = minutessum-1; i < 4; i++) {   strip.SetPixelColor(leds_minutes[i]-1, color);} 
                            } 
                        }

                        for(int i = 0; i < 5; i++) {            strip.SetPixelColor(leds_time_it_is[i]-1, color); }                        
                        for(int i = 0; i < 13; i++) {           if(leds_time_minutes[tmp_minute][i] >= 0) { strip.SetPixelColor(leds_time_minutes[tmp_minute][i]-1, color); } }
                        for(int i = 0; i < 6; i++) {            if(leds_time_hours[tmp_hour][i] >= 0) { strip.SetPixelColor(leds_time_hours[tmp_hour][i]-1, color); } }
                        // for(int i = 0; i < minutessum; i++) {   strip.SetPixelColor(leds_minutes[i]-1, color);}   
                    

                        strip.Show();
                        // ESP_LOGD("loop", "Update Time: %i:%i  Brightness: %i RGBW: %i-%i-%i-%i", hour, minute, brightness, red, green, blue, white);
                        // ESP_LOGD("loop", "Using tmp_hour: %i tmp_minute: %i minutessum: %i", tmp_hour, tmp_minute, minutessum);
                    }
                }
            }
        }


};
