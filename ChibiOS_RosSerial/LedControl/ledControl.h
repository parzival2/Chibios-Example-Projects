#ifndef LEDS_H
#define LEDS_H

#ifdef __cplusplus
extern "C" {
#endif

#define LED_ORANGE 3
#define LED_GREEN  4
#define LED_RED    5
#define LED_BLUE   6

void led_init(void);
void led_set(int led, int brightness);

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */
