#include "InterruptIn.h"
#include "PinNames.h"
#include "mbed.h"

DigitalOut oled1(PA_8);
InterruptIn ibutton1(BUTTON1);
static auto sleep_time = 100ms;
static int a = 0;
Ticker toggle_led_ticker;
void led_ticker()
{
	oled1 = !oled1;
}
void pressed()
{
	a++;
	toggle_led_ticker.detach(); // открепляет таймер
	if (a > 3)
	{
		sleep_time = 100ms;
	}
	if (a > 7)
	{
		sleep_time = 500ms;
	}
	if (a > 11)
	{
		sleep_time = 1000ms;
		a = 0;
	}
	toggle_led_ticker.attach(&led_ticker, sleep_time); // прикрепляет
}
// main() runs in its own thread in the OS
int main()
{
	toggle_led_ticker.attach(&led_ticker, sleep_time);
	ibutton1.rise(&pressed);

	while (true) {
	}
}