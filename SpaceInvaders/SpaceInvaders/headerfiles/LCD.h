/*
 * LCD.h
 *
 * Created: 11-Feb-20 13:57:18
 *  Author: pmhol
 */ 


#ifndef LCD_H_
#define LCD_H_


void lcd_command(unsigned char command);
void init_lcd(void);
void lcd_writeChar( unsigned char dat );

void lcd_writeLine1 ( char text1[] );
void lcd_writeLine2 ( char text2[] );




#endif /* LCD_H_ */