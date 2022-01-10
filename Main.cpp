
    /* Main.cpp */

#include "Main.h"
#include "CO2Detection.h"

CO2Detection CO2_Handler(NO_TOLERATED_ERR, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);

uint32_t Main_baseISRTime_CNT = (uint32_t)ZERO;

void isr_init(void)
{
#ifdef ARDUINO_CODE    /* Code activate if arduino uC used. */

    cli();//stop interrupts

    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    sei();//allow interrupts

#endif
}

#ifdef ARDUINO_CODE /* Code activate if arduino uC used. */
ISR(TIMER1_COMPA_vect)
{
#endif

#ifndef ARDUINO_CODE /* Code activated if arduino uC not used. */
void isr_main(void)
{
#endif

    Main_baseISRTime_CNT++;

}

/* One time startup function */
void setup(void)
{
    functionState_t func_state = FUNCTION_OK;

    func_state = CO2_Handler.CO2Detection_Init();

    Main_baseISRTime_CNT = (uint32_t)ZERO;

    isr_init();
}

/* Cyclic function that runs with uC freq. */ 
void loop(void)
{
    functionState_t func_state = FUNCTION_OK;

    co2Value_t sensor_value = ZERO;

    if(ZERO == (Main_baseISRTime_CNT%SAMPLING_TIME))
    {
        /* 1. Valorile senzorilor sunt citite la intervale de <X> ms */
        func_state = CO2_Handler.CO2Detection_Main();

        /* 11. Cantitatea de CO2 este afișată pe un ecran de tip ceas */
        func_state = (functionState_t)(func_state | CO2_Handler.getCO2Value(&sensor_value));

        /* TO DO: Afisarea pe un ecran de tip ceas */

        if(FUNCTION_OK != func_state)
        {
            /* Error reaction... */ 

        }else{ /* Do nothing... */ }
    }
    else
    {
        /* Do nothing... */
    }
}

#ifndef ARDUINO_CODE /* Code activated if not used for arduino uC */
void main(void)
{
    setup();

    while(E_ON)
    {
        loop();
    }
}
#endif