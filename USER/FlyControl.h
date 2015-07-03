#ifndef __FLYCONTROL_H_
#define __FLYCONTROL_H_

//00.005
#include "stm32f10x.h"

#define Kk 10
#define PB__roll 1.6*Kk
#define DB__roll 43*Kk
#define IB__roll 0.004*Kk
#define PB__pitch 1.6*Kk
#define DB__pitch 43*Kk
#define IB__pitch 0.004*Kk
#define PB__yaw 1.6*Kk
#define DB__yaw 43*Kk
#define IB__yaw 0.004*Kk

#define PB__roll_in 0.2
#define DB__roll_in 1
#define IB__roll_in 0
#define PB__pitch_in 0.2
#define DB__pitch_in 1
#define IB__pitch_in 0
#define PB__yaw_in 2
#define DB__yaw_in 10
#define IB__yaw_in 0


#define CtrSize 0.02

typedef enum { 
	CTRL_EMPTY,
	CTRL_PITCH_UP,
	CTRL_PITCH_DOWN,
	CTRL_ROLL_LEFT,
	CTRL_ROLL_RIGHT,
	CTRL_UP,
	CTRL_DOWN,
	CTRL_STOP
}CTRL;


void Control(int);







#endif
