#include <rise/common/ExceptionTemplate.h>
#include <rise/common/exmacros.h>
#include <rise/common/Log.h>
#include "sqlite3.h"
#include "DbConn.h"
#include "Objects.h"
#include "UsersToGroups.h"
#include "Acl.h"

namespace staff
{
  namespace security
  {

    CAcl& CAcl::Inst()
    {
      if (!m_pInst)
      {
        m_pInst = new CAcl;
      }

      return *m_pInst;
    }

    void CAcl::FreeInst()
    {
      if (m_pInst)
      {
        delete m_pInst;
        m_pInst = NULL;
      }
    }


    void CAcl::SetUserAccess(int nObjectId, EAccess eAccess)
    {
      sqlite3* pDb = CDbConn::GetDb();
      sqlite3_stmt* pVm = NULL;

      if (eAccess == EAccessInherited)
      {
        // remove ace
        int nResult = sqlite3_prepare_v2(pDb, "DELETE FROM objects_to_users_acl WHERE objectid = ? AND userid IS NULL",
                                         -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set user access(inherit): "
                       + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }
      else
      {
        // add ace
        int nResult = sqlite3_prepare_v2(pDb, "INSERT OR REPLACE INTO objects_to_users_acl(objectid, permit) "
                                                "VALUES(?, ?)", -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 2, eAccess == EAccessGranted ? 1 : 0);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set user access: " + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }

      RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
    }

    void CAcl::SetUserAccess(int nObjectId, int nUserId, EAccess eAccess)
    {
      sqlite3* pDb = CDbConn::GetDb();
      sqlite3_stmt* pVm = NULL;

      if (eAccess == EAccessInherited)
      {
        // remove ace
        int nResult = sqlite3_prepare_v2(pDb, "DELETE FROM objects_to_users_acl WHERE objectid = ? AND userid = ?",
                                         -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 2, nUserId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set user access(inherit): "
                       + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }
      else
      {
        // add ace
        int nResult = sqlite3_prepare_v2(pDb, "INSERT OR REPLACE INTO objects_to_users_acl(objectid, userid, permit) "
                                         "VALUES(?, ?, ?)", -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 2, nUserId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 3, eAccess == EAccessGranted ? 1 : 0);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set user access: " + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }

      RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
    }

    void CAcl::GetUserAccess(int nObjectId, int nUserId, EAccess& reAccess)
    {
      sqlite3* pDb = CDbConn::GetDb();
      sqlite3_stmt* pVm = NULL;

      RISE_ASSERTP(nObjectId >= 0);
      RISE_ASSERTP(nUserId >= 0);

      reAccess = EAccessInherited;

      // checking user access only for existing users
      int nResult = sqlite3_prepare_v2(pDb, "SELECT a.permit, a.userid, u.id FROM objects_to_users_acl a, users u WHERE "
                                              "a.objectid = ?1 AND (a.userid = ?2 OR a.userid IS NULL) AND u.id = ?2 "
                                              "ORDER BY userid IS NOT NULL DESC LIMIT 0,1", -1, &pVm, NULL);
      RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

      try
      {
        nResult = sqlite3_bind_int(pVm, 1, nObjectId);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        nResult = sqlite3_bind_int(pVm, 2, nUserId);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        nResult = sqlite3_step(pVm);
        if(nResult == SQLITE_ROW)
        {
          reAccess = sqlite3_column_int(pVm, 0) == 0 ? EAccessDenied : EAccessGranted;
        }
        else
        {
          RISE_ASSERTS(nResult == SQLITE_DONE, sqlite3_errmsg(pDb));
        }
      }
      catch(...)
      {
        RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
        throw;
      }

      RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
    }



    void CAcl::SetGroupAccess(int nObjectId, EAccess eAccess)
    {
      sqlite3* pDb = CDbConn::GetDb();
      sqlite3_stmt* pVm = NULL;

      if (eAccess == EAccessInherited)
      {
        // remove ace
        int nResult = sqlite3_prepare_v2(pDb, "DELETE FROM objects_to_groups_acl WHERE objectid = ? AND groupid IS NULL",
                                         -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set group access(inherit): "
                       + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }
      else
      {
        // add ace
        int nResult = sqlite3_prepare_v2(pDb, "INSERT OR REPLACE INTO objects_to_groups_acl(objectid, permit) "
                                                "VALUES(?, ?)", -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 2, eAccess == EAccessGranted ? 1 : 0);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set group access: " + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }

      RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
    }

    void CAcl::SetGroupAccess(int nObjectId, int nGroupId, EAccess eAccess)
    {
      sqlite3* pDb = CDbConn::GetDb();
      sqlite3_stmt* pVm = NULL;

      if (eAccess == EAccessInherited)
      {
        // remove ace
        int nResult = sqlite3_prepare_v2(pDb, "DELETE FROM objects_to_groups_acl WHERE objectid = ? AND groupid = ?",
                                         -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 2, nGroupId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set group access(inherit): "
                       + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }
      else
      {
        // add ace
        int nResult = sqlite3_prepare_v2(pDb, "INSERT OR REPLACE INTO objects_to_groups_acl(objectid, groupid, permit) "
                                                "VALUES(?, ?, ?)", -1, &pVm, NULL);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        try
        {
          nResult = sqlite3_bind_int(pVm, 1, nObjectId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 2, nGroupId);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          nResult = sqlite3_bind_int(pVm, 3, eAccess == EAccessGranted ? 1 : 0);
          RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

          RISE_ASSERTS(sqlite3_step(pVm) == SQLITE_DONE, "Failed to set group access: " + std::string(sqlite3_errmsg(pDb)));
        }
        catch(...)
        {
          RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
          throw;
        }
      }

      RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
    }

    void CAcl::GetGroupAccess(int nObjectId, int nGroupId, EAccess &reAccess)
    {
      sqlite3* pDb = CDbConn::GetDb();
      sqlite3_stmt* pVm = NULL;

      reAccess = EAccessInherited;

      // checking group access only for existing groups
      int nResult = sqlite3_prepare_v2(pDb, "SELECT a.permit, a.groupid, u.id FROM objects_to_groups_acl a, groups u WHERE "
                                              "a.objectid = ?1 AND (a.groupid = ?2 OR a.groupid IS NULL) AND u.id = ?2 "
                                              "ORDER BY groupid IS NOT NULL DESC LIMIT 0,1", -1, &pVm, NULL);
      RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

      try
      {
        nResult = sqlite3_bind_int(pVm, 1, nObjectId);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        nResult = sqlite3_bind_int(pVm, 2, nGroupId);
        RISE_ASSERTS(nResult == SQLITE_OK, sqlite3_errmsg(pDb));

        nResult = sqlite3_step(pVm);
        if(nResult == SQLITE_ROW)
        {
          reAccess = sqlite3_column_int(pVm, 0) == 0 ? EAccessDenied : EAccessGranted;
        }
        else
        {
          RISE_ASSERTS(nResult == SQLITE_DONE, sqlite3_errmsg(pDb));
        }
      }
      catch(...)
      {
        RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
        throw;
      }

      RISE_ASSERTS(sqlite3_finalize(pVm) == SQLITE_OK, sqlite3_errmsg(pDb));
    }


    bool CAcl::CalculateUserAccess(int nObjectId, int nUserId)
    {
      // TODO: optimize - rewrite to SQL, stored procedures
      // 1. check user access to object
      // 2. check user's groups access to object
      // 3. if access == inherited, object=parent object; goto 1

      int nCurrentObjectId = nObjectId;
      EAccess eAccess = EAccessInherited;
      TIntList lsGroupIds;
      bool bGroupsGet = false;

      for (;;)
      {
        GetUserAccess(nCurrentObjectId, nUserId, eAccess);

#ifdef _DEBUG
        rise::LogDebug2() << "Object id = " << nCurrentObjectId << ", user id = " << nUserId
            << ", access = " << eAccess;
#endif

        if (eAccess != EAccessInherited)
        {
          rise::LogDebug2() << "Rule found to access user " << nUserId << " to object: "
              << nObjectId << " in object: " << nCurrentObjectId << " = " << ((eAccess == EAccessGranted) ? "Grant" : "Deny");
          return eAccess == EAccessGranted;
        }

        if (!bGroupsGet)
        {
          CUsersToGroups::Inst().GetUserGroups(nUserId, lsGroupIds);
          bGroupsGet = true;
        }

        for (TIntList::const_iterator itGroupId = lsGroupIds.begin(); itGroupId != lsGroupIds.end(); ++itGroupId)
        {
          GetGroupAccess(nCurrentObjectId, *itGroupId, eAccess);

#ifdef _DEBUG
          rise::LogDebug2() << "Object id = " << nCurrentObjectId << ", user id = " << nUserId
              << ", group id = " << *itGroupId << ", access = " << eAccess;
#endif

          if (eAccess != EAccessInherited)
          {
            rise::LogDebug2() << "Rule found to access user " << nUserId << " to object: "
                << nObjectId << " by entering into group " << *itGroupId <<
                " in object: " << nCurrentObjectId << " = " << (eAccess == EAccessGranted);
            return eAccess == EAccessGranted;
          }
        }

        if (nCurrentObjectId == 0)
        {
          // rule is not found
          break;
        }

        CObjects::Inst().GetParentId(nCurrentObjectId, nCurrentObjectId);
      }

      // rule is not found -- using false by default
      rise::LogDebug2() << "Rule to access user " << nUserId << " to object: "
          << nObjectId << " is not found, using default: false";
      return false;
    }

    bool CAcl::CalculateUserAccess(const std::string& sObjectPath, int nUserId)
    {
      // TODO: optimize - rewrite to SQL, stored procedures

      std::string::size_type nPos = sObjectPath.find_first_of('.');
      std::string::size_type nBegin = 0;

#ifdef _DEBUG
      rise::LogDebug2() << "Calculating access to [" << sObjectPath << "] for user id=" << nUserId;
#endif

      CObjects& rObjects = CObjects::Inst();

      int nObjectId = 0;

      for (;;)
      {
#ifdef _DEBUG
          rise::LogDebug2() << "Getting child object [" << sObjectPath.substr(0, nPos) << "]";
#endif
        if (!rObjects.GetChildId(nObjectId, sObjectPath.substr(nBegin, nPos - nBegin), nObjectId))
        {
#ifdef _DEBUG
          rise::LogDebug2() << "Object [" << sObjectPath.substr(0, nPos)
              << "] is not found. Access will be calculated for [" << sObjectPath.substr(0, nBegin - 1) << "] id=" << nObjectId;
#endif
          break;
        }

        if (nPos == std::string::npos)
        {
#ifdef _DEBUG
          rise::LogDebug2() << "Object [" << sObjectPath << "] found. id=" << nObjectId;
#endif
          break;
        }

        nBegin = nPos + 1;
        nPos = sObjectPath.find_first_of('.', nBegin);
      }

      return CalculateUserAccess(nObjectId, nUserId);
    }


    CAcl::CAcl()
    {
    }

    CAcl::~CAcl()
    {
    }

    CAcl* CAcl::m_pInst = NULL;
  }
}