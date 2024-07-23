
/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
//#define ILI9488_DRIVER

#ifdef TFTILI9341
  //#define ILI9341_2_DRIVER       // Generic driver for common displays
  #define SCREEN_WIDTH 320
  #define SCREEN_HEIGHT 240
  #define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
#else
  #define ILI9488_DRIVER     // WARNING: Do not connect ILI9488 display SDO to MISO if 
  #define SCREEN_WIDTH 480
  #define SCREEN_HEIGHT 320
  #define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
#endif
//#define TFT_WIDTH  SCREEN_WIDTH // ST7789 240 x 240 and 240 x 320
//#define TFT_HEIGHT SCREEN_HEIGHT // ST7789 240 x 320

#include <TFT_eSPI.h>
#include <lvgl.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen - Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>



// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);



// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// If logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

// Get the Touchscreen data
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = x;
    data->point.y = y;

    // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
     Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}


// Callback that is triggered when btn1 is clicked
static void event_handler_btn1(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
   
    Serial.print("clicked1");
    
  }
}
// Callback that is triggered when btn1 is clicked
static void event_handler_btn2(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    Serial.print("clicked2");
    
  }
}
// Callback that is triggered when btn1 is clicked
static void event_handler_btn3(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    Serial.print("clicked3");
    
  }
}
// Callback that is triggered when btn1 is clicked
static void event_handler_btn4(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
  
    Serial.print("clicked4");
    
  }
}




void lv_create_main_gui(void) {
    static lv_style_t screen_style;
  lv_style_init(&screen_style);

   lv_color_t screen_color = lv_color_hex(0xEBEFF3);  // Color #EBEFF3
  lv_style_set_bg_color(&screen_style, screen_color);

  lv_obj_t * screen = lv_scr_act();
  lv_obj_add_style(screen, &screen_style, 0);
   /*Init the style for the default state*/
    static lv_style_t style;
    lv_style_init(&style);
  lv_style_set_border_color(&style, lv_color_white());
  lv_style_set_border_width(&style, 5); 
  lv_style_set_radius(&style, 10); 
    

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_shadow_offset_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);
  
    /*Init the pressed style*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 30);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_pr, 5);
    lv_style_set_shadow_offset_y(&style_pr, 3);
    lv_style_set_bg_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 4));

    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_pr, &trans);


  lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_CLICKED, NULL);
   lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_align(btn1, LV_ALIGN_TOP_LEFT, 5, 5);
   lv_obj_set_height(btn1,145);
  lv_obj_set_width(btn1, 195);
      lv_obj_add_style(btn1, &style, 0);

    lv_obj_add_style(btn1, &style_pr, LV_STATE_PRESSED);
  // Create a label for the button
  lv_obj_t * btn_label = lv_label_create(btn1);
  lv_label_set_text(btn_label,"Fan 1");
  
  lv_obj_center(btn_label);

  lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_CLICKED, NULL);
  lv_obj_align(btn2, LV_ALIGN_BOTTOM_LEFT, 5, -5);
   lv_obj_set_height(btn2,143);
  lv_obj_set_width(btn2, 195);
  
  // Create a label for the button
  lv_obj_t * btn_label2 = lv_label_create(btn2);
  lv_label_set_text(btn_label2,"Fan 2");
  lv_obj_center(btn_label2);
   lv_obj_add_style(btn2, &style, 0);

    lv_obj_add_style(btn2, &style_pr, LV_STATE_PRESSED);

  lv_obj_t * btn3 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn3, event_handler_btn3, LV_EVENT_CLICKED, NULL);
     lv_obj_add_flag(btn3, LV_OBJ_FLAG_CHECKABLE);

  lv_obj_align(btn3, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);

   lv_obj_set_height(btn3,143);
  lv_obj_set_width(btn3,195);
  // Create a label for the button
  lv_obj_t * btn_label3 = lv_label_create(btn3);
  lv_label_set_text(btn_label3,"Fan 3");
  lv_obj_center(btn_label3);
   lv_obj_add_style(btn3, &style, 0);

    lv_obj_add_style(btn3, &style_pr, LV_STATE_PRESSED);

   lv_obj_t * btn4 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn4, event_handler_btn4, LV_EVENT_CLICKED, NULL);
     lv_obj_add_flag(btn4, LV_OBJ_FLAG_CHECKABLE);

  lv_obj_align(btn4, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
   lv_obj_set_height(btn4,143);
  lv_obj_set_width(btn4, 195);
  // Create a label for the button
  lv_obj_t * btn_label4 = lv_label_create(btn4);
  lv_label_set_text(btn_label4,"Fan 4");
  lv_obj_center(btn_label4);
   lv_obj_add_style(btn4, &style, 0);

    lv_obj_add_style(btn4, &style_pr, LV_STATE_PRESSED);

 

}
  
  



void setup() {
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(9600);
  Serial.println(LVGL_Arduino);
  
  // Start LVGL
  lv_init();
  // Register print function for debugging
  //lv_log_register_print_cb(log_print);

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 1: touchscreen.setRotation(1);
  touchscreen.setRotation(1);

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  
  // Initialize an LVGL input device object (Touchscreen)
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  // Set the callback function to read Touchscreen input
  lv_indev_set_read_cb(indev, touchscreen_read);

  // Function to draw the GUI (text, buttons and sliders)
  lv_create_main_gui();
}

void loop() {
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);           // let this time pass
}