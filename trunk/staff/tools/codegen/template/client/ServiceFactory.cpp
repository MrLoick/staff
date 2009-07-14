// This file generated by staff_codegen
// DO NOT EDIT

#include <memory>
#foreach $(Project.Interfaces)
#include "$(Interface.Name)Proxy.h"
#end
#include "ServiceFactory.h"

void* CServiceFactory::AllocateClient(const std::string& sClientType, const std::string& sServiceUri, const std::string& sSessionId)
{
#foreach $(Project.Interfaces)
#foreach $(Interface.Classes)
  if (sClientType == typeid($(Class.NsName)).name())
  {
    std::auto_ptr< $(Class.NsName)Proxy > pClientProxy(new $(Class.NsName)Proxy);
    pClientProxy->Init(sServiceUri.size() != 0 ? sServiceUri : \
#ifeq($(Class.ServiceUri),)
"http://localhost:9090/axis2/services/$(Class.ServiceNsName)"\
#else
"$(Class.ServiceUri)"\
#ifeqend
, sSessionId);
    return pClientProxy.release();
  } else
#end
#end
  return NULL;
}

CServiceFactory& CServiceFactory::Inst()
{
  if (m_pInst == NULL)
  {
    m_pInst = new CServiceFactory;
  }

  return *m_pInst;
}

CServiceFactory::CServiceFactory()
{
}

CServiceFactory* CServiceFactory::m_pInst = NULL;