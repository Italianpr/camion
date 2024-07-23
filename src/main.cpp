#include "demos/lv_demos.h"
#include <Arduino.h>
#include <lvgl.h>
//#include "../.pio/libdeps/esp32doit-devkit-v1/lvgl/examples/lv_examples.h"

#define HORIZONTAL_RESOLUTION 480
#define VERTICAL_RESOLUTION 320
#define DRAW_BUFFER_SIZE HORIZONTAL_RESOLUTION * 32

// Function Declarations
void initTFT();
void configureLVGL();

// Variables
static lv_display_t *mainDisplay;
static uint8_t drawBuffer[DRAW_BUFFER_SIZE];
unsigned long lastTickMillis = 0;

void initTFT();
void configureLVGL();
void lv_example_get_started_1(void);

void setup()
{
  // Configure and start the TFT
  initTFT();

  // Configure and start LVGL
  configureLVGL();

  lv_example_get_started_1();
}

void loop()
{
  // LVGL Tick Interface
  unsigned int tickPeriod = millis()-lastTickMillis;
  lv_tick_inc(tickPeriod);
  lastTickMillis = millis();

  // LVGL Task Handler
  lv_task_handler();
}

void initTFT()
{
  // Turn on Backlight
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
}

void configureLVGL()
{
  // Start LVGL
  lv_init();

  // Configure the display driver
  mainDisplay = lv_tft_espi_create(HORIZONTAL_RESOLUTION, VERTICAL_RESOLUTION, drawBuffer, DRAW_BUFFER_SIZE);
}

#if LV_BUILD_EXAMPLES && LV_USE_LABEL

/**
 * Basic example to create a "Hello world" label
 */
void lv_example_get_started_1(void)
{
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

#endif