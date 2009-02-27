// This file generated by staff_codegen
// DO NOT EDIT
\
#ifneq("$(Interface.Namespace)","")
#var sNamespace $(Interface.Namespace).
namespace('$(Interface.Namespace)');
#else
#var sNamespace 
#ifeqend
#foreach $(Interface.Classes)

///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct serializators
#foreach $(Interface.Structs)
function SerializeStruct_$(Struct.Name)(tOperation, rstStruct, tNode)
{
#foreach $(Struct.Members)
#ifeq($(Param.DataType.Type),struct)
  SerializeStruct_$(Struct.Name)(tOperation, rstStruct.$(Param.Name), tOperation.AddParameter('$(Param.Name)', '', tNode));
#else
#ifeq($(Param.DataType.Type),typedef)
  SerializeTypedef_$(Param.DataType.Name)(tOperation, rstStruct.$(Param.Name), tOperation.AddParameter('$(Param.Name)', '', tNode));
#else
  tOperation.AddParameter('$(Param.Name)', rstStruct.$(Param.Name), tNode);
#ifeqend
#ifeqend
#end
}

#end

///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct deserializators
#foreach $(Interface.Structs)
function DeserializeStruct_$(Struct.Name)(tOperation, tNode)
{
  var tResult = 
  {
#foreach $(Struct.Members)
#ifeq($(Param.$Num),0) // ������� ����� �����������
\
#else
,
#ifeqend
    $(Param.Name): null\
#end

  };

#foreach $(Struct.Members)
#ifeq($(Param.DataType.Type),struct)
  tResult.$(Param.Name) = DeserializeStruct_$(Param.DataType.Name)(tOperation, tOperation.SubNode("$(Param.Name)", tNode));
#else
#ifeq($(Param.DataType.Type),typedef)
  tResult.$(Param.Name) = DeserializeTypedef_$(Param.DataType.Name)(tOperation, tOperation.SubNode("$(Param.Name)", tNode));
#else
  tResult.$(Param.Name) = tOperation.SubNodeText("$(Param.Name)", tNode);
#ifeqend
#ifeqend
#end
  return tResult;
}

#end

//-----------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef serializators
#foreach $(Interface.Typedefs)

// $(Typedef.Name)  Typedef.DataType.Type $(Typedef.DataType.Type) $(Typedef.DataType.Name)
#ifeq($(Typedef.DataType.IsTemplate),1)
function SerializeTypedef_$(Typedef.Name)(tOperation, rtType, tNode)
{
  for(var i = 0; i != rtType.length; ++i)
#ifeq($(Typedef.DataType.Name),std::map) // ---- map -------------------------- key
  {
    var tItem = tOperation.AddParameter('Item', '', tNode);
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),struct)    // !!struct!!
    SerializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, rtType[i], tOperation.AddParameter('Key', '', tItem));
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),generic)    // !!generic!!
    tOperation.AddParameter('Key', rtType[i].key, tItem);
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),dataobject) // !!dataobject!! 
    tOperation.AddDataParameter('Key', rtType[i].key, tItem); // dataobject as key??? very strange
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),typedef)    // !!typedef!!
    SerializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, rtType[i], tOperation.AddParameter('Key', '', tItem));
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),template)    // !!template!!
    SerializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, rtType[i], tOperation.AddParameter('Key', '', tItem));
#else
#error "Typedef.DataType.Type = $(Typedef.DataType.TemplateParams.TemplateParam1.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend //  - value -
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),struct)    // !!struct!!
    SerializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam2.Name)(tOperation, rtType[i], tOperation.AddParameter('Value', '', tItem));
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),generic)    // !!generic!!
    tOperation.AddParameter('Value', rtType[i].value, tItem);
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),dataobject) // !!dataobject!! 
    tOperation.AddDataParameter('Value', rtType[i].value, tItem); // dataobject as value??? very strange
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),typedef)    // !!typedef!!
    SerializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam2.Name)(tOperation, rtType[i], tOperation.AddParameter('Value', '', tItem));
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),template)    // !!template!!
    SerializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam2.Name)(tOperation, rtType[i], tOperation.AddParameter('Value', '', tItem));
#else
#error "Typedef.DataType.Type = $(Typedef.DataType.TemplateParams.TemplateParam2.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
  }
#else  // ---------------------------- list -----------------------------------
  {
// Typedef.DataType.TemplateParams.TemplateParam1.Type = $(Typedef.DataType.TemplateParams.TemplateParam1.Type)
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),struct)    // !!struct!!
    SerializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, rtType[i], tOperation.AddParameter('Item', '', tNode));
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),generic)    // !!generic!!
  tOperation.AddParameter('Item', rtType[i], tNode);
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),dataobject) // !!dataobject!! 
  tOperation.AddDataParameter('Item', rtType[i], tNode);
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),typedef)    // !!typedef!!
  SerializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, rtType[i], tOperation.AddParameter('Item', '', tNode))
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),template)    // !!template!!
  SerializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, rtType[i], tOperation.AddParameter('Item', '', tNode))
