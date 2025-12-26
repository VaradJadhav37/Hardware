#include "stm32g071xx.h"

void LCD_gpio(void);
void LCD_cmd(uint8_t cmd);
void LCD_disp(unsigned char char1);
void msdelay(uint32_t value);

int main(void)
{
    unsigned char msg1[16] = "Dept of EC";
    unsigned char msg2[16] = "SVNIT";
    uint8_t j;

    LCD_gpio();        // Initialize GPIO
    msdelay(50);

    LCD_cmd(0x38);     // 8-bit mode, 2 line, 5x7 dots
    LCD_cmd(0x01);     // Clear display
    LCD_cmd(0x0E);     // Display ON, cursor ON
    LCD_cmd(0x06);     // Auto increment cursor
    LCD_cmd(0x80);     // Force cursor to first line

    for (j = 0; j < 16; j++)
        LCD_disp(msg1[j]);

    LCD_cmd(0xC0);     // Move to second line

    for (j = 0; j < 16; j++)
        LCD_disp(msg2[j]);
}

void LCD_gpio(void)
{
    // Enable clock for Port A and Port B
    RCC->IOPENR |= 0x00000003;

    // Set PA5, PA6, PA7 as output (EN, RW, RS)
    GPIOA->MODER &= 0xFFFF03FF;
    GPIOA->MODER |= 0x00005400;
    GPIOA->OTYPER &= 0xFFFFF1FF;
    GPIOA->PUPDR &= 0xFFFF03FF;

    // Set PB0 to PB7 as output (LCD data pins)
    GPIOB->MODER &= 0xFFFF0000;
    GPIOB->MODER |= 0x00005555;
    GPIOB->OTYPER &= 0xFFFFFF00;
    GPIOB->PUPDR &= 0xFFFF0000;

    GPIOA->ODR &= 0xFFBF;   // PA6 (RW) = 0 (Write mode)
}

void LCD_cmd(uint8_t cmd)
{
    GPIOB->ODR &= 0xFF00;
    GPIOB->ODR |= cmd;          // Send command

    GPIOA->ODR &= 0xFF7F;       // RS = 0 (Command mode)
    GPIOA->ODR |= 0x0020;       // EN = 1
    msdelay(1);
    GPIOA->ODR &= 0xFFDF;       // EN = 0
    msdelay(50);
}

void LCD_disp(unsigned char char1)
{
    GPIOB->ODR &= 0xFF00;
    GPIOB->ODR |= char1;        // Send data

    GPIOA->ODR |= 0x0080;       // RS = 1 (Data mode)
    GPIOA->ODR |= 0x0020;       // EN = 1
    msdelay(1);
    GPIOA->ODR &= 0xFFDF;       // EN = 0
    msdelay(50);
}

void msdelay(uint32_t value)
{
    long int loops;
    loops = 850 * value * 4;
    while (loops--);
}
