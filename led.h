#ifndef _LED_H_
#define _LED_H_

#define BLUE PB1
#define GREEN PB2
#define RED PB3

void LED_init(void);
void LED_toggle(int LED);
int simple_ramp(void);

#endif  // _LED_H_
