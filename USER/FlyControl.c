#include "include.h"
#include "FlyControl.h"
#include "Pwm.h"








/**** int main.c ****/
extern u8 CtrData;
extern float Pitch, Roll, Yaw;
extern float PWM[4];




float COS=0;
float FeedBack(float,int);
float InfMax(float);
float FeedBackRollOut = 0, FeedBackRollIn = 0, FeedBackPitchOut = 0,FeedBackPitchIn = 0, FeedBackYawIn = 0, FeedBackYawOut=0;
float M=830;


float deltaT;

/* data it usese,
*  CtrData 
*  data from MPU, 
*/

float CPitch=0;
float CRoll=0;
float CYaw=0;

//add by LSY 2015/6/8
//start
typedef struct
{
	float in, last_in;
	float out;
	float state, last_state;
} Ncell;

Ncell P_input[2];
Ncell Y_input[2];
Ncell R_input[2];
Ncell P_hide[3];
Ncell Y_hide[3];
Ncell R_hide[3];
Ncell P_output[1];
Ncell Y_output[1];
Ncell R_output[1];
float r, y;
float P_in_hid[2][3];
float R_in_hid[2][3];
float Y_in_hid[2][3];
float P_hid_out[3];
float Y_hid_out[3];
float R_hid_out[3];
int k = 0;
float P_err_out;
float P_err_hid[3];
float Y_err_out;
float Y_err_hid[3];
float R_err_out;
float R_err_hid[3];
float PID_Pitch_Inital_Value[3];	//wait to set initial value
float PID_Roll_Inital_Value[3];	//wait to set initial value
float PID_Yaw_Inital_Value[3];	//wait to set initial value
float yeta = 0.05;	//study rate


