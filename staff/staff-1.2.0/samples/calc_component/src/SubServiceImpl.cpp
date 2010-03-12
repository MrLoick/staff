// This file generated by staff_codegen
// Service Implementation

#include <rise/common/ExceptionTemplate.h>
#include <rise/string/String.h>
#include "Calculator.h"
#include "SubServiceImpl.h"
#include "SubServiceContext.h"
#include "ServiceLocator.h"

namespace samples
{
  namespace calc
  {

    CSubServiceImpl::~CSubServiceImpl()
    {
    }

    int CSubServiceImpl::Sub(int nA, int nB) const
    {
      const rise::CString& sID = CSubServiceContext::GetContext().GetServiceID(this);

      CCalculator* pCalculatorService = 
        reinterpret_cast<CCalculator*>(staff::CServiceLocator::Inst().LocateService("samples.Calculator", sID));

      RISE_ASSERTES(pCalculatorService != NULL, rise::CLogicNoItemException, 
        "Service [samples.Calculator] with id [" + sID + "] not found");

      return pCalculatorService->Sub(nA, nB);
    }


  }
}
