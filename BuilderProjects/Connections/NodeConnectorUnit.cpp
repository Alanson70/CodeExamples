//---------------------------------------------------------------------------


#pragma hdrstop

#include "NodeConnectorUnit.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
#ifdef PROXY
__fastcall TNodeConnector::TNodeConnector(TComponent* Owner)  : TProxyConnector(Owner)
#else
__fastcall TNodeConnector::TNodeConnector(TComponent* Owner)  : TLinksConnector(Owner)
#endif
{
 //_Links=new TLink(this);
}
//--------------------------------------------------------------------------
__fastcall TNodeConnector::~TNodeConnector()
{
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessFor(int purpose)
{
 switch(purpose)
 {
  case 1 : return AccessForRunning();
  case 2 : return AccessForCommonMonitor();
  case 3 : return AccessForSimpleControl();
  case 4 : return AccessForCommonLocalControl();
  case 5 : return AccessForCommonRemoteControl();
  case 6 : return AccessForFullLocalControl();
  case 7 : return AccessForFullRemoteControl();
  case 8 : return AccessForManagement();
  case 9 : return AccessForHiddenOptions();
  case 10 : return AccessForConfiguring();
 }
 return false;
}
//---------------------------------------------------------------------------
bool TNodeConnector::AccessForRunning()
{
 if(UserAccessRights()==usertypeGUEST) return true;
 return true;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForCommonMonitor()
{
 if(UserAccessRights()==usertypeGUEST) return true;
 return true;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForSimpleControl()
{
 if(UserAccessRights()==usertypeGUEST) return false;
 return true;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForCommonLocalControl()
{
 if(UserAccessRights()==usertypeGUEST) return false;
 return true;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForCommonRemoteControl()
{
 if(UserAccessRights()==usertypeGUEST)    return false;
 if(UserAccessRights()==usertypeOPERATOR) return false;
#ifdef PROXY
 if(_firstConnector!=this) return false;
#endif 
 return true;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForFullLocalControl()
{
 if(UserAccessRights()==usertypeADMINISTRATOR) return true;
 if(UserAccessRights()==usertypeDEVELOPER)     return true;
 //if(UserAccessRights()==usertypeMANAGER)       return true;
 if(UserAccessRights()==usertypeENGINEER)      return true;
 return false;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForFullRemoteControl()
{
 if(UserAccessRights()==usertypeADMINISTRATOR) return true;
 if(UserAccessRights()==usertypeDEVELOPER)     return true;
 if(UserAccessRights()==usertypeENGINEER)      return true;
 return false;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForManagement()
{
 if(UserAccessRights()==usertypeADMINISTRATOR) return true;
 return false;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForHiddenOptions()
{
 if(UserAccessRights()==usertypeDEVELOPER) return true;
 return false;
}

//---------------------------------------------------------------------------
bool TNodeConnector::AccessForConfiguring()
{
 if(UserAccessRights()==usertypeADMINISTRATOR) return true;
 if(UserAccessRights()==usertypeDEVELOPER)     return true;
 if(UserAccessRights()==usertypeENGINEER)     return true;
 return false;
}

//-----------------------
/*

bool AccessForRunning(TLink *link)
{
 if(link==NULL) return false;
 return AccessForRunning((TNodeConnector *)link->Server());
}
bool AccessForCommonMonitor(TLink *link)
{
 if(link==NULL) return false;
 return AccessForCommonMonitor((TNodeConnector *)link->Server());
}
bool AccessForSimpleControl(TLink *link)
{
 if(link==NULL) return false;
 return AccessForSimpleControl((TNodeConnector *)link->Server());
}
bool AccessForCommonLocalControl(TLink *link)
{
 if(link==NULL) return false;
 return AccessForCommonLocalControl((TNodeConnector *)link->Server());
}
bool AccessForCommonRemoteControl(TLink *link)
{
 if(link==NULL) return false;
 return AccessForCommonRemoteControl((TNodeConnector *)link->Server());
}
bool AccessForFullLocalControl(TLink *link)
{
 if(link==NULL) return false;
 return AccessForFullLocalControl((TNodeConnector *)link->Server());
}
bool AccessForFullRemoteControl(TLink *link)
{
 if(link==NULL) return false;
 return AccessForFullRemoteControl((TNodeConnector *)link->Server());
}
bool AccessForManagement(TLink *link)
{
 if(link==NULL) return false;
 return AccessForManagement((TNodeConnector *)link->Server());
}
bool AccessForHiddenOptions(TLink *link)
{
 if(link==NULL) return false;
 return AccessForHiddenOptions((TNodeConnector *)link->Server());
}
bool AccessForConfiguring(TLink *link)
{
 if(link==NULL) return false;
 return AccessForConfiguring((TNodeConnector *)link->Server());
}

*/
