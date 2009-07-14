namespace('webapp.widget');
IncludeCss("webapp/assets/widgets/ActiveServices/ActiveServices");

///////////////////////////////////////////////////////////////
// class ActiveServices: service list widget

webapp.widget.ActiveServices = Class.create();
webapp.widget.ActiveServices.prototype.extend(webapp.widget.Widget.prototype).extend
({
  Create: function(tParentElem)
  {
    this.tFrame = document.createElement('iframe');
    tParentElem.appendChild(this.tFrame);

    var tFrameDoc = (this.tFrame.contentWindow || this.tFrame.window).document;
    tFrameDoc.location = webapp.Env.protocol + Session.sHost + (Session.sPort ? (':' + Session.sPort) : '') + '/axis2/services';
    this.tFrame.className = "iframeHidden";
    this.tFrame.frameBorder = 'none';
    this.tFrame.visibility = 'hidden';
    addHandler(this.tFrame, 'load', this._OnFrameLoaded.bindAsEventListener(this));
    
/*    tParentElem.style.width = "100%";
    tParentElem.style.height = 400;
    tParentElem.style.overflow = "auto";*/
    this.tContentDiv = new webapp.ui.Div(tParentElem, { sClass: "divActiveServices" });

    this.tTable = new webapp.ui.Table(this.tContentDiv, { sClass: "tableActiveServices" });
    var tHeaderRow = this.tTable.AddHeadRow({sClass: "trActiveServicesHeader"});
    this.tTable.AddCell(tHeaderRow, {tContent: _("Service name"), sClass: "tdBordered" });
    this.tTable.AddCell(tHeaderRow, {tContent: _("Description"), sClass: "tdBordered" });

    var tResize = new YAHOO.util.Resize(tParentElem, { handles: ['b'], minWidth: 151, minHeight: 201 });

    tResize.on
    (
      'resize',
      function(tSize)
      {
//        tParentElem.style.width = tSize.width - 4;
        tParentElem.style.height = tSize.height - 4;
        this.tContentDiv.SetHeight(tSize.height - 4);
      }.bind(this)
    );
  },
  
  _OnFrameLoaded: function(tEvent)
  {
    var tFrameDoc = (this.tFrame.contentWindow || this.tFrame.window).document;
    var tFontElem = tFrameDoc.getElementsByTagName('font')[0];
    var tServiceRow;
    var tCellDescr;
    
    for (var itServiceElem = tFontElem.firstChild; itServiceElem; itServiceElem = itServiceElem.nextSibling)
    {
      if (itServiceElem.nodeType == 1)
      {
        if (itServiceElem.nodeName.toLowerCase() == 'h3')
        { // service name
          tServiceRow = this.tTable.AddRow();
          var tCellServiceName = this.tTable.AddCell(tServiceRow, { sClass: "tdBordered" });
          new webapp.ui.Label(tCellServiceName, { sCaption: _(itServiceElem.firstChild.firstChild.nodeValue),
               sClass: "labelServiceName" });
          tCellDescr = null;
        }
        else
        if (itServiceElem.nodeName.toLowerCase() == 'p')
        { // service description
          tCellDescr = this.tTable.AddCell(tServiceRow, { sClass: "tdBordered" });
          var sDescr = itServiceElem.firstChild ? _(itServiceElem.firstChild.nodeValue) : ("<" + _("No description") + ">");
          new webapp.ui.Label(tCellDescr, { sCaption: sDescr, sClass: "labelServiceDescr" });
        }
        else
        if (itServiceElem.nodeName.toLowerCase() == 'ul' && tCellDescr)
        { // service operations
          var tOpsElem = document.createElement("ul");
          tOpsElem.className = 'ulOperations';
          var tCaptionElem = document.createTextNode(_("Service operations") + ':');
          tOpsElem.appendChild(tCaptionElem);
          tCellDescr.appendChild(tOpsElem);

          for (var itOpElem = itServiceElem.firstChild; itOpElem; itOpElem = itOpElem.nextSibling)
          {
            if (itOpElem.nodeType == 1 && itOpElem.nodeName.toLowerCase() == 'li')
            {
              var tOpElem = document.createElement("li");
              tOpElem.className = 'liOperation';
              var tOpElemText = document.createTextNode(itOpElem.firstChild.nodeValue);
              tOpElem.appendChild(tOpElemText);
              tOpsElem.appendChild(tOpElem);
            }
          }
        }
      }
    }
  }
  
});
