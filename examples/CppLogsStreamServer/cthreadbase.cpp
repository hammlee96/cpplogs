#include "cthreadbase.h"

CThreadBase::CThreadBase()
{

}

CThreadBase *CThreadBase::GetCThreadBaseIns()
{
    static CThreadBase *getCThreadBaseIns = nullptr;
    if(!getCThreadBaseIns){
        getCThreadBaseIns = new CThreadBase;
    }
    return getCThreadBaseIns;
}

std::thread *CThreadBase::get_thread(const std::string strThreadName)
{
    thread *p = nullptr;

    std::map<std::string, thread *>::iterator it = m_pThreadMap.find(strThreadName);

    if(it != m_pThreadMap.end()){
        p = it->second;
    }

    return p;
}

void CThreadBase::JoinThread(const std::string strThreadName)
{
    std::thread *currThread = get_thread(strThreadName);
    if(currThread)
    {
        currThread->join();
        delete currThread;
        currThread = nullptr;
        m_pThreadMap.erase(strThreadName);
    }
}
