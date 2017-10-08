#include "user_board.h"

#include "gpio.h"
#include "spi.h"

#include "user_5110.h"

const unsigned char font6x8[][6] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },// sp
{ 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },// !
{ 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },// "
{ 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },// #
{ 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },// $
{ 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },// %
{ 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },// &
{ 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },// '
{ 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },// (
{ 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },// )
{ 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },// *
{ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },// +
{ 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },// ,
{ 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },// -
{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },// .
{ 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },// /
{ 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },// 0
{ 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },// 1
{ 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },// 2
{ 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },// 3
{ 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },// 4
{ 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },// 5
{ 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },// 6
{ 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },// 7
{ 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },// 8
{ 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },// 9
{ 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },// :
{ 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },// ;
{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },// <
{ 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },// =
{ 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },// >
{ 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },// ?
{ 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },// @
{ 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },// A
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },// B
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },// C
{ 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },// D
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },// E
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },// F
{ 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },// G
{ 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },// H
{ 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },// I
{ 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },// J
{ 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },// K
{ 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },// L
{ 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },// M
{ 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },// N
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },// O
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },// P
{ 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },// Q
{ 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },// R
{ 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },// S
{ 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },// T
{ 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },// U
{ 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },// V
{ 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },// W
{ 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },// X
{ 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },// Y
{ 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },// Z
{ 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },// [
{ 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },// 55
{ 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },// ]
{ 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },// ^
{ 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },// _
{ 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },// '
{ 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },// a
{ 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },// b
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },// c
{ 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },// d
{ 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },// e
{ 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },// f
{ 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },// g
{ 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },// h
{ 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },// i
{ 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },// j
{ 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },// k
{ 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },// l
{ 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },// m
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },// n
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },// o
{ 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },// p
{ 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },// q
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },// r
{ 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },// s
{ 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },// t
{ 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },// u
{ 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },// v
{ 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },// w
{ 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },// x
{ 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },// y
{ 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },// z
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }// horiz lines
};

uint8_t spiOK = 0U;

/**
 * Initialize LCD.
 */
void LCD_Init(void) {
  LCD_Reset();
  LCD_Write_Command(0x21);
  LCD_Write_Command(0xD0);
  LCD_Write_Command(0x20);
  LCD_Write_Command(0x0C);
  LCD_Clear();
}

/**
 * Reset LCD.
 */
void LCD_Reset(void) {
  HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_RESET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_SET);
}

/**
 * Set LCD cursor position.
 * @param PosX X Position
 * @param PosY Y Position
 */
void LCD_Set_Postion(uint8_t PosX, uint8_t PosY) {
  LCD_Write_Command(0x40 | PosY);
  LCD_Write_Command(0x80 | PosX);
}

/**
 * Clear all contents on LCD.
 */
void LCD_Clear(void) {
  uint8_t t;
  uint8_t k;
  LCD_Set_Postion(0,0);
  for(t=0;t<6;t++)
  {
    for(k=0;k<84;k++)
    {
      LCD_Write_Data(0x00);
    }
  }
}

/**
 * Write a single char to LCD.
 * @param ch char to write.
 */
void LCD_Write_Char(uint8_t ch) {
  uint8_t line;
  ch -= 32;
  for (line=0; line<6; line++) LCD_Write_Data(font6x8[ch][line]);
}

/**
 * Write a string to LCD.
 * @param PosX X start point
 * @param PosY Y start point
 * @param str  string to write.
 */
void LCD_Write_String(uint8_t PosX, uint8_t PosY, char * str) {
  LCD_Set_Postion(PosX, PosY);
  while(* str) {
    LCD_Write_Char(* str);
    str ++;
  }
}

/**
 * Write LCD command to SPI
 * @param cmd command to write.
 */
void LCD_Write_Command(uint8_t cmd) {
  HAL_GPIO_WritePin(LCD_CE_PORT, LCD_CE_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit_DMA(&LCD_SPI_INTERFACE, &cmd, 0x01);
  uint32_t tickStart = HAL_GetTick();
  while(!spiOK) {
    if ((HAL_GetTick() - tickStart) > LCD_MAX_TIMEOUT_TICKS) {
      break; // Oops!
    }
  }
  HAL_GPIO_WritePin(LCD_CE_PORT, LCD_CE_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  spiOK = 0;
}

/**
 * Write LCD data to SPI
 * @param data data to write.
 */
void LCD_Write_Data(uint8_t data) {
  HAL_GPIO_WritePin(LCD_CE_PORT, LCD_CE_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  HAL_SPI_Transmit_DMA(&LCD_SPI_INTERFACE, &data, 0x01);
  uint32_t tickStart = HAL_GetTick();
  while(!spiOK) {
    if ((HAL_GetTick() - tickStart) > LCD_MAX_TIMEOUT_TICKS) {
      break; // Oops!
    }
  }
  HAL_GPIO_WritePin(LCD_CE_PORT, LCD_CE_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
  spiOK = 0;
}

/**
 * HAL SPI transfer complete callback
 * @param hspi HAL SPI handler.
 */
void LCD_Callback(void) {
  spiOK = 1;
}
