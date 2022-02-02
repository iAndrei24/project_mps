#include "Env.h"
#include "CTRL.h"
#include "SEN.h"
#include "ACT.h"
#include <conio.h>
#include <windows.h>

#ifdef TEST_UNIT_MODE
#include "Tst.h"
#endif

#ifdef TEST_VALIDATION_MODE
#include "VLD_Tst.h"
#endif

sensorValue_t DBG_SENSOR_VALUE = 12U;
uint8_t DBG_Achitation = ZERO;

bool isRunning = true;

uint8_t ENV_TimeBase_CNT = 0u;
uint8_t previous_ENV_TimeBase_CNT = 0u;

void CALLBACK isr_time_base(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
    /* Mark the previous time */
    previous_ENV_TimeBase_CNT = ENV_TimeBase_CNT;

    printf("%d\n", ENV_TimeBase_CNT);
    ENV_TimeBase_CNT++;
}

int main()
{
    /* Initialization section */
   

#ifdef TEST_UNIT_MODE
    printf(">>>>> Test mode active <<<<<\n");
    
    (void)TST_Init();

    (void)TST_Main();

#else

#ifdef TEST_VALIDATION_MODE

    printf("###################################\n");
    printf("### Start project validation... ###\n");
    printf("####################################\n\n");

    (void)VLD_InvalidRead_To_Error();
    (void)VLD_WarningRead_To_Warning();
    (void)VLD_EmergencyRead_To_Emergency();

    printf("\n\n###################################\n");
    printf("#### End project validation... ####\n");
    printf("####################################\n\n");

#else

    printf("#######################################\n");
    printf("### Start project initialization... ###\n");
    printf("#######################################\n\n");
    
    MSG msg;

    (void)SEN_Init();
    (void)ACT_Init();
    (void)CTRL_Init();
    DBG_SENSOR_VALUE = 12U;
    uint8_t timer_id = SetTimer(NULL, 0, 1000 * 3, (TIMERPROC)&isr_time_base);

    /* Cyclic activity section */
    printf("\n########################################\n");
    printf("### Start project cyclic activiry... ###\n");
    printf("########################################\n\n");
    do
    {


        /* Condition to call sistem functionality at x time sample */
        if (previous_ENV_TimeBase_CNT != ENV_TimeBase_CNT)
        {
            (void)CTRL_Main();

        }
        else { /* Do nothing */ }

        /* Needed to handle timer event list. */
        if (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
        else
        {
            KillTimer(NULL, timer_id);
            isRunning = false;
        }

        /* Needed to handle keyboard interrupt list. */
        //if (!_kbhit())
        //{
        //    printf("\nKey interrupt was hit '%c'\n", _getch());
        //}
        //else { /* Do nothing */ }

    } while (isRunning);

#endif

#endif

    return 0;
}