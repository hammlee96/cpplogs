/*
* function		: thread pool
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.19
*
* change author	: hammlee
* change date	: 2024.02.19
* change log	: init
*/
#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H

#include "cpplogs/basetools/base.h"
#include "cthreadbase.h"
#include <mutex>
#include <condition_variable>
#include <functional>

using Function = void (*)(void*);
class CThreadPool : public CThreadBase
{
private:
    struct St_ThreadPoolInfo
    {
        int total_num;
        int running_num;
        int wait_num;
    }m_st_tpi;

    std::mutex m_mutex;
    bool m_isFuncThreadCreateFinished;

public:
    bool thread_pool_routine(Function func, void *args){
        m_st_tpi.running_num++;
        thread* thread_ptr = force_create_thread(func, args);

        if(!thread_ptr){
            m_st_tpi.running_num--;
            return false;
        }
        m_isFuncThreadCreateFinished = true;
        thread_ptr->join();
        m_st_tpi.running_num--;
        return true;
    }

    void thread_pool_add(Function func, void* arg)
    {
        if(m_st_tpi.total_num <= 0){
            return;
        }
        std::unique_lock<std::mutex> lock(m_mutex);
        m_st_tpi.wait_num++;
        CPPLOGS_DEBUG <<"total: "<<m_st_tpi.total_num;
        CPPLOGS_DEBUG <<"running: "<<m_st_tpi.running_num;
        CPPLOGS_DEBUG <<"wait: "<<m_st_tpi.wait_num;
        while(m_st_tpi.running_num >= m_st_tpi.total_num){
            CPPLOGS_DEBUG <<"waiting";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        m_isFuncThreadCreateFinished = false;
        thread* thread_ptr = force_create_thread(std::mem_fn(&CThreadPool::thread_pool_routine), this, func, arg);
        while(!m_isFuncThreadCreateFinished){
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        m_st_tpi.wait_num--;
    }

    inline void thread_pool_create(int nTotalNum)
    {
        memset(&m_st_tpi, 0, sizeof(m_st_tpi));
        m_st_tpi.total_num = nTotalNum;
        m_isFuncThreadCreateFinished = false;

//        create_thread(m_strManagerThread, std::mem_fn(&CThreadPool::thread_pool_manager), this);
    }

    inline void thread_pool_delete(){
        std::unique_lock<std::mutex> lock(m_mutex);
    }

    inline bool get_status()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        CPPLOGS_DEBUG <<"running thread: "<<m_st_tpi.running_num<<","<<"waitting thread: "<<m_st_tpi.wait_num;
        return m_st_tpi.running_num || m_st_tpi.wait_num;
    }
    inline int get_running_num(){
        return m_st_tpi.running_num;
    }
};

#endif // CTHREADPOOL_H
