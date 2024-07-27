#include <TFT_eSPI.h>
#include <lvgl.h>
#include "mconfig.h"
#define MY_DISP_HOR_RES SCREEN_WIDTH
#define MY_DISP_VER_RES SCREEN_HEIGHT


lv_display_t *display;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t buf1[DRAW_BUF_SIZE / 4];

void setup(){
    Serial.begin(9600);
    lv_init();
    lv_tick_set_cb(xTaskGetTickCount);
    
    display = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, buf1, sizeof(buf1));
    
    static lv_style_t scrstyle;
    lv_style_init(&scrstyle);
    lv_color_t color =lv_color_hex(0x003a57);
    lv_style_set_bg_color(&scrstyle, color);
    lv_obj_t *scr1 = lv_scr_act();
    lv_obj_add_style(scr1, &scrstyle, LV_PART_MAIN);
    
    /*Change the active screen's background color*/
    //lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    // lv_obj_t * label = lv_label_create(lv_screen_active());
    // lv_label_set_text(label, "Hello world");
    // lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    static lv_style_t lbstyle;
    lv_style_init(&lbstyle);
    lv_style_set_bg_color(&lbstyle, lv_color_hex(0xff0000));

    lv_obj_t *label = lv_label_create(scr1);
    lv_label_set_text(label, "Hello  word");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(label, &lbstyle, LV_PART_MAIN);
    Serial.println("Testing tft screen1");
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
    // if (millis() - start > delayms){
    //     lv_screen_load((isscr1)?scr1:scr2);
    //     start = millis();
    //     Serial.print("Testing tft screen");
    //     Serial.println((isscr1)?"1":"2");
    //     isscr1 = !isscr1;
    // }
}