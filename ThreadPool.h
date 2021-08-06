#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <pthread.h>
#include "TaskQueue.h"

template<typename T>
class ThreadPool
{
public:
	ThreadPool(int min, int max);
	~ThreadPool();

	void addTask(Task<T> t);
	
	int getBusyNum();
	
	int getLiveNum();


private:
	static void* worker(void* arg);	
	static void* manager(void* arg);
	void threadExit();

private:
	TaskQueue<T>* taskQ;
	pthread_t managerID;
	pthread_t* threadIDs;
	int minNum;   
	int maxNum;   
	int busyNum;  
	int liveNum;  
	int exitNum;  
	pthread_mutex_t mutexPool; 
	pthread_cond_t notEmpty;
	bool shutdown; 
};


#endif // !_THREADPOOL_H

