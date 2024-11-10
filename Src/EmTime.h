#ifndef EMTIME_H_
#define EMTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#ifdef HTIM_US
	#include "tim.h"
#endif

typedef uint32_t EmTick_t;

void 	 EmTick__init();
EmTick_t EmTick__nowMs();
void     EmTick__sleepMs(EmTick_t d);
#ifdef HTIM_US
uint16_t EmTick__nowUs();
void 	 EmTick__sleepUs(EmTick_t d);
#endif


typedef struct
{
	EmTick_t tick;
}EmStopwatch_t;
void 	 EmStopwatch(EmStopwatch_t* self);
void 	 EmStopwatch__reset(EmStopwatch_t* self);
EmTick_t EmStopwatch__split(EmStopwatch_t* self);


typedef struct
{
	EmStopwatch_t sw;
	EmTick_t      duration;
	uint8_t       active;
}EmTimer_t;
void 	EmTimer(EmTimer_t* self);
void	EmTimer__reset(EmTimer_t* self, uint32_t durationMS);
uint8_t EmTimer__isActive(EmTimer_t* self);
void 	EmTimer__stop(EmTimer_t* self);
uint8_t EmTimer__eventListener(EmTimer_t* self, void(*eventHandler)(EmTimer_t*));

#ifdef __cplusplus
}
#endif

#endif /* EMTIME_H_ */
