/************************ (C) COPYLEFT 2010 Leafgrass *************************

* File Name		: os_cpu_c.c 
* Author		: Librae
* Date			: 06/10/2010
* Description	: task stack init    hook functions
*

******************************************************************************/

#ifndef	__OS_CPU_H__
#define	__OS_CPU_H__

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/******************************************************************************
*                    data type independent of complier
******************************************************************************/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;			/* Unsigned  8 bit quantity       */
typedef signed   char  INT8S;			/* Signed    8 bit quantity       */
typedef unsigned short INT16U;			/* Unsigned 16 bit quantity       */
typedef signed   short INT16S;			/* Signed   16 bit quantity       */
typedef unsigned int   INT32U;			/* Unsigned 32 bit quantity       */
typedef signed   int   INT32S;			/* Signed   32 bit quantity       */
typedef float          FP32;			/* Single precision floating point*/
typedef double         FP64;			/* Double precision floating point*/

//STM32 is 32-bit 
typedef unsigned int   OS_STK;			/* Each stack entry is 32-bit wide*/
typedef unsigned int   OS_CPU_SR;		/* Define size of CPU status register*/
/* 
*******************************************************************************
*                             Cortex M3
*                     Critical Section Management
*******************************************************************************
*/


/*
*******************************************************************************
*                          ARM Miscellaneous
*******************************************************************************
*/


#define  OS_STK_GROWTH        1      /* Stack grows from HIGH to LOW memory on ARM    */
//macro : task switch, impelemented by asmmble
#define  OS_TASK_SW()         OSCtxSw()

/*
*******************************************************************************
*                               PROTOTYPES
*                           (see OS_CPU_A.ASM)
*******************************************************************************
*********************************************************************************************************
*                                              Cortex-M3
*                                      Critical Section Management
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*             NOT IMPLEMENTED
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*             NOT IMPLEMENTED
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/
//OS_CRITICAL_METHOD = 1 :直接使用处理器的开关中断指令来实现宏 
//OS_CRITICAL_METHOD = 2 :利用堆栈保存和恢复CPU的状态 
//OS_CRITICAL_METHOD = 3 :利用编译器扩展功能获得程序状态字，保存在局部变量cpu_sr

#define  OS_CRITICAL_METHOD   3	 	//进入临界段的方法

#if OS_CRITICAL_METHOD == 3
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}
#endif

void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);

void       OSPendSV(void);

#if OS_CRITICAL_METHOD == 3u                      /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif
OS_CPU_EXT INT32U OSInterrputSum;

#endif

/************************ (C) COPYLEFT 2010 Leafgrass ************************/
