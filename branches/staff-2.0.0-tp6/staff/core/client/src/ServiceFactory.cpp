// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// DO NOT EDIT

#include <memory>
#include <map>
#include <rise/string/String.h>
#include <rise/common/MutablePtr.h>
#include "IProxyAllocator.h"
#include "ServiceFactory.h"

namespace staff
{
  class ServiceFactory::ServiceFactoryImpl
  {
  public:
    typedef std::map<std::string, IProxyAllocator*> ProxyAllocatorMap;

  public:
    ProxyAllocatorMap m_mProxyAllocators;
  };

  IService* ServiceFactory::AllocateClient(const std::string& sClientType,
                                            const std::string& sServiceUri,
                                            const std::string& sSessionId,
                                            const std::string& sInstanceId)
  {
    ServiceFactoryImpl::ProxyAllocatorMap::const_iterator itProxyAllocator =
        m_pImpl->m_mProxyAllocators.find(sClientType);
    if (itProxyAllocator == m_pImpl->m_mProxyAllocators.end())
    {
      return NULL;
    }

    return itProxyAllocator->second->AllocateProxy(sServiceUri, sSessionId, sInstanceId);
  }

  IService* ServiceFactory::AllocateClientByHost(const std::string& sClientType,
                                          const std::string& sHost,
                                          int nPort,
                                          const std::string& sProtocol,
                                          const std::string& sServiceName,
                                          const std::string& sSessionId,
                                          const std::string& sInstanceId)
  {
    ServiceFactoryImpl::ProxyAllocatorMap::const_iterator itProxyAllocator =
        m_pImpl->m_mProxyAllocators.find(sClientType);
    if (itProxyAllocator == m_pImpl->m_mProxyAllocators.end())
    {
      return NULL;
    }

    const std::string& sBaseUri = sProtocol + "://" + sHost + ":" + rise::ToStr(nPort) + "/axis2/services/";

    return itProxyAllocator->second->AllocateProxy(sBaseUri, sServiceName, sSessionId, sInstanceId);
  }

  ServiceFactory& ServiceFactory::Inst()
  {
    static ServiceFactory tInst;
    return tInst;
  }

  void ServiceFactory::RegisterProxyAllocator(const std::string& sProxyTypeId, IProxyAllocator& rProxyAllocator)
  {
    m_pImpl->m_mProxyAllocators[sProxyTypeId] = &rProxyAllocator;
  }

  ServiceFactory::ServiceFactory()
  {
    m_pImpl = new ServiceFactoryImpl;
  }

  ServiceFactory::~ServiceFactory()
  {
    delete m_pImpl;
  }

}
