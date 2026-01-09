#include "display_helper.h"
#include <Arduino.h>

// 屏幕对象定义
DisplayType display(GxEPD2_750c_Z90(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

void initDisplay() {
  display.init(115200);
  display.setRotation(1);
}

void drawBitmaps() {
#if !defined(__AVR)
  const bitmap_pair bitmap_pairs[] = {
    {Bitmap_example_black, Bitmap_example_red}
    // ,{Bitmap2_black, Bitmap2_red}
  };
#else
  const bitmap_pair bitmap_pairs[] = {};
#endif
  bool mirror_state = display.mirror(true);
  for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++) {
    display.setFullWindow();
    display.firstPage();
    do {
      display.fillScreen(GxEPD_WHITE);
      display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, 880, 528, GxEPD_BLACK);
      display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, 880, 528, GxEPD_RED);
    } while (display.nextPage());
    delay(2000);
  }
  display.mirror(mirror_state);
}
