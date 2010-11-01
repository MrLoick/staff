#include <rise/plugin/PluginExport.h>
#include <rise/common/MutablePtr.h>
#include "Sqlite.h"

namespace staff
{
namespace das
{
  class ProviderAllocatorImpl: public ProviderAllocator
  {
  public:
    virtual PProvider Allocate(const std::string& sName)
    {
      if (sName == "staff.das.Sqlite")
      {
        return PProvider(new ::staff::das::Sqlite);
      }
      else
      {
        RISE_THROWS(rise::CLogicNoItemException, "Can't instantiate provider: " + sName +
                    "\nAvailable providers are:\n"
                    "  staff.das.Sqlite\n"
                    );
      }
    }

    virtual void GetProvidersList(StringList& rlsProvidersList)
    {
      rlsProvidersList.clear();
      rlsProvidersList.push_back("staff.das.Sqlite");
    }
  };
}
}

RISE_DECLARE_PLUGIN(::staff::das::ProviderAllocatorImpl);

