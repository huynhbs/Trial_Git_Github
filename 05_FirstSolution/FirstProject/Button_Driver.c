#include "Button_Driver.h"

typedef enum {
    BUTTON_SINGLE_MODE = 0,
    BUTTON_DOUBLE_MODE,
    BUTTON_HOLD_MODE
} buttoncurrentmode;

int ButtonMode = 0x00;
int ModeProcess = 0x00;

void ButtonModeProcess(ButtonLogicHandler_t* cxt2)
{

    if (ModeProcess == BUTTON_SINGLE_MODE) ButtonMode = BUTTON_SINGLE_MODE;
    if (ModeProcess == BUTTON_DOUBLE_MODE) ButtonMode = BUTTON_DOUBLE_MODE;
    if (ModeProcess == BUTTON_HOLD_MODE) ButtonMode = BUTTON_HOLD_MODE;
}

void Callback_GPIO_Low(void)
{
    printf("detect button is pusshing and timming time to detect single/double/holding");

}

void Callback_GPIO_Low(void)
{
    printf("detect button is released and timming time to detect single/double/holding");

}

void ButtonServiceHandler(ButtonServiceHandler_t* cxt)
{
    switch (ButtonMode)
    {
    case BUTTON_SINGLE_MODE:

        if (cxt->SingleCallback) /*verify except void pointer*/
        {
            cxt->SingleCallback();/* call fuction off LED*/
        }
        break;

    case BUTTON_DOUBLE_MODE:
        if (cxt->DoubleCallback)
        {
            cxt->DoubleCallback();
        }
        break;

    case BUTTON_HOLD_MODE:
        if (cxt->HoldCallback)
        {
            cxt->HoldCallback();
        }
        break;

    default:
        break;
    }
}