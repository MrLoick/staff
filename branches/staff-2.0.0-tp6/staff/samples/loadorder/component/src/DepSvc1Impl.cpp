// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include <rise/common/Log.h>
#include "DepSvc1Impl.h"

namespace samples
{
namespace loadorder
{

DepSvc1Impl::DepSvc1Impl()
{
}

DepSvc1Impl::~DepSvc1Impl()
{
}

void DepSvc1Impl::OnCreate()
{
  rise::LogInfo() << "Service 1 is loaded";
}

void DepSvc1Impl::OnDestroy()
{
  // this function is called immediately before service instance destruction
}


}
}

