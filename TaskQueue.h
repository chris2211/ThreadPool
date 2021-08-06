#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H


#include <queue>
#include <pthread.h>

using callback = void(*)(void* arg);

template<typename T>
struct Task {
	Task<T>() {
		func = nullptr;
		arg = nullptr;
	}

	Task<T>(callback f, void* arg) {
		this->arg = (T*)arg;
		func = f;
	}

	callback func;
	T* arg;
};

template<typename T>
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();

	void add(Task<T> t);
	void add(callback f,void *arg);

	Task<T> take();

	inline int taskNum() {
		return m_taskQ.size();
	}

private:
	pthread_mutex_t m_mutex;
	std::queue<Task<T>> m_taskQ;
};


#endif // !_TASKQUEUE_H