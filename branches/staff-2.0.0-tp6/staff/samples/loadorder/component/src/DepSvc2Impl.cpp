// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include <rise/common/Log.h>
#include "DepSvc2Impl.h"

namespace samples
{
namespace loadorder
{

DepSvc2Impl::DepSvc2Impl()
{
}

DepSvc2Impl::~DepSvc2Impl()
{
}

void DepSvc2Impl::OnCreate()
{
  rise::LogInfo() << "Service 2 is loaded";
}

void DepSvc2Impl::OnDestroy()
{
  // this function is called immediately before service instance destruction
}


}
}

