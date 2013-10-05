#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "num2words-hr.h"
#include "resource_ids.auto.h"


#define MY_UUID { 0x7B, 0xE7, 0xE4, 0x07, 0x4E, 0x75, 0x43, 0x9C, 0x8D, 0x98, 0x69, 0x96, 0x8D, 0xD4, 0x3C, 0xB9 }
PBL_APP_INFO(MY_UUID,
             "TextWatch-hr", 
             "Kost kost@linux.hr",
             1, 2, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define BUFFER_SIZE 86

static struct CommonWordsData {
  TextLayer label;
  TextLayer label2;
  Window window;
  char buffer[BUFFER_SIZE];
  char buffer2[BUFFER_SIZE];
} s_data;

static void update_time(PblTm* t) {
  time_to_2words(t->tm_hour, t->tm_min, s_data.buffer, BUFFER_SIZE, s_data.buffer2, BUFFER_SIZE);
  text_layer_set_text(&s_data.label, s_data.buffer);
  text_layer_set_text(&s_data.label2, s_data.buffer2);
}

static void handle_minute_tick(AppContextRef app_ctx, PebbleTickEvent* e) {
  update_time(e->tick_time);
}

static void handle_init(AppContextRef ctx) {
  (void) ctx;

  window_init(&s_data.window, "Clock_Window");
  const bool animated = true;
  window_stack_push(&s_data.window, animated);

  window_set_background_color(&s_data.window, GColorBlack);
  resource_init_current_app(&APP_RESOURCES);

  //GFont gotham = fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD);
  GFont fontPlain = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SANSATION_LIGHT_42));
  GFont fontBold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SANSATION_BOLD_42));

  text_layer_init(&s_data.label, GRect(0, 0, s_data.window.layer.frame.size.w, 100));
  text_layer_init(&s_data.label2, GRect(0, 37, s_data.window.layer.frame.size.w, s_data.window.layer.frame.size.h - 37));
  text_layer_set_background_color(&s_data.label, GColorClear);
  text_layer_set_background_color(&s_data.label2, GColorClear);
  text_layer_set_text_color(&s_data.label, GColorWhite);
  text_layer_set_text_color(&s_data.label2, GColorWhite);
  text_layer_set_font(&s_data.label, fontBold);
  text_layer_set_font(&s_data.label2, fontPlain);
  layer_add_child(&s_data.window.layer, &s_data.label.layer);
  layer_add_child(&s_data.window.layer, &s_data.label2.layer);

  PblTm t;
  get_time(&t);
  update_time(&t);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
