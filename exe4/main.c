#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_R = 4;
const int LED_G = 6;
volatile int flag_R = 0;
volatile int flag_G = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (gpio == BTN_PIN_R) {
    flag_R = !flag_R; 
  } else if (gpio == BTN_PIN_G) {
    flag_G = !flag_G; 
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

  while (true) {
    if(flag_R){
      gpio_put(LED_R, 1);
    } else {
      gpio_put(LED_R, 0);
    }
    if(flag_G){
      gpio_put(LED_G, 1);
    } else {
      gpio_put(LED_G, 0);
    }
  }
}
