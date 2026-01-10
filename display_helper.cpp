/**
 * @file display_helper.cpp
 * @brief 墨水屏显示辅助函数实现
 */

#include "display_helper.h"
#include <Arduino.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// 屏幕对象定义：CS=5(SS), DC=17, RST=16, BUSY=4
DisplayType display(GxEPD2_750c_Z90(/*CS=5*/ 5, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 19));

// 初始化显示器
void initDisplay() {
  display.init(115200);      // 初始化，波特率115200
  display.setRotation(0);    // 设置横屏显示（旋转90度）
}

// 显示预设的三色图片数组
void drawBitmaps() {
#if !defined(__AVR)
  // 定义要显示的图片对数组，可扩展添加更多图片
  const bitmap_pair bitmap_pairs[] = {
    {Bitmap3c880x528_black, Bitmap3c880x528_red}
    // ,{Bitmap2_black, Bitmap2_red}  // 可继续添加
  };
#else
  const bitmap_pair bitmap_pairs[] = {};  // AVR平台空间不足
#endif
  
  bool mirror_state = display.mirror(true);  // 启用镜像模式
  
  // 循环显示每张图片
  for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++) {
    display.setFullWindow();  // 全屏刷新
    display.firstPage();
    do {
      display.fillScreen(GxEPD_WHITE);  // 填充白色背景
      // 分别绘制黑色和红色通道
      display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, 880, 528, GxEPD_BLACK);
      display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, 880, 528, GxEPD_RED);
    } while (display.nextPage());
    delay(2000);  // 每张图片间隔2秒
  }
  
  display.mirror(mirror_state);  // 恢复镜像状态
}

// 清空屏幕，显示全白
void clearScreen() {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
  } while (display.nextPage());
}

// 在指定位置显示文本
void displayText(const char* text, int x, int y, uint16_t color) {
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);  // 设置字体
  display.setTextColor(color);          // 设置文本颜色
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);            // 设置光标位置
    display.println(text);              // 输出文本
  } while (display.nextPage());
}

// 显示单张三色图片
void displayImage(const unsigned char* blackBitmap, const unsigned char* redBitmap) {
  bool mirror_state = display.mirror(true);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    // 绘制黑色通道（如果提供）
    if (blackBitmap) {
      display.drawInvertedBitmap(0, 0, blackBitmap, 880, 528, GxEPD_BLACK);
    }
    // 绘制红色通道（如果提供）
    if (redBitmap) {
      display.drawInvertedBitmap(0, 0, redBitmap, 880, 528, GxEPD_RED);
    }
  } while (display.nextPage());
  display.mirror(mirror_state);
}

// 使显示器进入休眠模式，降低功耗
void hibernateDisplay() {
  display.hibernate();
}

// 水平居中显示文本
void displayTextCenter(const char* text, int y, uint16_t color) {
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(color);
  
  // 计算文本边界，用于居中对齐
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  int x = (display.width() - tbw) / 2;  // 计算居中 X 坐标
  
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.println(text);
  } while (display.nextPage());
}

// 显示多行文本
void displayMultilineText(const char* lines[], int numLines, int startX, int startY, int lineSpacing, uint16_t color) {
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(color);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    // 逐行显示文本
    for (int i = 0; i < numLines; i++) {
      display.setCursor(startX, startY + i * lineSpacing);
      display.println(lines[i]);
    }
  } while (display.nextPage());
}

// 在指定位置显示图标/小图片
void displayIcon(const unsigned char* iconBitmap, int x, int y, int width, int height, uint16_t color) {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(x, y, iconBitmap, width, height, color);
  } while (display.nextPage());
}

// 绘制矩形边框
void drawRect(int x, int y, int width, int height, uint16_t color) {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawRect(x, y, width, height, color);
  } while (display.nextPage());
}
