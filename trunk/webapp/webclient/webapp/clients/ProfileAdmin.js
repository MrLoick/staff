// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// DO NOT EDIT
namespace('webapp.admin');

///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct serializators
function SerializeStruct_webapp_admin_SWidget(tOperation, rstStruct, tNode)
{
  tOperation.AddParameter('sName', rstStruct.sName, tNode);
  tOperation.AddParameter('sDescr', rstStruct.sDescr, tNode);
}

function SerializeStruct_webapp_admin_SProfile(tOperation, rstStruct, tNode)
{
  tOperation.AddParameter('sName', rstStruct.sName, tNode);
  SerializeTypedef_webapp_admin_TWidgetList(tOperation, rstStruct.lsWidgets, tOperation.AddParameter('lsWidgets', '', tNode));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct deserializators
function DeserializeStruct_webapp_admin_SWidget(tOperation, tNode)
{
  var tResult = {};

  tResult.sName = tOperation.SubNodeText("sName", tNode);
  tResult.sDescr = tOperation.SubNodeText("sDescr", tNode);
  return tResult;
}

function DeserializeStruct_webapp_admin_SProfile(tOperation, tNode)
{
  var tResult = {};

  tResult.sName = tOperation.SubNodeText("sName", tNode);
  tResult.lsWidgets = DeserializeTypedef_webapp_admin_TWidgetList(tOperation, tOperation.SubNode("lsWidgets", tNode));
  return tResult;
}

//-----------------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef serializators

// ::webapp::admin::TStringList  Typedef.DataType.Type template std::list
function SerializeTypedef_webapp_admin_TStringList(tOperation, rtType, tNode)
{
  for(var i = 0; i != rtType.length; ++i)
  {
// Typedef.DataType.TemplateParams.TemplateParam1.Type = string
  tOperation.AddParameter('Item', rtType[i], tNode);
  }
  return tNode;
}

// ::webapp::admin::TWidgetList  Typedef.DataType.Type template std::list
function SerializeTypedef_webapp_admin_TWidgetList(tOperation, rtType, tNode)
{
  for(var i = 0; i != rtType.length; ++i)
  {
// Typedef.DataType.TemplateParams.TemplateParam1.Type = struct
    SerializeStruct_webapp_admin_SWidget(tOperation, rtType[i], tOperation.AddParameter('Item', '', tNode));
  }
  return tNode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef deserializators
function DeserializeTypedef_webapp_admin_TStringList(tOperation, tNode)
{
// container :: std::list< std::string >
  var tItem = null;

  var tResult = tNode == null ? tOperation.ResultElement() : tNode;
  var aResult = new Array();
  var j = 0;

  for (var i = 0; i < tResult.childNodes.length; i++)
  {
    if( tResult.childNodes[i].nodeName == "Item")
    {
//template std::list<std::string>
    aResult[j++] = tResult.childNodes[i].firstChild != null ? tResult.childNodes[i].firstChild.nodeValue : ""; // *** generic std::string
    }
  }

  return aResult;
}

function DeserializeTypedef_webapp_admin_TWidgetList(tOperation, tNode)
{
// container :: std::list< ::webapp::admin::SWidget >
  var tItem = null;

  var tResult = tNode == null ? tOperation.ResultElement() : tNode;
  var aResult = new Array();
  var j = 0;

  for (var i = 0; i < tResult.childNodes.length; i++)
  {
    if( tResult.childNodes[i].nodeName == "Item")
    {
//template std::list<::webapp::admin::SWidget>
    aResult[j++] = DeserializeStruct_webapp_admin_SWidget(tOperation, tResult.childNodes[i]); // *** struct ::webapp::admin::SWidget
    }
  }

  return aResult;
}


//-----------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////
// class: webapp.admin.ProfileAdmin

webapp.admin.ProfileAdmin = Class.create();
webapp.admin.ProfileAdmin.prototype = 
{
  initialize: function(sServiceUri, sSessionId, sTargetNamespace)
  {
    if (!sServiceUri)
    {
      sServiceUri = webapp.Env.protocol + Session.sHost + (Session.sPort ? (':' + Session.sPort) : '') + '/axis2/services/webapp.admin.ProfileAdmin';
    }
    
    if (!sTargetNamespace)
    {
      sTargetNamespace = sServiceUri;
    }
    
    this.sTargetNamespace = sTargetNamespace || sServiceUri;

    this.tClient = new staff.Client(sServiceUri, sSessionId || Session.sID || "");
  },
  
  SetDataObjectAsXml: function(bDataObjectAsXml)
  {
    this.bDataObjectAsXml = bDataObjectAsXml;
  },
  
  SetID: function(sSessionId)
  {
    this.tClient.SetSessionId(sSessionId);
  },

  GetProfileList: function(pOnComplete, pOnError)
  {
    var tOperation = new staff.Operation('GetProfileList', this.sTargetNamespace, '', '');
    tOperation.SetSoapAction("");
    
    if(typeof pOnComplete == 'function')
    { // make async call
      this.tClient.InvokeOperation(tOperation,
        function(tOperation)
        {
          pOnComplete(DeserializeTypedef_webapp_admin_TStringList(tOperation), tOperation);
        },
        pOnError
      );
    }
    else
    {
      this.tClient.InvokeOperation(tOperation);

      return DeserializeTypedef_webapp_admin_TStringList(tOperation);
    }
  },

  RemoveProfile: function(sName, pOnComplete, pOnError)
  {
    var tOperation = new staff.Operation('RemoveProfile', this.sTargetNamespace, '', '');
    tOperation.SetSoapAction("");
    
    tOperation.AddParameter('sName', sName);
    if(typeof pOnComplete == 'function')
    { // make async call
      this.tClient.InvokeOperation(tOperation,
        function(tOperation)
        {
          pOnComplete(tOperation);
        },
        pOnError
      );
    }
    else
    {
      this.tClient.InvokeOperation(tOperation);
    }
  },

  GetProfile: function(sName, pOnComplete, pOnError)
  {
    var tOperation = new staff.Operation('GetProfile', this.sTargetNamespace, '', '');
    tOperation.SetSoapAction("");
    
    tOperation.AddParameter('sName', sName);
    if(typeof pOnComplete == 'function')
    { // make async call
      this.tClient.InvokeOperation(tOperation,
        function(tOperation)
        {
          pOnComplete(DeserializeStruct_webapp_admin_SProfile(tOperation), tOperation);
        },
        pOnError
      );
    }
    else
    {
      this.tClient.InvokeOperation(tOperation);

      return DeserializeStruct_webapp_admin_SProfile(tOperation);
    }
  },

  SetProfile: function(rProfile, pOnComplete, pOnError)
  {
    var tOperation = new staff.Operation('SetProfile', this.sTargetNamespace, '', '');
    tOperation.SetSoapAction("");
    
    SerializeStruct_webapp_admin_SProfile(tOperation, rProfile, tOperation.AddParameter('rProfile'));
    if(typeof pOnComplete == 'function')
    { // make async call
      this.tClient.InvokeOperation(tOperation,
        function(tOperation)
        {
          pOnComplete(tOperation);
        },
        pOnError
      );
    }
    else
    {
      this.tClient.InvokeOperation(tOperation);
    }
  }
}
