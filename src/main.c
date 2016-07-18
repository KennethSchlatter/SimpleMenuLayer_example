#include <pebble.h>

#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 3
#define NUM_SECOND_MENU_ITEMS 1

// Define a Window
static Window *window;

// Define a Simple Menu Layer
static SimpleMenuLayer *menu_layer;
// Create an array that contains the names of the sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
// Create an array that contains the items in the first section
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];
// Create an array that contains the items in the second section
static SimpleMenuItem second_menu_items[NUM_SECOND_MENU_ITEMS];

// Create a boolean for the first section that we will switch 'on' and 'off'
static bool first_special_flag = false;
// Create another boolean for the second section
static bool second_special_flag = false;
// Create a variable to count how many times we've selected an item from the first section
static int first_hit_count = 0;
// Create a variable to count how many times we've selected an item from the second section
static int second_hit_count = 0;

// Create a simple callback for when an item is selected
static void first_menu_select_callback(int index, void *ctx) {
  // Figure out which item from the first menu is selected and change its subtitle
  first_menu_items[index].subtitle = "You've hit select here!";
  // Mark the layer dirty, so it is very clear that this item has been selected
  layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// Create a callback for the first section that does special stuff when the item is selected
static void first_special_select_callback(int index, void *ctx) {
  // Toggle the boolean we create earlier
  first_special_flag = !first_special_flag;
  // Firgure out which item is selected from the second menu. There's only one possibility now, but you could add more
  SimpleMenuItem *menu_item = &first_menu_items[index];
  
  // An If/Else statement that changes the subtitle depending on the boolean
  if (first_special_flag) {
    // If the boolean "special_flag", is true, set the subtitle to "Okay, it's not so special."
    menu_item->subtitle = "Okay, maybe something is here.";
  } else {
    // If the boolean "special_flag", is false when, set the subtitle to "Well, maybe a little."
    menu_item->subtitle = "Well... maybe.";
  }
  
  // If this item has ben clicked 5 times, do this code
  if (++first_hit_count > 5) {
    // Change the item title to "VERY Special Item"
    menu_item->title = "Much Special Item";
  }
  
  // Make it clear that this item has been selected
  layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// Create a callback for the second section that does special stuff when the item is selected
static void second_special_select_callback(int index, void *ctx) {
  // Toggle the boolean we create earlier
  second_special_flag = !second_special_flag;
  // Firgure out which item is selected from the second menu. There's only one possibility now, but you could add more
  SimpleMenuItem *menu_item = &second_menu_items[index];
  
  // An If/Else statement that changes the subtitle depending on the boolean
  if (second_special_flag) {
    // If the boolean "special_flag", is true, set the subtitle to "Okay, it's not so special."
    menu_item->subtitle = "Okay, it's not so special.";
  } else {
    // If the boolean "special_flag", is false when, set the subtitle to "Well, maybe a little."
    menu_item->subtitle = "Well, maybe a little.";
  }
  
  // If this item has ben clicked 5 times, do this code
  if (++second_hit_count > 5) {
    // Change the item title to "VERY Special Item"
    menu_item->title = "VERY Special Item";
  }
  
  // Make it clear that this item has been selected
  layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// Load the Window
static void window_load(Window *window) {  
  // This let's us change the order later, if we want to
  int num_a_items = 0;
  
  // Add an item to the first section
  first_menu_items[num_a_items++] = (SimpleMenuItem) {
    // Call the item "First Item"
    .title = "First Item",
    // When this item is selected, the code in the first_menu_select_callback will be called
    .callback = first_menu_select_callback,
  };
  
  // Add another item to the first section
    first_menu_items[num_a_items++] = (SimpleMenuItem) {
    // Call the item "Option Two"
    .title = "Option Two",
    // Give this item a subtitle, "Look! A Subtitle!"
    .subtitle = "Look! A Subtitle!",
    // When this item is selected, the code in the first_menu_select_callback will be called
    .callback = first_menu_select_callback,
  };
  
  // Add a third item to the first section
    first_menu_items[num_a_items++] = (SimpleMenuItem) {
    // Call the item "Three!"
    .title = "Three!",
    // Make the subtitle "I have a card!"
    .subtitle = "Nothing Special Here.",
    // When this item is selected, the code in the first_special_select_callback will be called
    .callback = first_special_select_callback,
  };
  
  // Add an item to the second section
    second_menu_items[0] = (SimpleMenuItem) {
    // Call the item "First Item"
    .title = "Special Item",
    // When this item is selected, the code in the second_special_select_callback will be called
    .callback = second_special_select_callback,
  };
  
  // Create the first section
    menu_sections[0] = (SimpleMenuSection) {
    // Define the number of items in this section
    .num_items = NUM_FIRST_MENU_ITEMS,
    // Define which items are in this section
    .items = first_menu_items,
  };
  
  // Create the second section
    menu_sections[1] = (SimpleMenuSection) {
    // Name this section "Another Section"
    .title = "Another Section",
    // Define the number of items in this section
    .num_items = NUM_SECOND_MENU_ITEMS,
    // Define which items are in this section
    .items = second_menu_items,
  };
  
  // Get the bounds (dimensions) of the screen
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  
  // Create the Simple Menu Layer using the inforation above
  menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);
  
  // Add the menu to the window
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(menu_layer));
}

// Unload the Window
static void window_unload(Window *window) {
  simple_menu_layer_destroy(menu_layer);
}

// Initialize the app
static void init() {
  // Create a Window
  window = window_create();
  
  // Set handlers to load and unload the Window
  window_set_window_handlers(window, (WindowHandlers) {
    // Create the load handler
    .load = window_load,
    // Create the unload handler
    .unload = window_unload
  });
  
  // Push the Window so it shows up
  window_stack_push(window, true);
}

// Deinitialize the app
static void deinit() {
  // Destroy the window
  window_destroy(window);
}

// Run everything in the right order
int main(void) {
  // Run the Initializing code
  init();
  // Run the App Event Loop (window_load and window_unload) code
  app_event_loop();
  // Run the Deinitializing code
  deinit();
}