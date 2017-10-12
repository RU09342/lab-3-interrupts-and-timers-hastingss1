# TIMER A Blink
Sean Hastings: Rather than using a loop, timers are used to control the speed of two blinking leds. Two TimerA interrupt service routines are implemented to independently toggle the two leds. In order to visibly tell that the timers are controlling the leds at different rates, Timer A0 is set to be twice as fast as Timer A1.

Implementation Note: The FR2311 must use Timer_B instead of Timer_A.

### Extra Work

#### Low Power Timers
Depending on the chosen low power mode, different parts of the processor can be turned off in order to reduce overall power. These 5 boards all use LPM3 to reduce power.
