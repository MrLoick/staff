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

// This file generated by staff_codegen
// Client skeleton

#include <stdio.h>
#include <iostream>
#include <memory>
#include <rise/string/String.h>
#include <rise/common/Log.h>
#include <rise/common/ExceptionTemplate.h>
#include <rise/common/console.h>
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#include "Login.h"

int main(int /*nArgs*/, const char* /*paszArgs*/[])
{
  try
  {
    std::string sSessionId;
    {
      std::auto_ptr<staff::Login> pLogin(staff::ServiceFactory::Inst().GetService<staff::Login>());

      RISE_ASSERTS(pLogin.get(), "Cannot get client for service Login!");

      // Invoke login service
      std::cout << "Session expiration = ";
      int nEx = pLogin->GetSessionExpiration();
      std::cout << nEx << ": Success" << std::endl;

      std::cout << "User login ";
      sSessionId = pLogin->LoginUser("user", "user");
      std::cout << (sSessionId != "" ? ": Success" : ": Error") << std::endl;

      // assert second session id = first id

      std::string sSessionId2 = pLogin->LoginUser("user", "user");
      std::cout << "Second login = same sessid" << (sSessionId == sSessionId2 ? ": Success" : ": Error") << std::endl;
    }

    {
      std::auto_ptr<staff::Login> pLogin(staff::ServiceFactory::Inst().GetService<staff::Login>("", sSessionId));

      RISE_ASSERTS(pLogin.get(), "Cannot get client for service Login!");

      std::cout << "Validating session ";
      bool bSessionValid = pLogin->ValidateSession();
      std::cout << (bSessionValid ? ": Success" : ": Error") << std::endl;

      std::cout << "Getting user name ";
      std::string sUser = pLogin->GetUserName();
      std::cout << ": Success: sUser = " << sUser << std::endl;

      std::cout << "Getting user id ";
      int nUserId = pLogin->GetUserId();
      std::cout << ": Success: nUserId = " << nUserId << std::endl;

      std::cout << "Logout user ";
      pLogin->Logout();
      std::cout << ": Success" << std::endl;

      // security module must not pass this request
      try
      {
        std::cout << "Validating closed session ";
        bSessionValid = pLogin->ValidateSession();
        RISE_THROW(rise::CLogicNoItemException);
//        std::cout << (!bSessionValid ? ": Success" : ": Error") << std::endl;
      }
      catch(const staff::RemoteException& /*rEx*/)
      {
        std::cout << ": Success" << std::endl;
      }
    }
  }
  catch(const staff::RemoteException& rEx)
  {
    std::cout << ": Error" << std::endl;
    rise::LogError() << rEx.GetDescr();
  }
  RISE_CATCH_ALL

  return 0;
}
