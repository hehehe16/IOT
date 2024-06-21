#ifndef __LCD_H
#define __LCD_H

#include "main.h"



#define LCD_FSMC_NEX         1              /* ʹ��FSMC_NE4��LCD_CS,ȡֵ��Χֻ����: 1~4 */
#define LCD_FSMC_AX          16             /* ʹ��FSMC_A10��LCD_RS,ȡֵ��Χ��: 0 ~ 25 */

#define LCD_FSMC_BCRX        FSMC_Bank1->BTCR[(LCD_FSMC_NEX - 1) * 2]       /* BCR�Ĵ���,����LCD_FSMC_NEX�Զ����� */
#define LCD_FSMC_BTRX        FSMC_Bank1->BTCR[(LCD_FSMC_NEX - 1) * 2 + 1]   /* BTR�Ĵ���,����LCD_FSMC_NEX�Զ����� */
#define LCD_FSMC_BWTRX       FSMC_Bank1E->BWTR[(LCD_FSMC_NEX - 1) * 2]      /* BWTR�Ĵ���,����LCD_FSMC_NEX�Զ����� */

#define LCD_BASE        (uint32_t)((0X60000000 + (0X4000000 * (LCD_FSMC_NEX - 1))) | (((1 << LCD_FSMC_AX) * 2) -2))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define L2R_U2D         0           /* ������,���ϵ��� */
#define L2R_D2U         1           /* ������,���µ��� */
#define R2L_U2D         2           /* ���ҵ���,���ϵ��� */
#define R2L_D2U         3           /* ���ҵ���,���µ��� */

#define U2D_L2R         4           /* ���ϵ���,������ */
#define U2D_R2L         5           /* ���ϵ���,���ҵ��� */
#define D2U_L2R         6           /* ���µ���,������ */
#define D2U_R2L         7           /* ���µ���,���ҵ��� */

#define DFT_SCAN_DIR    L2R_U2D     /* Ĭ�ϵ�ɨ�跽�� */

#define WHITE           0xFFFF      /* ��ɫ */
#define BLACK           0x0000      /* ��ɫ */
#define RED             0xF800      /* ��ɫ */
#define GREEN           0x07E0      /* ��ɫ */
#define BLUE            0x001F      /* ��ɫ */ 
#define MAGENTA         0XF81F      /* Ʒ��ɫ/�Ϻ�ɫ = BLUE + RED */
#define YELLOW          0XFFE0      /* ��ɫ = GREEN + RED */
#define CYAN            0X07FF      /* ��ɫ = GREEN + BLUE */  

/* �ǳ�����ɫ */
#define BROWN           0XBC40      /* ��ɫ */
#define BRRED           0XFC07      /* �غ�ɫ */
#define GRAY            0X8430      /* ��ɫ */ 
#define DARKBLUE        0X01CF      /* ����ɫ */
#define LIGHTBLUE       0X7D7C      /* ǳ��ɫ */ 
#define GRAYBLUE        0X5458      /* ����ɫ */ 
#define LIGHTGREEN      0X841F      /* ǳ��ɫ */  
#define LGRAY           0XC618      /* ǳ��ɫ(PANNEL),���屳��ɫ */ 
#define LGRAYBLUE       0XA651      /* ǳ����ɫ(�м����ɫ) */ 
#define LBBLUE          0X2B12      /* ǳ����ɫ(ѡ����Ŀ�ķ�ɫ) */ 

#define LCD_BL(x)   do{ x ? \
                      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, GPIO_PIN_RESET); \
                     }while(0)
typedef struct
{
    uint16_t width;     /* LCD ��� */
    uint16_t height;    /* LCD �߶� */
    uint16_t id;        /* LCD ID */
    uint8_t dir;        /* ���������������ƣ�0��������1�������� */
    uint16_t wramcmd;   /* ��ʼдgramָ�� */
    uint16_t setxcmd;   /* ����x����ָ�� */
    uint16_t setycmd;   /* ����y����ָ�� */
} _lcd_dev;

typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;
extern _lcd_dev lcddev;


void lcd_init();
void lcd_display_dir(uint8_t dir);
void lcd_set_cursor(uint16_t x, uint16_t y);
void lcd_clear(uint16_t color);
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color);
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color);
void lcd_write_ram_prepare(void);
void lcd_wr_data(volatile uint16_t data);
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);

#endif