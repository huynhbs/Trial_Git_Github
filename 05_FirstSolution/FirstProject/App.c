
#include <stdio.h>
#include <math.h>
#include <stdbool.h >
#include "Button_Driver.h"
#include "Button_Service.h"

int main() {
	while (1)
	{
		Buttonservice();
		delay_ms(10);
	}

}

void AppSingle(void)
{
	printf("AppSingle is performing.\n");
}

void AppDouble(void)
{
	printf("AppDouble is performing.\n");
}

void AppHold(void)
{
	printf("AppHold is performing.\n");
}
/*compiler of VS have form: cl source_code.c*/


