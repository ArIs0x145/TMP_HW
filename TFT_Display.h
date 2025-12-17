#ifndef TFT_DISPLAY_H
#define TFT_DISPLAY_H

#include <TFT_eSPI.h>

class TFT_Display {
private:
    TFT_eSPI tft_;
public:
    TFT_Display();

    void begin(int rotation = 1);
    void clear();
    
    void setFont(uint8_t font);
    void setTextSize(uint8_t size);
    void setFreeFont(const GFXfont* font);
    
    void showText(const String& text, int x, int y, uint16_t color = TFT_WHITE, uint8_t font = 2, uint8_t size = 1);
};

#endif