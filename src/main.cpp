#include <TFT_eSPI.h>
#include <lvgl.h>
#include "mconfig.h"
#define MY_DISP_HOR_RES SCREEN_WIDTH
#define MY_DISP_VER_RES SCREEN_HEIGHT


lv_display_t *display;

/*Declare a buffer for 1/10 screen size*/
//#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */
//#define BYTE_PER_PIXEL 1 /*will be 2 for RGB565 */
//static uint8_t buf1[MY_DISP_HOR_RES * MY_DISP_VER_RES / 10 * BYTE_PER_PIXEL];
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t buf1[DRAW_BUF_SIZE / 4];

/*void my_disp_flush(lv_display_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    ili9488_flush(disp, area, color_p);
    int32_t x, y;
    /*It's a very slow but simple implementation.
     *`set_pixel` needs to be written by you to a set pixel on the screen* /
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            set_pixel(x, y, *color_p);
            color_p++;
        }
    }

    lv_display_flush_ready(disp);         /* Indicate you are ready with the flushing* /
}*/
lv_obj_t * scr1;
lv_obj_t * scr2;
void setup(){
    Serial.begin(9600);
    lv_init();
    lv_tick_set_cb(xTaskGetTickCount);
    /*display = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);  /*Initialize the display buffer.*/
    display = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, buf1, sizeof(buf1));
    //lv_display_set_flush_cb(display, my_disp_flush);
    scr1 = lv_obj_create(NULL);//lv_scr_act();//lv_screen_active();//lv_obj_create(NULL);
    static lv_style_t scrstyle;
    lv_style_init(&scrstyle);
    lv_color_t color =lv_color_hex(0x390bde);
    lv_style_set_bg_color(&scrstyle, color);
    lv_obj_add_style(scr1, &scrstyle, 0);
    //lv_obj_set_style_bg_grad_color(scr1, {255, 0, 0}, 10);
    lv_screen_load(scr1);
    Serial.println("Testing tft screen1");
    delay(5000);
    scr2 = lv_obj_create(NULL);//lv_scr_act();//lv_screen_active();//lv_obj_create(NULL);
    static lv_style_t scrstyle2;
    lv_style_init(&scrstyle2);
    lv_color_t color2 =lv_color_hex(0xe5eb34);
    lv_style_set_bg_color(&scrstyle2, color2);
    lv_obj_add_style(scr2, &scrstyle2, 0);
    //lv_obj_set_style_bg_grad_color(scr1, {255, 0, 0}, 10);
    lv_screen_load(scr2);
    Serial.println("Testing tft screen2");
}
unsigned long start = 0;
const unsigned long delayms = 5000;
bool isscr1 = false;
void loop(){
    //lv_tick_inc(5);
    //lv_timer_handler();
    lv_task_handler();  // let the GUI do its work
    lv_tick_inc(5);     // tell LVGL how much time has passed
    delay(5);
    if (millis() - start > delayms){
        lv_screen_load((isscr1)?scr1:scr2);
        start = millis();
        Serial.print("Testing tft screen");
        Serial.println((isscr1)?"1":"2");
        isscr1 = !isscr1;
    }
}