#else
#error "Typedef.DataType.Type = $(Typedef.DataType.TemplateParams.TemplateParam1.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
  }
#ifeqend
  return tNode;
}
#else // DataType.IsTemplate
#ifneq($(Typedef.DataType.Type),struct)
function SerializeTypedef_$(Typedef.Name)(tOperation, rtType, tNode)
{
#ifeq($(Typedef.DataType.Type),generic)    // !!generic!!
  return tOperation.SetValue(rtType, tNode);
#else
#ifeq($(Typedef.DataType.Type),dataobject) // !!dataobject!! 
  return tOperation.SetData(rtType, tNode);
#else
#ifeq($(Typedef.DataType.Type),typedef)    // !!typedef!!
  return SerializeTypedef_$(Typedef.DataType.Name)(tOperation, rtType, tNode);
#else
#ifeq($(Typedef.DataType.Type),template)    // !!template!!
  return SerializeTypedef_$(Typedef.DataType.Name)(tOperation, rtType, tNode);
#else
#error "Typedef.DataType.Type = $(Typedef.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
}
#ifeqend // #ifneq($(Typedef.DataType.Type),struct)

#ifeqend // ifeq($(Typedef.DataType.IsTemplate),1)
#end // foreach $(Interface.Typedefs)

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef deserializators
#foreach $(Interface.Typedefs)
function DeserializeTypedef_$(Typedef.Name)(tOperation, tNode)
{
#ifeq($(Typedef.DataType.IsTemplate),1)
// container :: $(Typedef.DataType.Name)

  var tItem = null;

  var tResult = tNode == null ? tOperation.ResultElement() : tNode;
  var aResult = new Array();
  var j = 0;

  for (var i = 0; i < tResult.childNodes.length; i++)
  {
#ifeq($(Typedef.DataType.Type),generic)
    if(tNode.firstChild == null) // generic 1
    {
      aResult[j] = "";
    } else
    {
      aResult[j] = tResult.childNodes[i].firstChild.nodeValue;
    }
#else
#ifeq($(Typedef.DataType.Type),struct)
// *** struct1 $(Typedef.DataType.Name)
    aResult[j++] = DeserializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam1)(tOperation, tResult.childNodes[i]);
#else
#ifeq($(Typedef.DataType.Type),typedef)
// *** td1 $(Typedef.DataType.Name)
    aResult[j++] = DeserializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1)(tOperation, tResult.childNodes[i]);
#else
#ifeq($(Typedef.DataType.Type),dataobject)
    aResult[j++] = tResult.childNodes[i]; // dataobject 2
#else
#ifeq($(Typedef.DataType.Type),template)  // !!      TEMPLATE        !!
    if( tResult.childNodes[i].nodeName == "Item")
    {
#ifeq($(Typedef.DataType.Name),std::map)
//template $(Typedef.DataType.Name)<$(Typedef.DataType.TemplateParams.TemplateParam1.Name), $(Typedef.DataType.TemplateParams.TemplateParam2.Name)>
      var tResultPair = 
      {
        key: null,
        value: null  
      };
    
      var pKey = tOperation.SubNode("Key", tResult.childNodes[i]);
      var pValue = tOperation.SubNode("Value", tResult.childNodes[i]);

      tResultPair.key =\
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),struct)
 DeserializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, pKey); // *** struct $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),typedef)
 DeserializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, pKey); // *** typedef $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),dataobject)
 pKey; // *** dataobject $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#else
  pKey.firstChild != null ? pKey.firstChild.nodeValue : ""; // *** generic $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#ifeqend
#ifeqend
#ifeqend
      tResultPair.value =\
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),struct)
 DeserializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam2.Name)(tOperation, pValue); // *** struct $(Typedef.DataType.TemplateParams.TemplateParam2.Name)
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),typedef)
 DeserializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam2.Name)(tOperation, pValue); // *** typedef $(Typedef.DataType.TemplateParams.TemplateParam2.Name)
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),dataobject)
 tResult.pValue; // *** dataobject $(Typedef.DataType.TemplateParams.TemplateParam2.Name)
#else
 tResult.pValue.firstChild != null ? tResult.pValue.firstChild.nodeValue : ""; // *** generic $(Typedef.DataType.TemplateParams.TemplateParam2.Name)
#ifeqend
#ifeqend
#ifeqend
      aResult[j++] = tResultPair;
#else
//template $(Typedef.DataType.Name)<$(Typedef.DataType.TemplateParams.TemplateParam1.Name)>
    aResult[j++] =\
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),struct)
 DeserializeStruct_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, tResult.childNodes[i]); // *** struct $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),typedef)
 DeserializeTypedef_$(Typedef.DataType.TemplateParams.TemplateParam1.Name)(tOperation, tResult.childNodes[i]); // *** typedef $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#else
 tResult.childNodes[i].firstChild != null ? tResult.childNodes[i].firstChild.nodeValue : ""; // *** generic $(Typedef.DataType.TemplateParams.TemplateParam1.Name)
