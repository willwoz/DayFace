#include "DayFace.h"
#include "pebble.h"
#include "PDUtils.h"

static Window *s_window;
static Layer *s_simple_bg_layer, *s_date_layer, *s_hands_layer;
static TextLayer *s_day_label, *s_count_label, *s_battery_label, *s_bt_label;

static BitmapLayer *s_background_layer, *s_bt_icon_layer;
static GBitmap *s_background_bitmap, *s_bt_icon_bitmap;


static GPath *s_tick_paths[NUM_CLOCK_TICKS];
static GPath *s_minute_arrow, *s_hour_arrow;
static GPath *s_triangle;

static char s_num_buffer[4], s_day_buffer[6], s_count_buffer[10], s_date_buffer[10],s_battery_buffer[4],s_bt_buffer[1];

static struct tm then;
static time_t seconds_then;

static void bg_update_proc(Layer *layer, GContext *ctx) {
  int i;
  const int x_offset = PBL_IF_ROUND_ELSE(18, 0);
  const int y_offset = PBL_IF_ROUND_ELSE(6, 0);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  
  graphics_context_set_fill_color(ctx, COLOR_FALLBACK(GColorBlueMoon,GColorWhite));
  graphics_context_set_stroke_color(ctx, COLOR_FALLBACK(GColorBlueMoon,GColorWhite));
  gpath_draw_outline(ctx, s_triangle);
  
  graphics_context_set_fill_color(ctx, GColorWhite);
  for (i = 0; i < NUM_CLOCK_TICKS_WHITE; ++i) {
    gpath_move_to(s_tick_paths[i], GPoint(x_offset, y_offset));
    gpath_draw_filled(ctx, s_tick_paths[i]);
  }
  
  graphics_context_set_fill_color(ctx, COLOR_FALLBACK(GColorRed,GColorWhite));
  for (; i < NUM_CLOCK_TICKS_RED; ++i) {
    gpath_move_to(s_tick_paths[i], GPoint(x_offset, y_offset));
    gpath_draw_filled(ctx, s_tick_paths[i]);
  }
}

static void hands_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  GPoint center = grect_center_point(&bounds);

//  const int16_t second_hand_length = PBL_IF_ROUND_ELSE((bounds.size.w / 2) - 19, bounds.size.w / 2);

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
//  int32_t second_angle = TRIG_MAX_ANGLE * t->tm_sec / 60;
//  GPoint second_hand = {
//    .x = (int16_t)(sin_lookup(second_angle) * (int32_t)second_hand_length / TRIG_MAX_RATIO) + center.x,
//    .y = (int16_t)(-cos_lookup(second_angle) * (int32_t)second_hand_length / TRIG_MAX_RATIO) + center.y,
//  };

  // second hand
//  graphics_context_set_stroke_color(ctx, GColorRed);
//  graphics_draw_line(ctx, second_hand, center);

  // minute/hour hand
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorBlack);

  gpath_rotate_to(s_minute_arrow, TRIG_MAX_ANGLE * t->tm_min / 60);
  gpath_draw_filled(ctx, s_minute_arrow);
  gpath_draw_outline(ctx, s_minute_arrow);

  gpath_rotate_to(s_hour_arrow, (TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6));
  gpath_draw_filled(ctx, s_hour_arrow);
  gpath_draw_outline(ctx, s_hour_arrow);

  // dot in the middle
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(bounds.size.w / 2 - 1, bounds.size.h / 2 - 1, 3, 3), 0, GCornerNone);
}

static void update_counter (struct tm *now_secs) {
    // Countdown update
    struct tm *now;
    time_t seconds_now;
    int difference;
    
    if (now_secs == NULL) {
        time_t t = time(NULL);
        now = localtime(&t);
    } else {
        now = now_secs;
    }
    
    seconds_now = p_mktime(now);

    // Determine the time difference
    if (seconds_now>seconds_then) {
        difference = ((((seconds_now - seconds_then) / 60) / 60) / 24);
    } else {
        difference = ((1+(((seconds_then - seconds_now) / 60) / 60) / 24));
    }

    snprintf (s_count_buffer,sizeof(s_count_buffer),"%d Days",difference);
    text_layer_set_text(s_count_label, s_count_buffer);
}
    
