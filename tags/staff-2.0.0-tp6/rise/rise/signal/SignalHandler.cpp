/*
 *  Copyright 2009 Utkin Dmitry
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
/* 
 *  This file is part of the WSF Staff project.
 *  Please, visit http://code.google.com/p/staff for more information.
 */

#include <map>
#include <signal.h>
#include <rise/common/Log.h>
#include <rise/common/Exception.h>
#include <rise/common/ExceptionTemplate.h>
#include <rise/string/String.h>
#include "SignalHandler.h"

namespace rise
{
  class CSignalCatcher
  {
  public:
    typedef std::multimap<int, CSignalHandler*>  TSignalHandlerMap;
    typedef std::map<int, CString>               TStrSignalMap;
#ifndef WIN32
    typedef std::map<int, struct sigaction>      TSignalActionMap;
#endif

  public:
    CSignalCatcher()      
    {
#ifndef WIN32
      sigfillset(&(m_stAction.sa_mask));
#endif
    }

    ~CSignalCatcher()
    {
    }
    
    void MapSignal(int nSignal)
    {
#ifndef WIN32
      UnMapSignal(nSignal);
      m_stAction.sa_handler = SignalCatcherInternal;
      struct sigaction& rSigaction = m_mSignalAction[nSignal];
      sigaction(nSignal, &m_stAction, &rSigaction);
      rise::LogDebug() << "added signal " << GetSignalStr(nSignal) <<  " , previous action: " 
                        << rSigaction.sa_sigaction << ": handler" << rSigaction.sa_handler;
#else
      if (nSignal <= CSignalHandler::ESIGTERM)
        signal(nSignal, &SignalCatcherInternal);
#endif
    }
    
    void UnMapSignal(int nSignal)
    {
#ifndef WIN32
      TSignalActionMap::iterator itSignalAct = m_mSignalAction.find(nSignal);
      if(itSignalAct != m_mSignalAction.end())
      {
        sigaction(nSignal, &(itSignalAct->second), NULL);
        m_mSignalAction.erase(itSignalAct);
      }
#else
      signal(nSignal, NULL);
#endif
    }
  
    void RegisterSignal(int nSignal, CSignalHandler* pSignalHandler)
    {
      RISE_ASSERTP(pSignalHandler);
    
      LogDebug2() << "registering signal " << CSignalHandler::GetSignalStr(nSignal) << 
                          " on handler: " << pSignalHandler;

      if ( m_mHandlers.find(nSignal) == m_mHandlers.end() )
        MapSignal(nSignal);
      
      m_mHandlers.insert(std::make_pair(nSignal, pSignalHandler));
    }

    void UnRegisterSignal(int nSignal, CSignalHandler* pSignalHandler)
    {
      RISE_ASSERTP(pSignalHandler);

      TSignalHandlerMap::iterator iter = m_mHandlers.find(nSignal);
    
      for(; iter != m_mHandlers.end() && iter->first == nSignal; ++iter)
        if ( iter->second == pSignalHandler )
        {
          m_mHandlers.erase(iter);
          if ( m_mHandlers.find(nSignal) == m_mHandlers.end() )
            UnMapSignal(nSignal);
          return;
        }

      RISE_THROWS(CLogicNoItemException, "Signal #" + CSignalHandler::GetSignalStr(nSignal) + 
          " does not registered on handler " + ToStr(pSignalHandler));
    }
    
    void UnRegisterAll(CSignalHandler* pSignalHandler)
    {
      RISE_ASSERTP(pSignalHandler);

      for(TSignalHandlerMap::iterator iter = m_mHandlers.begin(); iter != m_mHandlers.end(); )
      {
        if ( iter->second == pSignalHandler )
        {
          int nSignal = iter->first;
          m_mHandlers.erase(iter);

          if ( m_mHandlers.find(nSignal) == m_mHandlers.end() )
            UnMapSignal(nSignal);

          iter = m_mHandlers.begin();
        } else
          ++iter;
      }
    }
    
