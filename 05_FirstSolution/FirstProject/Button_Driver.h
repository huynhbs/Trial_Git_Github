
#ifndef _BUTTONDRIVER_H_
#define _BUTTONDRIVER_H_

#include <stdint.h>

    typedef void (*ButtonInputHighHandler)(void);
    typedef void (*ButtonInputLowHandler)(void);

    typedef struct {
        ButtonInputHighHandler HighCallback;
        ButtonInputLowHandler LowCallback;
        uint8_t state;
    } ButtonLogicHandler_t;

    typedef void (*ButtonSingleHandler)(void);
    typedef void (*ButtonDoubleHandler)(void);
    typedef void (*ButtonHoldHandler)(void);

    typedef struct {
        ButtonSingleHandler SingleCallback;
        ButtonDoubleHandler DoubleCallback;
        ButtonHoldHandler  HoldCallback;
        uint8_t state;
    } ButtonServiceHandler_t;


    void ButtonModeProcess(ButtonLogicHandler_t* cxt2);
    void  ButtonServiceHandler(ButtonServiceHandler_t* cxt);

#endif /* _BUTTONDRIVER_H_ */
