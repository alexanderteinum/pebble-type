#include <pebble.h>

// Screen dimensions and layout constants
#define SCREEN_HEIGHT 168
#define SMALL_FONT_HEIGHT 14
#define TIME_FONT_HEIGHT 29

// Layout adjustment constants (fine-tuning vertical positioning)
#define STEPS_Y_ADJUSTMENT 10
#define TIME_Y_ADJUSTMENT 13
#define DATE_Y_ADJUSTMENT 10

// Battery warning threshold (percentage)
/**
 * Update time, date, and step count displays
 * Called on initialization and every minute
 */
static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Update time display with 24h or 12h format based on user preference
  static char s_time_buffer[TIME_BUFFER_SIZE];
  strftime(s_time_buffer, sizeof(s_time_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  text_layer_set_text(s_time_layer, s_time_buffer);

  // Update date display (DD-MM format)
  static char s_date_buffer[DATE_BUFFER_SIZE];
  strftime(s_date_buffer, sizeof(s_date_buffer), "%d-%m", tick_time);
  text_layer_set_text(s_date_layer, s_date_buffer);

  // Update step count from Health API
  int step_count = (int)health_service_sum_today(HealthMetricStepCount);
  static char s_step_buffer[STEPS_BUFFER_SIZE];
  snprintf(s_step_buffer, sizeof(s_step_buffer), "%d", step_count);
  text_layer_set_text(s_steps_layer, s_step_buffer);
}

/**
 * Tick handler called every minute
 * 
 * @param tick_time Current time
 * @param units_changed Time units that changed
 */ * @param charge_state Current battery charge state
 */
static void handle_battery(BatteryChargeState charge_state) {
  bool is_low = charge_state.charge_percent <= BATTERY_LOW_THRESHOLD;
  layer_set_hidden(text_layer_get_layer(s_battery_layer), !is_low);
}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char s_time_buffer[8];
  strftime(s_time_buffer, sizeof(s_time_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  text_layer_set_text(s_time_layer, s_time_buffer);

  static char s_date_buffer[8];
/**
 * Initialize and layout UI elements when window loads
 * Creates a vertically balanced stack with steps, time, and date
 * 
 * @param window The main window
 */
static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Calculate vertical positions for centered layout
  // Time is centered, steps above, date below
  int time_y = (SCREEN_HEIGHT - TIME_FONT_HEIGHT) / 2;
  int steps_y = (time_y - SMALL_FONT_HEIGHT) / 2;
  int date_y = (time_y + TIME_FONT_HEIGHT) + steps_y;

  // Create and configure steps layer
  s_steps_layer = text_layer_create(GRect(0, steps_y - STEPS_Y_ADJUSTMENT, bounds.size.w, SMALL_FONT_HEIGHT + STEPS_Y_ADJUSTMENT));
  if (s_steps_layer) {
    text_layer_set_background_color(s_steps_layer, GColorClear);
    text_layer_set_text_color(s_steps_layer, GColorBlack);
    text_layer_set_font(s_steps_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_steps_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(s_steps_layer));
  }

  // Create and configure time layer (main display)
  s_time_layer = text_layer_create(GRect(0, time_y - TIME_Y_ADJUSTMENT, bounds.size.w, TIME_FONT_HEIGHT + TIME_Y_ADJUSTMENT));
  if (s_time_layer) {
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer, GColorBlack);
    text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  }

  // Create and configure date layer
  s_date_layer = text_layer_create(GRect(0, date_y - DATE_Y_ADJUSTMENT, bounds.size.w, SMALL_FONT_HEIGHT + DATE_Y_ADJUSTMENT));
/**
 * Clean up UI elements when window unloads
 * 
 * @param window The main window
 */
static void main_window_unload(Window *window) {
  if (s_steps_layer) text_layer_destroy(s_steps_layer);
  if (s_time_layer) text_layer_destroy(s_time_layer);
  if (s_date_layer) text_layer_destroy(s_date_layer);
  if (s_battery_layer) text_layer_destroy(s_battery_layer);
}

/**
 * Initialize the watchface
 * Sets up window, subscribes to services, and performs initial update
 */
static void init() {
  s_main_window = window_create();
  if (!s_main_window) {
    return;
  }

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(s_main_window, true);

  // Subscribe to time updates every minute
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Subscribe to battery state changes
  battery_state_service_subscribe(handle_battery);

  // Perform initial update
  update_time();
  handle_battery(battery_state_service_peek());
}

/**
 * Clean up on app exit
 */
static void deinit() {
  if (s_main_window) {
    window_destroy(s_main_window);
  }r(s_battery_layer, GColorRed);
  layer_add_child(window_layer, text_layer_get_layer(s_battery_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_steps_layer);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_battery_layer);
}

static void init() {
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(s_main_window, true);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(handle_battery);

  update_time();
  handle_battery(battery_state_service_peek());
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
