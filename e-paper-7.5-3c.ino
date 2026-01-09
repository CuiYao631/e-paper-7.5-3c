
#include "display_helper.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  
  initDisplay();
  Serial.println("Display initialized");
  drawBitmaps();
  Serial.println("Image displayed");
  display.hibernate();
}

void loop() {
    // 墨水屏通常不需要在 loop 中刷新
}