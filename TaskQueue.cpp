#include "TaskQueue.h"

template<typename T>
TaskQueue<T>::TaskQueue()
{
    pthread_mutex_init(&m_mutex,NULL);
}

template<typename T>
TaskQueue<T>::~TaskQueue()
{
    pthread_mutex_destroy(&m_mutex);
}

template<typename T>
void TaskQueue<T>::add(Task<T> t)
{
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push(t);
    pthread_mutex_unlock(&m_mutex);
}

template<typename T>
void TaskQueue<T>::add(callback f, void* arg)
{
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push(Task<T>(f,arg));
    pthread_mutex_unlock(&m_mutex);
}

template<typename T>
Task<T> TaskQueue<T>::take()
{
    Task<T> t;
    pthread_mutex_lock(&m_mutex);
    if (m_taskQ.size() > 0) {
        t = m_taskQ.front();
        m_taskQ.pop();
    }
    pthread_mutex_unlock(&m_mutex);

    return t;
}