static void date_update_proc(Layer *layer, GContext *ctx) {
  time_t t = time(NULL);
  struct tm *now = localtime(&t);
 

  strftime(s_day_buffer, sizeof(s_day_buffer), "%a", now);
  strftime(s_num_buffer, sizeof(s_num_buffer), "%d", now);
  snprintf(s_date_buffer,sizeof(s_date_buffer),"%s %s",s_day_buffer,s_num_buffer);
  text_layer_set_text(s_day_label, s_date_buffer);
  
  update_counter(now);

  BatteryChargeState charge_state = battery_state_service_peek();
  if (charge_state.is_charging) {
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "C");
  } else {
    if (charge_state.charge_percent<25) {
      text_layer_set_text_color(s_battery_label, GColorRed);
    } else {
       text_layer_set_text_color(s_battery_label, GColorWhite);
    }
      
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "%d%%", charge_state.charge_percent);
  }
}

static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(window_get_root_layer(s_window));
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
    Tuple *yearfrom_t = dict_find(iter, KEY_YEAR);
    Tuple *monthfrom_t = dict_find(iter, KEY_MONTH);
    Tuple *dayfrom_t = dict_find(iter, KEY_DAY);
    Tuple *showseconds_t = dict_find(iter, KEY_SHOWSECONDS);
    Tuple *format_t = dict_find(iter, KEY_FORMAT);
    Tuple *showtriangle_t = dict_find(iter, KEY_SHOWTRIANGLE);

  
    APP_LOG (APP_LOG_LEVEL_INFO,"INFO: Returned from settings");
    
    if (yearfrom_t) {
        APP_LOG (APP_LOG_LEVEL_INFO,"INFO: Date Changed");
        global_config.year = yearfrom_t->value->int32;
        global_config.month = monthfrom_t->value->int8;
        global_config.day = dayfrom_t->value->int8;

        then.tm_year = global_config.year - 1900;
        then.tm_mon = global_config.month -1;
        then.tm_mday = global_config.day;
        seconds_then = p_mktime(&then);
        update_counter (NULL);
    }
  
    if (showseconds_t) {
        APP_LOG (APP_LOG_LEVEL_INFO,"INFO: Seconds CHanged");
        global_config.showseconds = showseconds_t->value->int8;
    }
  
    if (format_t) {
        APP_LOG (APP_LOG_LEVEL_INFO,"INFO: Format changed");
        global_config.countformat = format_t->value->int8;
    }
    
    if (showtriangle_t) {
        APP_LOG (APP_LOG_LEVEL_INFO,"INFO: Triangle Changed");
        global_config.showtriangle = showtriangle_t->value->int8;
    }
  
    APP_LOG (APP_LOG_LEVEL_INFO,"Configged : year - %d, month - %d, - day %d, seconds %d, format %d, triangle %d",(int)global_config.year, global_config.month, global_config.day, global_config.showseconds, global_config.countformat, global_config.showtriangle);
    
}

static void bluetooth_callback(bool connected) {
  // Show icon if disconnected
  layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), connected);

  if(!connected) {
    // Issue a vibrating alert
    vibes_double_pulse();
  }
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_simple_bg_layer = layer_create(bounds);
  layer_set_update_proc(s_simple_bg_layer, bg_update_proc);
  layer_add_child(window_layer, s_simple_bg_layer);

  s_date_layer = layer_create(bounds);
  layer_set_update_proc(s_date_layer, date_update_proc);
  layer_add_child(window_layer, s_date_layer);

  s_day_label = text_layer_create(PBL_IF_ROUND_ELSE(
    GRect(48, 40, 90, 20),
    GRect(31, 40, 90, 20)));
  text_layer_set_text_alignment(s_day_label,GTextAlignmentCenter);
  text_layer_set_text(s_day_label, s_day_buffer);
  text_layer_set_background_color(s_day_label, GColorBlack);
  text_layer_set_text_color(s_day_label, GColorWhite);
  text_layer_set_font(s_day_label, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  layer_add_child(s_date_layer, text_layer_get_layer(s_day_label));

  s_count_label = text_layer_create(PBL_IF_ROUND_ELSE(
    GRect(48, 114, 90, 20),
    GRect(31, 114, 90, 20)));
  text_layer_set_text_alignment(s_count_label,GTextAlignmentCenter);
  text_layer_set_text(s_count_label, s_count_buffer);
  text_layer_set_background_color(s_count_label, GColorBlack);
  text_layer_set_text_color(s_count_label, GColorWhite);
  text_layer_set_font(s_count_label, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  layer_add_child(s_date_layer, text_layer_get_layer(s_count_label));
   
  s_battery_label = text_layer_create(PBL_IF_ROUND_ELSE(
    GRect(28, 80, 36, 20),
    GRect(11, 80, 36, 20)));
  text_layer_set_text_alignment(s_battery_label,GTextAlignmentCenter);
  text_layer_set_text(s_battery_label, s_battery_buffer);
  text_layer_set_background_color(s_battery_label, GColorBlack);
  text_layer_set_text_color(s_battery_label, GColorWhite);
  text_layer_set_font(s_battery_label, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(s_date_layer, text_layer_get_layer(s_battery_label));
 
  // Create the Bluetooth icon GBitmap
  s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON_GLASS);

  // Create the BitmapLayer to display the GBitmap
  s_bt_icon_layer = bitmap_layer_create(PBL_IF_ROUND_ELSE(
    GRect(125, 80, 20, 20),
    GRect(108, 80, 20, 20)));
  bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bt_icon_layer));

  s_hands_layer = layer_create(bounds);
  
  bluetooth_callback(connection_service_peek_pebble_app_connection());

  layer_set_update_proc(s_hands_layer, hands_update_proc);
  layer_add_child(window_layer, s_hands_layer);
  
  // Show the correct state of the BT connection from the start
  bluetooth_callback(connection_service_peek_pebble_app_connection());
}