    const CString& GetSignalStr( int nSignal ) const
    {
      if (m_tStrSignalMap.empty())
      {
#define RISE_REGISTER_SIGNAL_DESCR(SIGNAL_NAME)\
        m_tStrSignalMap[CSignalHandler::SIGNAL_NAME] = #SIGNAL_NAME;

#ifdef WIN32
      RISE_REGISTER_SIGNAL_DESCR(ESIGNONE)
      RISE_REGISTER_SIGNAL_DESCR(ESIGABRT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGABRT_COMPAT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGFPE)
      RISE_REGISTER_SIGNAL_DESCR(ESIGILL)
      RISE_REGISTER_SIGNAL_DESCR(ESIGINT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGSEGV)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTERM)
      RISE_REGISTER_SIGNAL_DESCR(ESIGHUP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGQUIT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTRAP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGBUS)
      RISE_REGISTER_SIGNAL_DESCR(ESIGKILL)
      RISE_REGISTER_SIGNAL_DESCR(ESIGUSR1)
      RISE_REGISTER_SIGNAL_DESCR(ESIGUSR2)
      RISE_REGISTER_SIGNAL_DESCR(ESIGPIPE)
      RISE_REGISTER_SIGNAL_DESCR(ESIGALRM)
      RISE_REGISTER_SIGNAL_DESCR(ESIGCHLD)
      RISE_REGISTER_SIGNAL_DESCR(ESIGCONT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGSTOP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTSTP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTTIN)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTTOU)
      RISE_REGISTER_SIGNAL_DESCR(ESIGURG)
      RISE_REGISTER_SIGNAL_DESCR(ESIGXCPU)
      RISE_REGISTER_SIGNAL_DESCR(ESIGXFSZ)
      RISE_REGISTER_SIGNAL_DESCR(ESIGVTALRM)
      RISE_REGISTER_SIGNAL_DESCR(ESIGPROF)
      RISE_REGISTER_SIGNAL_DESCR(ESIGWINCH)
      RISE_REGISTER_SIGNAL_DESCR(ESIGIO)
      RISE_REGISTER_SIGNAL_DESCR(ESIGPWR)
      RISE_REGISTER_SIGNAL_DESCR(ESIGSYS)
      RISE_REGISTER_SIGNAL_DESCR(ESIGRTMIN)
#else
      RISE_REGISTER_SIGNAL_DESCR(ESIGNONE)
      RISE_REGISTER_SIGNAL_DESCR(ESIGHUP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGINT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGQUIT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGILL)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTRAP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGABRT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGBUS)
      RISE_REGISTER_SIGNAL_DESCR(ESIGFPE)
      RISE_REGISTER_SIGNAL_DESCR(ESIGKILL)
      RISE_REGISTER_SIGNAL_DESCR(ESIGUSR1)
      RISE_REGISTER_SIGNAL_DESCR(ESIGSEGV)
      RISE_REGISTER_SIGNAL_DESCR(ESIGUSR2)
      RISE_REGISTER_SIGNAL_DESCR(ESIGPIPE)
      RISE_REGISTER_SIGNAL_DESCR(ESIGALRM)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTERM)
      RISE_REGISTER_SIGNAL_DESCR(ESIGCHLD)
      RISE_REGISTER_SIGNAL_DESCR(ESIGCONT)
      RISE_REGISTER_SIGNAL_DESCR(ESIGSTOP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTSTP)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTTIN)
      RISE_REGISTER_SIGNAL_DESCR(ESIGTTOU)
      RISE_REGISTER_SIGNAL_DESCR(ESIGURG)
      RISE_REGISTER_SIGNAL_DESCR(ESIGXCPU)
      RISE_REGISTER_SIGNAL_DESCR(ESIGXFSZ)
      RISE_REGISTER_SIGNAL_DESCR(ESIGVTALRM)
      RISE_REGISTER_SIGNAL_DESCR(ESIGPROF)
      RISE_REGISTER_SIGNAL_DESCR(ESIGWINCH)
      RISE_REGISTER_SIGNAL_DESCR(ESIGIO)
#if defined OS_Linux
      RISE_REGISTER_SIGNAL_DESCR(ESIGPWR)
#endif
      RISE_REGISTER_SIGNAL_DESCR(ESIGSYS)
#if !defined OS_Darwin
      RISE_REGISTER_SIGNAL_DESCR(ESIGRTMIN)
#endif
#endif

#undef RISE_REGISTER_SIGNAL_DESCR
      }

      TStrSignalMap::const_iterator itFnd = m_tStrSignalMap.find(nSignal);
      if (itFnd == m_tStrSignalMap.end())
      {
#if !defined OS_Darwin
        if(nSignal > CSignalHandler::ESIGRTMIN)
        {
          static std::string sSig;
          sSig = "ESIGRTMIN+" + ToStr(nSignal - CSignalHandler::ESIGRTMIN);
          return sSig;
        }
#endif
        static const CString sSigUnknown("EUNKNOWN");
        return sSigUnknown;
      }

      return itFnd->second;    
    }
    
  public:
    static CSignalCatcher& Inst()
    {
      static CSignalCatcher tInst;
      return tInst;
    }

  private:
    static void SignalCatcherInternal(int nSignal)
    {
      Inst().SignalCatcher(nSignal);
    }
    
    
    void SignalCatcher(int nSignal)
    {
      rise::LogDebug2() << "sending signal: " << GetSignalStr(nSignal) << " to handlers";
      TSignalHandlerMap::iterator itHandler = m_mHandlers.find(nSignal);
      for(; itHandler != m_mHandlers.end() && itHandler->first == nSignal; ++itHandler)
        itHandler->second->SignalHandler(nSignal);

#ifndef WIN32
      rise::LogDebug2() << "sending signal: " << GetSignalStr(nSignal) << " to previous handlers";
      TSignalActionMap::iterator itAction = m_mSignalAction.find(nSignal);
      if(itAction != m_mSignalAction.end() && itAction->second.sa_handler != NULL)
      {
        rise::LogDebug2() << "PREV HANDLER";
        itAction->second.sa_handler(nSignal);
      }
#endif
    }

  public:
    static TStrSignalMap     m_tStrSignalMap;
    TSignalHandlerMap        m_mHandlers;
#ifndef WIN32
    TSignalActionMap         m_mSignalAction;
    struct sigaction         m_stAction;
#endif
  };
  
  CSignalCatcher::TStrSignalMap CSignalCatcher::m_tStrSignalMap;

/////////////////////////////////////////////////////////////////////////////////////////
  
  CSignalHandler::~CSignalHandler()
  {
    UnRegisterAll();
  }

  void CSignalHandler::RegisterSignal(int nSignal)
  {
    CSignalCatcher::Inst().RegisterSignal(nSignal, this);
  }

  void CSignalHandler::UnRegisterSignal(int nSignal)
  {
    CSignalCatcher::Inst().UnRegisterSignal(nSignal, this);
  }

  void CSignalHandler::UnRegisterAll()
  {
    CSignalCatcher::Inst().UnRegisterAll(this);
  }  

  const CString& CSignalHandler::GetSignalStr( int nSignal )
  {
    return CSignalCatcher::Inst().GetSignalStr(nSignal);
  }

} // namespace rise