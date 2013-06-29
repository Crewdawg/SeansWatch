#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x2E, 0x11, 0xC5, 0x2A, 0xC6, 0x4D, 0x4C, 0xF5, 0xB1, 0xFE, 0x0E, 0xA6, 0x44, 0x17, 0x05, 0x5F }
PBL_APP_INFO(MY_UUID,
             "SeansWatch", "Canyon Networks",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer timeLayer;

static char hourText[] = "00:00";

void setTime(PblTm *t) {
  if(clock_is_24h_style())
	  string_format_time(hourText, sizeof(hourText), "%H:%M", t);
  else
	string_format_time(hourText, sizeof(hourText), "%I:%M", t);
	
  text_layer_set_text(&timeLayer, hourText);
}

void handle_min_tick(AppTaskContextRef ctx, PebbleTickEvent *t) {
	(void)ctx;
	
	PblTm time;
	get_time(&time);
	setTime(t->tick_time);	
}

void handle_sec_tick(AppTaskContextRef ctx, PebbleTickEvent *t) {
	(void)ctx;
	
	PblTm time;
	get_time(&time);
	
	int seconds = time.tm_sec;
	
	if(seconds == 0)
		setTime(t->tick_time);	
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);
	  
  text_layer_init(&timeLayer, GRect(30,30,150,50));
  text_layer_set_background_color(&timeLayer,GColorClear);
  text_layer_set_font(&timeLayer,fonts_get_system_font(FONT_KEY_GOTHAM_30_BLACK));
  text_layer_set_text_alignment(&timeLayer, GTextAlignmentCenter);
	
  layer_add_child(&window.layer, &timeLayer.layer);
	
  PblTm time;
  get_time(&time);
  setTime(&time);
}



void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
	
	.tick_info = {
	  .tick_handler = &handle_sec_tick,
	  .tick_units = SECOND_UNIT
	}
  };
  app_event_loop(params, &handlers);
}
