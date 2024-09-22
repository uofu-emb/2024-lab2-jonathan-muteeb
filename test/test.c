#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "util.h"

int count = 0;
bool on = false;

/* The linker will use this instead of the FreeRTOS one */
void vTaskDelay(const uint32_t xTicksToDelay) {
    sleep_ms(xTicksToDelay);
}

/* We don't need to do any set up or tear down for the tests here */
void setUp(void) {}
void tearDown(void) {}

void test_blink_and_delay() {
    bool states[] = {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    int nstates = 11;
    for (int i = 0; i <= 3*nstates; i++) {
        TEST_ASSERT_TRUE_MESSAGE(on == states[i % nstates], "Wrong LED state");
        bool next_on = blink_and_delay(&count, on);
        TEST_ASSERT_TRUE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN) == on, "Wrong LED pin state");
        on = next_on;
    }
}

void test_invertchar_letters(void) {
    char* lower = "abcdefghijklmnopqrstuvwxyz";
    char* upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 26; i++) {
        TEST_ASSERT_EQUAL_CHAR(lower[i], invertchar(upper[i]));
        TEST_ASSERT_EQUAL_CHAR(upper[i], invertchar(lower[i]));
    }
}

void test_invertchar_symbols(void) {
    for (char c = 0;;) {
        if (c == 'a' || c == 'A') {
            c += 26;
            continue;
        }
        TEST_ASSERT_EQUAL_CHAR(c, invertchar(c));
        if (++c == 0) break;
    }
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_blink_and_delay);
    RUN_TEST(test_invertchar_letters);
    RUN_TEST(test_invertchar_symbols);
    sleep_ms(5000);
    return UNITY_END();
}
