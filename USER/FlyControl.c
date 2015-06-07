#include "include.h"


float CPitch=0;
float CRoll=0;
float CYaw=0;





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
float COS=0;
float FeedBack(float,int);
float InfMax(float);
float FeedBackRollOut = 0, FeedBackRollIn = 0, FeedBackPitchOut = 0,FeedBackPitchIn = 0, FeedBackYawIn = 0, FeedBackYawOut=0;
float M=830;
	float deltaT;
void Control()
{
	switch(CtrData)
	{
	case 0:
		;
		break;
	case 1:
		CPitch+=CtrSize;
		break;
	case 2:
		CPitch-=CtrSize;
		break;
	case 3:
		CRoll+=CtrSize;
		break;
	case 4:
		CRoll-=CtrSize;
		break;
	case 5:
		M+=CtrSize;
		if(M>=950)
		{
			while(1)
			{
				TIM2->CCR3 = 0;
				TIM2->CCR4 = 0;
				TIM1->CCR1 = 0;
				TIM1->CCR4 = 0;
			}
		}
		break;
	case 6:
		M-=CtrSize;
		break;
	case 7:
		while(1)
		{
			TIM2->CCR3 = 0;
			TIM2->CCR4 = 0;
			TIM1->CCR1 = 0;
			TIM1->CCR4 = 0;
		}
		break;
	}
	IMUupdate(GX_F,GY_F,GZ_F,AX_F,AY_F,AZ_F);
	//IMUupdate(0,0,0,AX_F,AY_F,AZ_F);
	FeedBackPitchOut=FeedBack(Pitch-CPitch,1);
	FeedBackRollOut=FeedBack(Roll-CRoll,0);
	FeedBackYawOut=FeedBack(Yaw-CYaw,2);
	
	FeedBackPitchIn=FeedBack(FeedBackPitchOut+GY_F,4);
	FeedBackRollIn=FeedBack(FeedBackRollOut+GX_F,3);
	FeedBackYawIn=FeedBack(FeedBackYawOut+GZ_F,5);
	COS=1;//pow(cos(Roll/57.3)*cos(Pitch/57.3),2);
	
	
	PWM[0]=InfMax((M-FeedBackPitchIn/2-FeedBackYawIn/4)/COS);
	PWM[1]=InfMax((M+FeedBackRollIn/2+FeedBackYawIn/4)/COS);
	PWM[2]=InfMax((M-FeedBackRollIn/2+FeedBackYawIn/4)/COS);
	PWM[3]=InfMax((M+FeedBackPitchIn/2-FeedBackYawIn/4)/COS);
	
//	PWM[0]=InfMax((M-FeedBackPitchIn)/COS);
//	PWM[1]=InfMax((M+FeedBackRollIn)/COS);
//	PWM[2]=InfMax((M-FeedBackRollIn)/COS);
//	PWM[3]=InfMax((M+FeedBackPitchIn)/COS);
	
	
//	PWM[0]=InfMax((M-FeedBackPitchOut)/COS);
//	PWM[1]=InfMax((M+FeedBackRollOut)/COS);
//	PWM[2]=InfMax((M-FeedBackRollOut)/COS);
//	PWM[3]=InfMax((M+FeedBackPitchOut)/COS);
		
	
//	PWM[0]=InfMax((M+FeedBackYawIn+FeedBackRollIn-FeedBackPitchIn)/COS);
//	PWM[1]=InfMax((M-FeedBackYawIn+FeedBackRollIn+FeedBackPitchIn)/COS);
//	PWM[2]=InfMax((M-FeedBackYawIn-FeedBackRollIn-FeedBackPitchIn)/COS);
//	PWM[3]=InfMax((M+FeedBackYawIn-FeedBackRollIn+FeedBackPitchIn)/COS);
	
	
	
//	PWM[0]=InfMax((M+FeedBackYawOut+FeedBackRollOut-FeedBackPitchOut)/COS);
//	PWM[1]=InfMax((M-FeedBackYawOut+FeedBackRollOut+FeedBackPitchOut)/COS);
//	PWM[2]=InfMax((M-FeedBackYawOut-FeedBackRollOut-FeedBackPitchOut)/COS);
//	PWM[3]=InfMax((M+FeedBackYawOut-FeedBackRollOut+FeedBackPitchOut)/COS);
	if(schedulercnt_20ms > 60)
	{
		//cuo0=0;cuo1=0;
		//printf("123564");
		//show4(PWM[0],PWM[1],PWM[2],PWM[3]);
		//send1(1.1);
		//show1(data - lastdata[i]);	
		show4(Roll,CRoll,Pitch,CPitch	);	
		schedulercnt_20ms = 0;
	}
	
	
}
float InfMax(float x)
{
	if(x>999)
		return 999;
	else
		return x;
}
float FeedBack(float data,int i){
	static float lastdata[6] = {0,0,0,0,0,0};
	static float alldata[6] = {0,0,0,0,0,0};
	float result;
	float P, D, I;
	deltaT = getDeltaT1(GetSysTime_us(),i);
	if(i<2)
	{
		if(i==0)
		{
			P = PB__roll; 
			D = DB__roll;
			I = IB__roll;
		}
		else if(i==1)
		{
			P = PB__pitch;
			D = DB__pitch;
			I = IB__pitch;
		}
		else
		{
			P = PB__yaw;
			D = DB__yaw;
			I = IB__yaw;
		}
	}
	else
	{
		if(i==3)
		{
			P = PB__roll_in; 
			D = DB__roll_in;
			I = IB__roll_in;
		}
		else if(i==4)
		{
			P = PB__pitch_in; 
			D = DB__pitch_in;
			I = IB__pitch_in;
		}
		else
		{
			P = PB__yaw_in; 
			D = DB__yaw_in;
			I = IB__yaw_in;
		}
	}
	if (data*(data - lastdata[i])>0||(data - lastdata[i]==0 && data!=0))
		alldata[i]+=data;
	result = P*data + D*(data - lastdata[i])+ I*alldata[i];
	lastdata[i] = data;		
	return result;
}
