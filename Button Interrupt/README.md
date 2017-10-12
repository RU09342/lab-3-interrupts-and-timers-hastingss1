# Button Interrupt
Instead of constantly polling the button to see if anything changed, a button interrupt is used to detect only when the button is pressed which in turn allows the processor to use less power. An interrupt service routine is used to toggle the led. Button Interrupt was successfully implemented on all 5 boards.

### Multiple Buttons
For the FR5994, two buttons are used along with one button interrupt service routine to toggle leds. In the routine, there is logic in place to check which button was pressed which in turn controls a particular led.

