#include "TFT_Display.h"

TFT_Display::TFT_Display() : tft_(TFT_eSPI()) {}

void TFT_Display::begin(int rotation) {
    tft_.init();
    tft_.setRotation(rotation);
    tft_.fillScreen(TFT_BLACK);
}

void TFT_Display::clear() {
    tft_.fillScreen(TFT_BLACK);
}

void TFT_Display::setFont(uint8_t font) {
    tft_.setTextFont(font);
}

void TFT_Display::setTextSize(uint8_t size) {
    tft_.setTextSize(size); 
}

void TFT_Display::setFreeFont(const GFXfont* font) {
    tft_.setFreeFont(font);
}

void TFT_Display::showText(const String& text, int x, int y, uint16_t color, uint8_t font, uint8_t size) {
    tft_.setTextColor(color);
    tft_.setTextFont(font);
    
    if (font == 1) {
        tft_.setTextSize(size);
    } else {
        tft_.setTextSize(1);
    }
    
    tft_.setCursor(x, y);
    tft_.println(text);
}