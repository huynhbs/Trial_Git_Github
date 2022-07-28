#include "Button_Driver.h"
#include "Button_Service.h"
void Buttonservice(void)
{
	ButtonServiceHandler_t Button1Service;
	Button1Service.DoubleCallback = AppDouble;
	Button1Service.SingleCallback = AppSingle;
	Button1Service.HoldCallback = AppHold;
	ButtonServiceHandler(&Button1Service);
}
