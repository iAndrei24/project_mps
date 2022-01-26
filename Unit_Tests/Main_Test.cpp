
    /* Main_Test.cpp */

#include "Main.h"
#include "Test.h"

/* Test Groups isr_main START*/

/* Testing that the function it's okay with normal inputs */
/* Result mut be the increment for the time frame */
TEST(isr_main,TimeFrameCouterIncrease)
{
    /* Initializare */

    /* Check inputs */
    Main_baseISRTime_CNT = 0u;

    /* Run Test */
    isr_main();

    /* Check Results */
    CHECK_EQUAL(1u, Main_baseISRTime_CNT);


    /* Deinitializare */

}

/* Test Groups isr_main END*/

/* Test Groups isr_init START*/

/* Testing that the function it's not okay with wrong inputs */
/* Result must be allk relevant registers beeing set */
TEST(isr_init,FUNCTION_NOK_Case)
{
    /* Initializare */
    TCCR1A = 0xA;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 0xA;
    TCCR1B = 0xA;
    TCCR1B = 0xA;
    TIMSK1 = 0xA;
    WGM12 = 0xA;
    CS12 = 0xA;
    CS10 = 0xA;
    OCIE1A = 0xA;
    TIMSK1 = 0xA;

    /* Check inputs */
    
    /* Run Test */
    isr_init();

    /* Check Results */
    CHECK_EQUAL(0, TCCR1A);
    CHECK_EQUAL(0, TCCR1B);
    CHECK_EQUAL(0, TCNT1);
    CHECK_EQUAL(15624, OCR1A);
    CHECK_EQUAL((1 << WGM12), TCCR1B);
    CHECK_EQUAL((1 << CS12) | (1 << CS10), TCCR1B);
    CHECK_EQUAL((1 << OCIE1A), TIMSK1);


    /* Deinitializare */

}

/* Test Groups CO2Detection_Init END*/