#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  //if (events == 0x4) { // fall edge
  //  printf("fall \n");
  //} else if (events == 0x8) { // rise edge
  //  printf("rise \n");
  //}
  flag = 1;
}

int main() {
  const int BTN_PIN_R = 28;

  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if(!gpio_get(BTN_PIN_R)){
      printf("fall\n");
      while (!gpio_get(BTN_PIN_R)){
      };
      printf("rise\n");
    }
    flag = 0;
  }
}
