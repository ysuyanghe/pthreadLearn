/*
 * =====================================================================================
 *
 *       Filename:  phreadLearn.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年11月29日 20时02分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YangHe, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#define MAX 10
pthread_mutex_t mut;
pthread_t thread[2];
int number=0,i;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  *thread1
 *  Description:  
 * =====================================================================================
 */
	void
*thread1 ()
{
	printf("thread1: I'am thread 1\n");
	for(i=0;i<MAX;i++)
	{
		printf("thread1:number=%d\n",number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(2);
	}
	printf("thread1:主函数在等我完成任务吗？\n");
	pthread_exit(NULL);
}		/* -----  end of function *thread1  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  *thread2
 *  Description:  
 * =====================================================================================
 */
	void
*thread2 ()
{
	printf("thread2:I'am thread2\n");
	for(i=0;i<MAX;i++)
	{
		printf("thread2:number=%d\n",number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(3);
	}
	printf("thread2:主函数在等我完成任务吗？\n");
	pthread_exit(NULL);
}		/* -----  end of function *thread2  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pthreadCreate
 *  Description:  
 * =====================================================================================
 */
	void
pthreadCreate ( void )
{

	memset(&thread,0,sizeof(thread));
	/* 创建线程 */
	if(pthread_create(&thread[0],NULL,thread1,NULL)!=0)
		printf("创建线程1失败！\n");
	else
		printf("创建线程1成功！\n");
	if(pthread_create(&thread[1],NULL,thread2,NULL)!=0)
		printf("创建线程2失败！\n");
	else
		printf("创建线程2成功！\n");
}		/* -----  end of function pthreadCreate  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pthreadWait
 *  Description:  
 * =====================================================================================
 */
	void
pthreadWait ( )
{
	/* 等待线程结束 */
	if(thread[0]!=0)
	{
		pthread_join(thread[0],NULL);
		printf("线程1已经结束\n");
	}
	if(thread[1]!=0)
	{
		pthread_join(thread[1],NULL);
		printf("线程2已经结束\n");
	}
}		/* -----  end of function pthreadWait  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	/*用默认属性初始化互斥锁  */
	pthread_mutexattr_t *mutexattr;
	int  type;
	if(pthread_mutexattr_settype(mutexattr,PTHREAD_MUTEX_ERRORCHECK)!=0)
		printf("set error\n");
	pthread_mutex_init(&mut,NULL);
	if(pthread_mutexattr_gettype(mutexattr,&type)!=0)
		printf("get error\n");
	printf("%d\n",type);
	printf("我是主函数，我正在创建线程\n");
	pthreadCreate();
	printf("我是主函数，我正在等待线程完成任务\n");
	pthreadWait();
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