void InitNN()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		P_in_hid[0][i] = 1;
		R_in_hid[0][i] = 1;
		Y_in_hid[0][i] = 1;
		P_in_hid[1][i] = -1;
		R_in_hid[1][i] = -1;
		Y_in_hid[1][i] = -1;
		P_hid_out[i] = PID_Pitch_Inital_Value[i];
		Y_hid_out[i] = PID_Pitch_Inital_Value[i];
		R_hid_out[i] = PID_Pitch_Inital_Value[i];
	}
	for (i = 0; i < 3; i++)
	{
		P_hide[i].last_state = 0;
		R_hide[i].last_state = 0;
		Y_hide[i].last_state = 0;
		P_hide[i].last_in = 0;
		R_hide[i].last_in = 0;
		Y_hide[i].last_in = 0;
	}
}
//end
void Control(int first)
{
	int i, j;
	int magic_num = 80000;
	switch(CtrData)
	{
	case CTRL_EMPTY://空周期
		;
		break;
	case CTRL_PITCH_UP:
		CPitch+=CtrSize;//俯仰，机头抬升
		break;
	case CTRL_PITCH_DOWN:
		CPitch-=CtrSize;//俯仰，机头下降
		break;
	case CTRL_ROLL_LEFT:
		CRoll+=CtrSize;//横滚，偏左
		break;
	case CTRL_ROLL_RIGHT:
		CRoll-=CtrSize;//横滚，偏右
		break;
	case CTRL_UP:
		M+=CtrSize;//马力增加，抬升
		if(M>=950)
		{
			while(1)
			{
				PWM[0]=PWM[1]=PWM[2]=PWM[3]=0;
				PWMControl(PWM);
			}
		}
		break;
	case CTRL_DOWN:
		M-=CtrSize;//马力减小，下降
		break;
	case CTRL_STOP://停止
		while(1)
		{
			PWM[0]=PWM[1]=PWM[2]=PWM[3]=0;
			PWMControl(PWM);
		}
		break;
	}
	IMUupdate(GX_F,GY_F,GZ_F,AX_F,AY_F,AZ_F);
	//IMUupdate(0,0,0,AX_F,AY_F,AZ_F);
	//FeedBackPitchOut=FeedBack(Pitch-CPitch,1);
	//FeedBackRollOut=FeedBack(Roll-CRoll,0);
	//FeedBackYawOut=FeedBack(Yaw-CYaw,2);
	//add by LSY 2015/6/8
	//start
	if (first == 1)
		InitNN(); //wait---only run once***************************************************
	P_input[0].in = CPitch;
	P_input[1].in = Pitch;
	for (i = 0; i < 2; i++)
		P_input[i].state = P_input[i].in;
	for (i = 0; i < 2; i++)
		P_input[i].out = P_input[i].state;
	for (i = 0; i < 3; i++)
	{
		P_hide[i].in = 0;
		for (j = 0; j < 2; j++)
			P_hide[i].in += P_input[j].out * P_in_hid[j][i];
	}
	P_hide[0].state = P_hide[0].in;
	P_hide[1].state = P_hide[1].last_state + P_hide[1].in;
	P_hide[1].last_state = P_hide[1].state;
	P_hide[2].state = P_hide[2].in - P_hide[2].last_in;
	P_hide[2].last_in = P_hide[2].in;
	for (i = 0; i < 3; i++)
		P_hide[i].out = P_hide[i].state;
	P_output[0].in = 0;
	for (i = 0; i < 3; i++)
		P_output[0].in += P_hid_out[i] * P_hide[i].out;
	P_output[0].state = P_output[0].in;
	P_output[0].out = P_output[0].state;
	FeedBackPitchOut = P_output[0].out;
	//
	Y_input[0].in = CYaw;
	Y_input[1].in = Yaw;
	for (i = 0; i < 2; i++)
		Y_input[i].state = Y_input[i].in;
	for (i = 0; i < 2; i++)
		Y_input[i].out = Y_input[i].state;
	for (i = 0; i < 3; i++)
	{
		Y_hide[i].in = 0;
		for (j = 0; j < 2; j++)
			Y_hide[i].in += Y_input[j].out * Y_in_hid[j][i];
	}
	Y_hide[0].state = Y_hide[0].in;
	Y_hide[1].state = Y_hide[1].last_state + Y_hide[1].in;
	Y_hide[1].last_state = Y_hide[1].state;
	Y_hide[2].state = Y_hide[2].in - Y_hide[2].last_in;
	Y_hide[2].last_in = Y_hide[2].in;
	for (i = 0; i < 3; i++)
		Y_hide[i].out = Y_hide[i].state;
	Y_output[0].in = 0;
	for (i = 0; i < 3; i++)
		Y_output[0].in += Y_hid_out[i] * Y_hide[i].out;
	Y_output[0].state = Y_output[0].in;
	Y_output[0].out = Y_output[0].state;
	FeedBackYawOut = Y_output[0].out;
	//
	R_input[0].in = CRoll;
	R_input[1].in = Roll;
	for (i = 0; i < 2; i++)
		R_input[i].state = R_input[i].in;
	for (i = 0; i < 2; i++)
		R_input[i].out = R_input[i].state;
	for (i = 0; i < 3; i++)
	{
		R_hide[i].in = 0;
		for (j = 0; j < 2; j++)
			R_hide[i].in += R_input[j].out * R_in_hid[j][i];
	}
	R_hide[0].state = R_hide[0].in;
	R_hide[1].state = R_hide[1].last_state + R_hide[1].in;
	R_hide[1].last_state = R_hide[1].state;
	R_hide[2].state = R_hide[2].in - R_hide[2].last_in;
	R_hide[2].last_in = R_hide[2].in;
	for (i = 0; i < 3; i++)
		R_hide[i].out = R_hide[i].state;
	R_output[0].in = 0;
	for (i = 0; i < 3; i++)
		R_output[0].in += R_hid_out[i] * R_hide[i].out;
	R_output[0].state = R_output[0].in;
	R_output[0].out = R_output[0].state;
	FeedBackRollOut = R_output[0].out;
	//
	//end
	FeedBackPitchIn=FeedBack(FeedBackPitchOut+GY_F,4);
	FeedBackRollIn=FeedBack(FeedBackRollOut+GX_F,3);
	FeedBackYawIn=FeedBack(FeedBackYawOut+GZ_F,5);
	COS=1;//pow(cos(Roll/57.3)*cos(Pitch/57.3),2);
	
	
	PWM[0]=InfMax((M-FeedBackPitchIn/2-FeedBackYawIn/4)/COS);
	PWM[1]=InfMax((M+FeedBackRollIn/2+FeedBackYawIn/4)/COS);
	PWM[2]=InfMax((M-FeedBackRollIn/2+FeedBackYawIn/4)/COS);
	PWM[3]=InfMax((M+FeedBackPitchIn/2-FeedBackYawIn/4)/COS);
	PWMControl(PWM);
	while (magic_num-- > 0)
	{	;	}
	//add by LuShiyin 2015/6/2 
	//start
	IMUupdate(GX_F, GY_F, GZ_F, AX_F, AY_F, AZ_F);
	P_err_out = CPitch - Pitch;
	for (i = 0; i < 3; i++)
	{
		P_err_hid[i] = P_hid_out[i] * P_err_out;
		P_hid_out[i] += yeta*P_hide[i].out*P_err_out;
	}
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			P_in_hid[i][j] += yeta*P_err_hid[j] * P_input[i].out;
		}
	}
	//
	Y_err_out = CYaw - Yaw;
	for (i = 0; i < 3; i++)
	{
		Y_err_hid[i] = Y_hid_out[i] * Y_err_out;
		Y_hid_out[i] += yeta*Y_hide[i].out*Y_err_out;
	}
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			Y_in_hid[i][j] += yeta*Y_err_hid[j] * Y_input[i].out;
		}
	}
	//
	R_err_out = CRoll - Roll;
	for (i = 0; i < 3; i++)
	{
		R_err_hid[i] = R_hid_out[i] * R_err_out;
		R_hid_out[i] += yeta*R_hide[i].out*R_err_out;
	}
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			R_in_hid[i][j] += yeta*R_err_hid[j] * R_input[i].out;
		}
	}
	//end
	
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

//	if(schedulercnt_20ms > 60)
//	{
//		//cuo0=0;cuo1=0;
//		//printf("123564");
//		//show4(PWM[0],PWM[1],PWM[2],PWM[3]);
//		//send1(1.1);
//		//show1(data - lastdata[i]);	
//		show4(Roll,CRoll,Pitch,CPitch	);	
//		schedulercnt_20ms = 0;
//	}
//	
	
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
