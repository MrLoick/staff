// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include "$(Interface.FilePath)$(Interface.Name)Impl.h"

#foreach $(Interface.Classes)
$(Class.OpeningNs)
$(Class.Name)Impl::$(Class.Name)Impl()
{
}

$(Class.Name)Impl::~$(Class.Name)Impl()
{
}

void $(Class.Name)Impl::OnCreate()
{
  // this function is called when service instance is created and registered
}

void $(Class.Name)Impl::OnDestroy()
{
  // this function is called immediately before service instance destruction
}

#foreach $(Class.Members)
$(Member.Return.UsedName) $(Class.Name)Impl::$(Member.Name)($(Member.Params))$(Member.Const)
{
#ifneq($(Member.Return),void)
  $(Member.Return.UsedName) tResult;
  // TODO: place your code here

  return tResult;  // result
#else
  // TODO: place your code here
#ifeqend
}

#end

$(Class.EndingNs)
#end