#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x30, 0x2D, 0xF5, 0x0D, 0x30, 0x6C, 0x41, 0xDF, 0x8C, 0x4C, 0xCA, 0x28, 0x52, 0x12, 0xBA, 0xBD }
PBL_APP_INFO(MY_UUID,
             "Template App", "Your Company",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}