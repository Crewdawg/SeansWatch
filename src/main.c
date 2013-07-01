#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "itoa.h"


#define MY_UUID { 0x2E, 0x11, 0xC5, 0x2A, 0xC6, 0x4D, 0x4C, 0xF5, 0xB1, 0xFE, 0x0E, 0xA6, 0x44, 0x17, 0x05, 0x5F }
PBL_APP_INFO(MY_UUID,
             "SeansWatch", "Canyon Networks",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer timeLayer;
TextLayer caseLayer;
int offon = 1;

static char hourText[] = "00-00";
static char caseChar = 0;

void setTime(PblTm *t) {
//  if(clock_is_24h_style())
//	  if(offon > 0)
//	  	  string_format_time(hourText, sizeof(hourText), "%H-%M", t);
//	  else
//		  string_format_time(hourText, sizeof(hourText), "%H:%M", t);
// else
//	if(offon == 1)
//	  string_format_time(hourText, sizeof(hourText), "%I-%M", t);
//	else
//	  string_format_time(hourText, sizeof(hourText), "%I:%M", t);
	
	switch( offon ) {
    case 1:
        string_format_time(hourText, sizeof(hourText), "%H/%M", t);
    case 2:
        string_format_time(hourText, sizeof(hourText), "%H-%M", t);
	case 3:
        string_format_time(hourText, sizeof(hourText), "%H\%M", t);
	case 4:
        string_format_time(hourText, sizeof(hourText), "%H:%M", t);
	case 5:
        string_format_time(hourText, sizeof(hourText), "%H/%M", t);
	case 6:
        string_format_time(hourText, sizeof(hourText), "%H-%M", t);
    case 7:
        string_format_time(hourText, sizeof(hourText), "%H\%M", t);
	default :
        string_format_time(hourText, sizeof(hourText), "%H:%M", t);
    }
	
	//sprintf(caseChar, "%d", offon);
	caseChar = itoa(offon);
	text_layer_set_text(&caseLayer, caseChar);
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
	
	//int seconds = time.tm_sec;
	
	if(offon == 7)
		offon = 0;
	else
		offon++;
	
	//if(seconds == 0)
		setTime(t->tick_time);	
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorWhite);
	  
  text_layer_init(&timeLayer, GRect(0,50,150,50));
  text_layer_set_background_color(&timeLayer, GColorBlack);
  text_layer_set_font(&timeLayer,fonts_get_system_font(FONT_KEY_GOTHAM_30_BLACK));
  text_layer_set_text_alignment(&timeLayer, GTextAlignmentCenter);
  text_layer_set_text_color(&timeLayer, GColorWhite);
	
  text_layer_init(&caseLayer, GRect(0,100,150,50));
  text_layer_set_background_color(&caseLayer, GColorBlack);
  text_layer_set_font(&caseLayer,fonts_get_system_font(FONT_KEY_GOTHAM_18_LIGHT_SUBSET));
  text_layer_set_text_alignment(&caseLayer, GTextAlignmentCenter);
  text_layer_set_text_color(&caseLayer, GColorWhite);
	
  layer_add_child(&window.layer, &timeLayer.layer);
  layer_add_child(&window.layer, &caseLayer.layer);
	
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
