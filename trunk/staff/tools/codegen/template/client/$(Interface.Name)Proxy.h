// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// DO NOT EDIT

#ifndef _$(Interface.Name)Proxy_h_
#define _$(Interface.Name)Proxy_h_

#ifneq($(Interface.Classes.$Count),0)
#include <staff/client/ServiceClient.h>
#ifeqend
#include <staff/common/WsdlTypes.h>
#include "$(Interface.Name).h"

#ifneq($(Interface.Classes.$Count),0)
#foreach $(Interface.Classes)
$(Class.OpeningNs)
//! Proxy for component service $(Class.ServiceNsName)
class $(Class.Name)Proxy: public $(Class.Name)
{
public:
  $(Class.Name)Proxy();
  virtual ~$(Class.Name)Proxy();
  void Init(const std::string& sServiceUri, const std::string& sSessionId, const std::string& sInstanceId);
  void Deinit();
  virtual staff::CServiceClient* GetClient();
#foreach $(Class.Members)
  $(Member.Return) $(Member.Name)($(Member.Params))$(Member.Const);
#end
private:
  mutable staff::CServiceClient m_tClient;
};

$(Class.EndingNs)
#end
#else // included types
namespace staff
{
  class CDataObject;
#foreach $(Interface.Structs)
#cginclude <common/StructSerialization.h>
#end
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.DataType.IsTemplate),1) // there must be an serializer for each container
  CDataObject& operator<<(CDataObject& rdoParam, const $(Typedef.NsName)& rtType);
#else // DataType.IsTemplate
#ifneq($(Typedef.DataType.Type),struct)     // !!struct!! structs already have serializator
  CDataObject& operator<<(CDataObject& rdoParam, const $(Typedef.NsName)& rtType);
#ifeqend // ifneq($(Typedef.DataType.Type),struct
#ifeqend // ifeq($(Typedef.DataType.IsTemplate),1)
#ifeq($(Typedef.DataType.IsTemplate),1) // there must be an serializer for each container
  const CDataObject& operator>>(const CDataObject& rdoParam, $(Typedef.NsName)& rtType);
#else // DataType.IsTemplate
#ifneq($(Typedef.DataType.Type),struct)     // !!struct!! structs already have serializator
  const CDataObject& operator>>(const CDataObject& rdoParam, $(Typedef.NsName)& rtType);
#ifeqend // ifneq($(Typedef.DataType.Type),struct
#ifeqend // ifeq($(Typedef.DataType.IsTemplate),1)
#end // foreach $(Interface.Typedefs)
}

#ifeqend
#endif

