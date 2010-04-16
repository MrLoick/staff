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

#ifndef _FILEUNPACKER_H_
#define _FILEUNPACKER_H_

#include <string>
#include <rise/threading/Thread.h>
#include <rise/process/Process.h>

namespace webapp
{
  namespace admin
  {
    //!  File unpacker
    class CFileUnpacker: rise::threading::CThread
    {
    public:
      enum EStatus
      {
        EUnknown = -3,
        EGenericError = -2,
        ERunning = -1,
        ESuccess = 0
      };

    public:
      CFileUnpacker();
      void Start(const std::string& sUnpackCmd);
      int GetStatus();

    private:
      void Run(void*);

    private:
      int m_nStatus;
      rise::process::CProcess m_tUnpackProc;
      std::string m_sUnpackCmd;
    };
  }
}

#endif // _FILEUNPACKER_H_
