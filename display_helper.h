/**
 * @file display_helper.h
 * @brief 7.5寸三色墨水屏显示辅助函数库
 * @details 支持 GDEH075Z90 (880x528) 三色墨水屏，提供文本、图片、图标显示功能
 */

#pragma once
#include <GxEPD2_3C.h>
#include "Bitmaps3c880x528.h"

// GDEH075Z90 880x528, SSD1677 三色墨水屏
typedef GxEPD2_3C<GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2> DisplayType;
extern DisplayType display;  // 全局显示器对象

// 三色图片结构体，包含黑色和红色通道
typedef struct {
  const unsigned char* black;  // 黑色通道位图
  const unsigned char* red;    // 红色通道位图
} bitmap_pair;

/**
 * @brief 初始化显示器
 * @details 初始化墨水屏，设置旋转方向为横屏
 */
void initDisplay();

/**
 * @brief 显示预设的三色图片数组
 * @details 循环显示 bitmap_pairs 中的所有图片，每张间隔2秒
 */
void drawBitmaps();

/**
 * @brief 清空屏幕，显示全白
 */
void clearScreen();

/**
 * @brief 在指定位置显示文本
 * @param text 要显示的文本内容
 * @param x 起始 X 坐标
 * @param y 起始 Y 坐标（基线位置）
 * @param color 文本颜色，默认黑色 (GxEPD_BLACK, GxEPD_RED)
 */
void displayText(const char* text, int x, int y, uint16_t color = GxEPD_BLACK);

/**
 * @brief 水平居中显示文本
 * @param text 要显示的文本内容
 * @param y 文本的 Y 坐标（基线位置）
 * @param color 文本颜色，默认黑色
 */
void displayTextCenter(const char* text, int y, uint16_t color = GxEPD_BLACK);

/**
 * @brief 显示多行文本
 * @param lines 文本行数组
 * @param numLines 行数
 * @param startX 起始 X 坐标
 * @param startY 起始 Y 坐标（第一行基线）
 * @param lineSpacing 行间距，默认30像素
 * @param color 文本颜色，默认黑色
 */
void displayMultilineText(const char* lines[], int numLines, int startX, int startY, int lineSpacing = 30, uint16_t color = GxEPD_BLACK);

/**
 * @brief 在指定位置显示图标/小图片
 * @param iconBitmap 图标位图数据
 * @param x 起始 X 坐标
 * @param y 起始 Y 坐标
 * @param width 图标宽度
 * @param height 图标高度
 * @param color 图标颜色，默认黑色
 */
void displayIcon(const unsigned char* iconBitmap, int x, int y, int width, int height, uint16_t color = GxEPD_BLACK);

/**
 * @brief 绘制矩形边框
 * @param x 起始 X 坐标
 * @param y 起始 Y 坐标
 * @param width 矩形宽度
 * @param height 矩形高度
 * @param color 边框颜色，默认黑色
 */
void drawRect(int x, int y, int width, int height, uint16_t color = GxEPD_BLACK);

/**
 * @brief 显示单张三色图片
 * @param blackBitmap 黑色通道位图数据（880x528）
 * @param redBitmap 红色通道位图数据（880x528）
 * @details 任一参数可为 NULL，跳过对应通道显示
 */
void displayImage(const unsigned char* blackBitmap, const unsigned char* redBitmap);

/**
 * @brief 使显示器进入休眠模式
 * @details 降低功耗，适合长时间不刷新时调用
 */
void hibernateDisplay();
