#include <pebble.h>

static Window    *s_main_window;
static TextLayer *s_steps_layer;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_battery_layer;

static void handle_battery(BatteryChargeState charge_state)
{
  bool is_low = charge_state.charge_percent <= 20;
  layer_set_hidden(text_layer_get_layer(s_battery_layer), !is_low);
}

static void update_time()
{
  time_t     temp      = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char s_time_buffer[8];
  strftime(s_time_buffer, sizeof(s_time_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M",
           tick_time);
  text_layer_set_text(s_time_layer, s_time_buffer);

  static char s_date_buffer[8];
  strftime(s_date_buffer, sizeof(s_date_buffer), "%d-%m", tick_time);
  text_layer_set_text(s_date_layer, s_date_buffer);

  int         step_count = (int) health_service_sum_today(HealthMetricStepCount);
  static char s_step_buffer[8];
  snprintf(s_step_buffer, sizeof(s_step_buffer), "%d", step_count);
  text_layer_set_text(s_steps_layer, s_step_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
  update_time();
}

static void main_window_load(Window *window)
{
  Layer *window_layer = window_get_root_layer(window);
  GRect  bounds       = layer_get_bounds(window_layer);

  int screen_h     = 168;
  int small_font_h = 14;
  int time_font_h  = 29;

  int time_y  = (screen_h - time_font_h) / 2;
  int steps_y = (time_y - small_font_h) / 2;
  int date_y  = (time_y + time_font_h) + steps_y;

  s_steps_layer = text_layer_create(GRect(0, steps_y - 10, bounds.size.w, small_font_h + 10));
  text_layer_set_background_color(s_steps_layer, GColorClear);
  text_layer_set_text_color(s_steps_layer, GColorBlack);
  text_layer_set_font(s_steps_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_steps_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_steps_layer));

  s_time_layer = text_layer_create(GRect(0, time_y - 13, bounds.size.w, time_font_h + 13));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

  s_date_layer = text_layer_create(GRect(0, date_y - 10, bounds.size.w, small_font_h + 10));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));

  s_battery_layer = text_layer_create(GRect(0, 0, bounds.size.w, 1));
  text_layer_set_background_color(s_battery_layer, GColorRed);
  layer_add_child(window_layer, text_layer_get_layer(s_battery_layer));
}

static void main_window_unload(Window *window)
{
  text_layer_destroy(s_steps_layer);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_battery_layer);
}

static void init()
{
  s_main_window = window_create();

  window_set_window_handlers(
      s_main_window, (WindowHandlers) {.load = main_window_load, .unload = main_window_unload});

  window_stack_push(s_main_window, true);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(handle_battery);

  update_time();
  handle_battery(battery_state_service_peek());
}

static void deinit()
{
  window_destroy(s_main_window);
}

int main(void)
{
  init();
  app_event_loop();
  deinit();
}
