#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  flag =! flag;
}

int main() {
  const int BTN_PIN_R = 28;
  const int LED = 4;

  stdio_init_all();

  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    //printf("%d", flag);
    if(flag){
      gpio_put(LED, 1);
    } else {
      gpio_put(LED, 0);
    }
  }
}
