Setup
-----

1. Compile the code and load it onto the pico:
 - `cmake -B build`
 - `cd build`
 - `make -j8`
 - `picotool load src/hello_freertos.elf`
2. Reboot the pico by unplugging or running `picotool reboot`

Testing Protocol
----------------

1. To test the LED, use a stopwatch to measure the time it takes to blink 10 times
2. To test the main task, send the string "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" to the pico

Expected Behavior
-----------------

1. The LED should blink 10 times every 11 seconds, with the LED staying off for a full second after 5 blinks, and otherwise blinking once per second
2. The pico should invert the case and send the string back, giving "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"