#ifeqend
#ifeqend
#ifeqend // #ifeq($(Typedef.DataType.Name),std::map)
    }
#else
#error "Typedef.DataType.Type = $(Typedef.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
  }

  return aResult;
#else // #ifeq($\(Typedef.DataType.IsTemplate),1) --------------------------------------------------------
// not a container :: $(Typedef.DataType.Name)
  if(tNode == null)
  {
    tNode = tOperation.ResultElement();
  }
#ifeq($(Typedef.DataType.Type),generic)    // !!generic!!
  return tNode.firstChild != null ? tNode.firstChild.nodeValue : "";
#else
#ifeq($(Typedef.DataType.Type),dataobject) // !!dataobject!! 
  return tNode;
#else
#ifeq($(Typedef.DataType.Type),typedef)    // !!typedef!!
  return DeserializeTypedef_$(Typedef.DataType.Name)(tOperation, tNode);
#else
#ifeq($(Typedef.DataType.Type),struct)    // !!typedef!!
  return DeserializeTypedef_$(Typedef.DataType.Name)(tOperation, tNode);
#else
#error "Typedef.DataType.Type = $(Typedef.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
}

#end

//-----------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////
// class: $(Class.ServiceName)

$($sNamespace)$(Class.ServiceName) = Class.create();
$($sNamespace)$(Class.ServiceName).tClient = null;
$($sNamespace)$(Class.ServiceName).prototype = 
{
  initialize: function(sServiceName, sHostName, sHostPort)
  {
    if(sServiceName == null)
      sServiceName = '$($sNamespace)$(Class.ServiceName)';
    this.tClient = new staff.Client(sServiceName, sHostName, sHostPort);
  },
  
  SetID: function(sID)
  {
    this.tClient.SetID(sID);
  }\
#foreach $(Class.Members)
,

  $(Member.Name): function(\
#foreach $(Member.Params)
$(Param.Name), \
#end
pOnComplete, pOnError)
  {
    var tOperation = new staff.Operation('$(Member.Name)', this.tClient.GetServiceUri());
    
#foreach $(Member.Params)
#ifeq($(Param.DataType.Type),struct) // !!struct!! 
    SerializeStruct_$(Param.DataType.Name)(tOperation, $(Param.Name), tOperation.AddParameter('$(Param.Name)'));
#else
#ifeq($(Param.DataType.Type),typedef)    // !!typedef!!
    SerializeTypedef_$(Param.DataType.Name)(tOperation, $(Param.Name), tOperation.AddParameter('$(Param.Name)'));
#else
#ifeq($(Param.DataType.Type),generic)    // !!generic!!
    tOperation.AddParameter('$(Param.Name)', $(Param.Name));
#ifeqend
#else
#ifeq($(Param.DataType.Type),dataobject) // !!dataobject!! 
    tOperation.AddDataParameter('$(Param.Name)', $(Param.Name));
#ifeqend
#ifeqend
#ifeqend
#end
    if(typeof pOnComplete == 'function')
    { // make async call
      this.tClient.InvokeOperation(tOperation,
        function(tOperation)
        {
#ifeq($(Member.Return.Type),struct) // !!struct!! 
          pOnComplete(DeserializeStruct_$(Member.Return.Name)(tOperation), tOperation);
#else
#ifeq($(Member.Return.Type),typedef)    // !!typedef!!
          pOnComplete(DeserializeTypedef_$(Member.Return.Name)(tOperation), tOperation);
#else
#ifeq($(Member.Return.Type),dataobject) // !!dataobject!! 
          pOnComplete(tOperation.ResultElement().firstChild, tOperation);
#else
#ifeq($(Member.Return.Type),generic)    // !!generic!!
#ifneq($(Member.Return.Name),void)      // !!not_void!!
          pOnComplete(tOperation.ResultElement().firstChild != null ? tOperation.ResultElement().firstChild.nodeValue : "", tOperation);
#else                                   // !!void!!
          pOnComplete(tOperation);
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
        },
        pOnError
      );
    }
    else
    {
      this.tClient.InvokeOperation(tOperation);
#ifeq($(Member.Return.Type),struct) // !!struct!! 

      return DeserializeStruct_$(Member.Return.Name)(tOperation);
#else
#ifeq($(Member.Return.Type),typedef)    // !!typedef!!

      return DeserializeTypedef_$(Member.Return.Name)(tOperation);
#else
#ifeq($(Member.Return.Type),dataobject) // !!dataobject!! 

      return tOperation.ResultElement().firstChild;
#else
#ifeq($(Member.Return.Type),generic)    // !!generic!!
#ifneq($(Member.Return.Name),void)      // !!not_void!!

      return tOperation.ResultElement().firstChild != null ? tOperation.ResultElement().firstChild.nodeValue : "";
#else                                   // !!void!!
\
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
    }
  }\
#end

}

#end