static void window_unload(Window *window) {
  layer_destroy(s_simple_bg_layer);
  layer_destroy(s_date_layer);

  text_layer_destroy(s_day_label);
  text_layer_destroy(s_count_label);
  text_layer_destroy(s_battery_label);
  
  gbitmap_destroy(s_bt_icon_bitmap);
  bitmap_layer_destroy(s_bt_icon_layer);

  layer_destroy(s_hands_layer);
 
}

static void init() {
    s_window = window_create();
    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(s_window, true);

    s_day_buffer[0] = '\0';
    s_num_buffer[0] = '\0';
    s_num_buffer[0] = '\0';
    s_battery_buffer[0] = '\0';
  
    if (persist_exists(KEY_STRUCTURE)) {
        persist_read_data (KEY_STRUCTURE,&global_config,sizeof(global_config));
    
        APP_LOG (APP_LOG_LEVEL_INFO,"Read : year - %d, month - %d, - day %d, seconds %d, format %d, triangle %d",(int)global_config.year, global_config.month, global_config.day, global_config.showseconds, global_config.countformat, global_config.showtriangle);
    } else {
        global_config.year = 2014;
        global_config.month = 11;
        global_config.day = 8;
        global_config.showseconds = 1;
        global_config.countformat = FMT_DAYS;
        global_config.showtriangle = 1;

        APP_LOG (APP_LOG_LEVEL_INFO,"Set : year - %d, month - %d, - day %d, seconds %d, format %d, triangle %d",(int)global_config.year, global_config.month, global_config.day, global_config.showseconds, global_config.countformat, global_config.showtriangle);
    }
    // Setup conter time from presist
    then.tm_hour = 0;
    then.tm_min = 0;
    then.tm_sec = 0;
    then.tm_year = global_config.year - 1900;
    then.tm_mon = global_config.month -1;
    then.tm_mday = global_config.day;
    seconds_then = p_mktime(&then);
  
    // init hand paths
    s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS);
    s_hour_arrow = gpath_create(&HOUR_HAND_POINTS);

    Layer *window_layer = window_get_root_layer(s_window);
    GRect bounds = layer_get_bounds(window_layer);
    GPoint center = grect_center_point(&bounds);
    gpath_move_to(s_minute_arrow, center);
    gpath_move_to(s_hour_arrow, center);

    for (int i = 0; i < NUM_CLOCK_TICKS; ++i) {
        s_tick_paths[i] = gpath_create(&ANALOG_BG_POINTS[i]);
    }

    /* init the triabgle for round or square */
    TRIANGLE_POINTS.points[0].x = bounds.size.w /2 ;
    TRIANGLE_POINTS.points[1].x = bounds.size.w / 9;
    TRIANGLE_POINTS.points[1].y = bounds.size.h * .72;
    TRIANGLE_POINTS.points[2].x = (bounds.size.w * 8) / 9;
    TRIANGLE_POINTS.points[2].y = bounds.size.h * .72;
    s_triangle = gpath_create(&TRIANGLE_POINTS);

    if (global_config.showseconds == 1) {
        tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
    } else {
        tick_timer_service_subscribe(MINUTE_UNIT, handle_second_tick);
    }
    
    // Register for Bluetooth connection updates
    connection_service_subscribe((ConnectionHandlers) {
        .pebble_app_connection_handler = bluetooth_callback
    });

    app_message_register_inbox_received(inbox_received_handler);
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {

    persist_write_data (KEY_STRUCTURE,&global_config,sizeof(global_config));

    gpath_destroy(s_minute_arrow);
    gpath_destroy(s_hour_arrow);

    for (int i = 0; i < NUM_CLOCK_TICKS; ++i) {
        gpath_destroy(s_tick_paths[i]);
    }

    gpath_destroy(s_triangle);
    tick_timer_service_unsubscribe();
    window_destroy(s_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
