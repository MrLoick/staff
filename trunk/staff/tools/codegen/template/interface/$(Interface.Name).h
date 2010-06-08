// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/

#ifndef _$(Interface.Name)_h_
#define _$(Interface.Name)_h_

#include <staff/common/WsdlTypes.h>
#include <staff/common/DataObject.h>
#include <staff/common/IService.h>
\
#var sOpeningNs
#var sEndingNs
\
#ifneq($(Interface.TargetNamespace),)

// targetNamespace: $(Interface.TargetNamespace)
#else
\
#ifeqend // tns
\
#ifneq($(Interface.Structs.$Count),0)   //   structs forwarding
#foreach $(Interface.Structs)
\
#ifneq($(Struct.NativeName),DataObject)
\
#var sNewOpeningNs $(Struct.OpeningNs)
#var sNewEndningNs $(Struct.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)\
#else
\
#ifeqend   // namespace changed
\
  struct $(Struct.Name);
#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#else
\
#ifeqend  // namespace changed
\
#else
\
#ifeqend   // !dataobject
#end       // foreach Interface.Structs

#ifeqend   // Interface.Structs.Count = 0
\
\
#ifneq($(Interface.Typedefs.$Count),0)   //  typedefs declaration
#foreach $(Interface.Typedefs)
#var sNewOpeningNs $(Typedef.OpeningNs)
#var sNewEndningNs $(Typedef.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)
#else
\
#ifeqend   // namespace changed
\
  typedef $(Typedef.DataType.UsedTypedef) $(Typedef.Name);\
#ifneq($(Typedef.Description),)
  //!< $(Typedef.Description)
#ifeqend
#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#else
\
#ifeqend   // namespace changed
#end        // foreach Interface.Typedefs

#ifeqend
\
#ifneq($(Interface.Structs.$Count),0)
\
#foreach $(Interface.Structs)              // structs declaration
\
#var sNewOpeningNs $(Struct.OpeningNs)
#var sNewEndningNs $(Struct.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)
#else
\
#ifeqend   // namespace changed
#ifneq($(Struct.Description),)
  //! $(Struct.Description)
#else
\
#ifeqend
#ifneq($(Struct.Detail),)
  /*! $(Struct.Detail) */
#else
\
#ifeqend
  struct $(Struct.Name)$(Struct.ParentDecl)
  {
#foreach $(Struct.Members)
    $(Param.DataType) $(Param.Name);\
#ifneq($(Param.Description),)
  //!< $(Param.Description)
#ifeqend
#end
  };
#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#ifeqend   // namespace changed
#end
#ifeqend
#foreach $(Interface.Classes)
\
#var sNewOpeningNs $(Class.OpeningNs)
#var sNewEndningNs $(Class.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)
#else
\
#ifeqend   // namespace changed
#ifneq($(Class.Description),)
  //! $(Class.Description)
#else
  //!  service $(Class.ServiceNsName)
#ifeqend
#ifneq($(Class.Detail),)
  /*! $(Class.Detail) */
#else
\
#ifeqend
#ifneq($(Class.ServiceUri),)
  // uri: $(Class.ServiceUri)
#else
\
#ifeqend
  class $(Class.Name): public staff::IService
  {
  public:
    //! destructor
    virtual ~$(Class.Name)() {}
#foreach $(Class.Members)

#ifneq($(Member.Description),)
    //! $(Member.Description)
#else
\
#ifeqend
#ifneq($(Member.Detail),)
    /*! $(Member.Detail) */
#else
\
#ifeqend
#ifneq($(Member.SoapAction),||$(Class.ServiceName)#$(Member.Name))
    // soapAction: $(Member.SoapAction)
#else
\
#ifeqend
#ifneq($(Member.NodeName),||$(Member.Name))
    // requestElement: $(Member.NodeName)
#else
\
#ifeqend
#ifneq($(Member.Return.ResponseName),||$(Member.Name)Result)
    // responseElement: $(Member.Return.ResponseName)
#else
\
#ifeqend
#ifneq($(Member.Return.NodeName),)
    // resultElement: $(Member.Return.NodeName)
#else
\
#ifeqend
    virtual $(Member.Return.UsedName) $(Member.Name)($(Member.Params))$(Member.Const) = 0;
#end
  };
\
#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#else
\
#ifeqend   // namespace changed

#end
$($sEndingNs)
#endif // _$(Interface.Name)_h_