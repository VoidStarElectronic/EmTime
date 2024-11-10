#include "EmTime.h"

#ifdef HTIM_US
#define __EmTick__nowUs()  (__HAL_TIM_GET_COUNTER(&HTIM_US))
#endif
extern __IO uint32_t uwTick;

void EmTick__init()
{
#ifdef HTIM_US
	HAL_TIM_Base_Start(&HTIM_US);
#endif
}
EmTick_t EmTick__nowMs()
{
	return uwTick;
//	return HAL_GetTick();
}
void EmTick__sleepMs(EmTick_t d)
{
	EmTick_t startTick = EmTick__nowMs();
	while( ( EmTick__nowMs() - startTick ) < d );
}

#ifdef HTIM_US
uint16_t EmTick__nowUs()
{
	return __EmTick__nowUs();
}
void EmTick__sleepUs(EmTick_t d)
{
	uint16_t startTick = __EmTick__nowUs();
	while( (EmTick__nowUs() - startTick ) < d );
}
#endif


void EmStopwatch(EmStopwatch_t* self)
{
	EmStopwatch__reset(self);
}
void EmStopwatch__reset(EmStopwatch_t* self)
{
	self->tick = EmTick__nowMs();
}
EmTick_t EmStopwatch__split(EmStopwatch_t* self)
{
	return (EmTick__nowMs() - self->tick);
}


void EmTimer(EmTimer_t* self)
{
	EmStopwatch(&self->sw);
	self->duration = 0;
	self->active = 0;
}
void EmTimer__reset(EmTimer_t* self, uint32_t durationMS)
{
	self->active = 1;
	self->duration = durationMS;
	EmStopwatch__reset(&self->sw);
}
uint8_t EmTimer__isActive(EmTimer_t* self)
{
	return self->active;
}
void EmTimer__stop(EmTimer_t* self)
{
	self->active = 0;
}
uint8_t EmTimer__eventListener(EmTimer_t* self, void(*eventHandler)(EmTimer_t*))
{
	if (self->active)
	{
		if (EmStopwatch__split(&self->sw) > self->duration)
		{
			self->active = 0;

			if( eventHandler != NULL)
				eventHandler(self);

			return 1;
		}
	}
	return 0;
}

