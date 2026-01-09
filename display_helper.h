#pragma once
#include <GxEPD2_3C.h>
#include "bitmaps/Bitmaps3c880x528.h"

// GDEH075Z90 880x528, SSD1677 三色墨水屏
typedef GxEPD2_3C<GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2> DisplayType;
extern DisplayType display;

// 三色图片结构体
typedef struct {
  const unsigned char* black;
  const unsigned char* red;
} bitmap_pair;

void initDisplay();
void drawBitmaps();
