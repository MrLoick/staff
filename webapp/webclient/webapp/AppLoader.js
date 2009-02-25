///////////////////////////////////////////////////////////////
// namespace webapp
namespace('webapp');

webapp.AppLoader =
{
  tMenuBar: null,
  tWidgetLoader: null,
  
///---------------------------------------------------
  Init: function(aOptions, pCompleteFunction)
  {
    var self = this;
    if(aOptions == null)
      aOptions = {};
      
    var asYuiComponents = [
      "reset", "fonts", "reset-fonts-grids", //css
      "button", "datatable", "container", "tabview"]; // js

    var tYuiLoader = new YAHOO.util.YUILoader
    ({
      require: asYuiComponents,
      base: 'yui/',
      onSuccess: function()
      {
        // Instantiate the Dialog
        webapp.dlgList = new YAHOO.widget.Dialog
        (
          "dlgList", 
          { 
            width: "230px",
            fixedcenter: true,
            visible: false, 
            constraintoviewport: true,
            buttons: 
            [ 
              { text: "Ввод", handler: function() { webapp.dlgList.onConfirm(); }, isDefault: true },
              { text: "Отмена", handler: function(){ webapp.dlgList.hide();} } 
            ]
          }
        );
        // Render the Dialog
        webapp.dlgList.render();
        LoadBase();
      },
      onFailure: function(e)
      {
        alert("error: " + YAHOO.lang.dump(e));
      }
     });
    tYuiLoader.insert();

    function LoadBase()
    {
      Include
      (
        ["ws", "error", "noselect"], 
        "webapp/common/",
        LoadStaff,
        function()
        {
          return (typeof WS != 'undefined') && (typeof GetErrorStr != 'undefined');
        }
      );
    }
    
    function LoadStaff()
    {
      Include
      (
        ["staff"],
        "webapp/common/",
        LoadView,
        function()
        {
          return (typeof staff != 'undefined');
        }
      );
    }
    
    function LoadView()
    {
      var asScripts = ["webapp.MessageBox"];
      if(aOptions.bEnableTabView)
      {
        asScripts.push("webapp.TabView");
      } 

      IncludeClass
      (
        asScripts,
        "",
        LoadWidget
      );
    }
    
    function LoadWidget()
    {
      IncludeClass
      (
        ["widget.Widget"],
        "webapp/",
        function()
        {
          try
          {
            IncludeClass
            (
              ["widget.WidgetManager", "widget.WidgetLoader", "widget.WidgetEditDialog"],
              "webapp/",
              function()
              {
                self.tWidgetLoader = new widget.WidgetLoader(aOptions.tWidgetInitInfo);
                pCompleteFunction();
              }
            );
          }
          catch(tEx)
          {
            var sMessage = tEx.text ? tEx.text : (tEx.message ? tEx.message : "");
            webapp.MessageBox.ShowMessage('Ошибка при создании загрузчика виджетов:' + sMessage, 'error');
          }
        }
      );
    }
  },
  
  GetMainTabView: function()
  {
    return this.tTabView;
  },
  
  GetWidgetLoader: function()
  {
    return this.tWidgetLoader;
  }
};
