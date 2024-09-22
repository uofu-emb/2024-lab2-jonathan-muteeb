#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

bool blink_and_delay(int* count, bool on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    if ((*count)++ % 11) on = !on;
    vTaskDelay(500);
    return on;
}

char invertchar(char c) {
    if (c <= 'z' && c >= 'a') return c - 32;
    else if (c >= 'A' && c <= 'Z') return c + 32;
    else return c;
}