/*
* function		: c++ thread class
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.19
*
* change author	: hammlee
* change date	: 2024.02.19
* change log	: init
*/
#ifndef CTHREADBASE_H
#define CTHREADBASE_H

#include "cpplogs/basetools/base.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <stdarg.h>

class CThreadBase : public std::thread
{
private:
    std::map<std::string, thread *> m_pThreadMap;

public:
    CThreadBase();
    static CThreadBase *GetCThreadBaseIns();
    thread *get_thread(const std::string strThreadName);
    void JoinThread(const std::string strThreadName);

public:
    template<class Fn, class... Args>
    thread *create_thread(std::string strThreadName, Fn&& fn, Args&& ... args)
    {
        if(nullptr != get_thread(strThreadName)){
            CPPLOGS_ERROR<<strThreadName<<" already exist";
            return nullptr;
        }

        thread *p = new thread(fn, args ...);
        if(!p){
            return nullptr;
        }

        m_pThreadMap.insert(strThreadName, p);
        return p;
    }

    template<class Fn, class... Args>
    thread *force_create_thread(Fn&& fn, Args&& ... args){
        thread *p = new thread(fn, args ...);
        if(!p){
            return nullptr;
        }
        return p;
    }
};



#endif // CTHREADBASE_H
