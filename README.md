# EmTime
 Timer and Stopwatch  
 
Example 1 :
* simple stopwatch
```
#include "main.h"
#include "gpio.h"
#include "EmTime.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

    EmStopwatch_t emSw1;
    
    EmStopwatch(&emSw1);

    EmStopwatch__reset(&emSw1);

    while(1)
    {
        if(EmStopwatch__split(&emSw1) > 1000 /*Milli Second*/ ) 
        {
            // led turns off after 1 second;
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        }

        // run codes 
    }
}
```

Example 2 :
* loop stopwatch
```
#include "main.h"
#include "gpio.h"
#include "EmTime.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    EmStopwatch_t emSw1;

    EmStopwatch(&emSw1);

    EmStopwatch__reset(&emSw1);

    while(1)
    {
        if(EmStopwatch__split(&emSw1) > 500 /*Milli Second*/ ) 
        {
            EmStopwatch__reset(&emSw1);
            //toggle led every 500 ms 
            HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        }

        // run codes 
    }
}
```

Example 3 :
* simple Timer
```
#include "main.h"
#include "gpio.h"
#include "EmTime.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

    EmTimer_t emT1;

    EmTimer(&emT1);

    EmTimer__reset(&emT1, 3000);

    while(1)
    {
        if(EmTimer__eventListener(&emT1, NULL)) 
        {
            // led turns off after 3 second;
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        }

        // run codes 
    }
}
```
Example 3 :
* Multi task Timer
```
#include "main.h"
#include "gpio.h"
#include "EmTime.h"

// task 1 run every 1000 ms
void task1(EmTimer_t* t)
{
    EmTimer__reset(t, 1000);

    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

// task 2 run every 300 ms
void task2(EmTimer_t* t)
{
    EmTimer__reset(t, 300);
    
    HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

    EmTimer_t emT1;
    EmTimer_t emT2;

    EmTimer(&emT1);
    EmTimer(&emT2);

    EmTimer__reset(&emT1, 1000);
    EmTimer__reset(&emT2, 300);

    while(1)
    {
        EmTimer__eventListener(&emT1, task1);
        EmTimer__eventListener(&emT2, task2);

        // run codes 
    }
}
```
