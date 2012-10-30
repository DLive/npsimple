////////////////////////////////////////////
/// ScriptablePluginObject class implementation
#ifdef XP_WIN
#include <windows.h>
#include <windowsx.h>
#endif

#ifdef XP_MAC
#include <TextEdit.h>
#endif

#ifdef XP_UNIX
#include <string.h>
#endif

#include "npsobj.h"
#include "mylog.h"


static NPIdentifier sfnamea_id;// = NPN_GetStringIdentifier("somefuction");
static NPIdentifier sfnameb_id;// = NPN_GetStringIdentifier("otherfunction");
static NPIdentifier spnamea_id;// = NPN_GetStringIdentifier("someproperty");
static NPIdentifier sftest_id;  

NPObject *
AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
  MYDBG(LF, "AllocateScriptablePluginObject");

  //sfnamea_id = NPN_GetStringIdentifier("somefuction");
  //sfnameb_id = NPN_GetStringIdentifier("otherfunction");
  //spnamea_id = NPN_GetStringIdentifier("someproperty");
  sftest_id  = NPN_GetStringIdentifier("test");  
  return new ScriptablePluginObject(npp);
}


bool
ScriptablePluginObject::HasMethod(NPIdentifier name)
{
  //MYDBG(LF, "ScriptablePluginObject::HasMethod");

  return (name == sftest_id ||
        name == sfnameb_id );
}
bool
ScriptablePluginObject::HasProperty(NPIdentifier name)
{
  //MYDBG(LF, "ScriptablePluginObject::HasProperty");

    return (name == spnamea_id ||
        name == spnamea_id);
	
}

bool
ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
 // MYDBG(LF, "ScriptablePluginObject::GetProperty");

    VOID_TO_NPVARIANT(*result);

    //if (name == spnamea_id) {
    //    static int a = 0;

    //    INT32_TO_NPVARIANT(a, *result);

    //    a += 5;

    //    return true;
    //}

    return true;
}


bool
ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args,
                               uint32_t argCount, NPVariant *result)
{
  MYDBG(LF, "ScriptablePluginObject::Invoke");
  if(name == sftest_id)
  {
		MessageBox(NULL,L"HAHA",L"haha",0);
		return true;
  }
  /*else if (name == sfnamea_id)
  {
    const char* outString = "somefunction method return val";
    char* npOutString = (char *)NPN_MemAlloc(strlen(outString) + 1);
    if (!npOutString)
      return false;
    strcpy(npOutString, outString);
    STRINGZ_TO_NPVARIANT(npOutString, *result);
    return true;
  }
  else if (name == sfnameb_id)
  {
    const char* outString = "otherfunction method return val";
    char* npOutString = (char *)NPN_MemAlloc(strlen(outString) + 1);
    if (!npOutString)
      return false;
    strcpy(npOutString, outString);
    STRINGZ_TO_NPVARIANT(npOutString, *result);
    return true;
  }*/
  return false;
}

bool
ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount,
                                      NPVariant *result)
{
  MYDBG(LF, "ScriptablePluginObject::InvokeDefault");

  const char* outString = "default method return val";
  char* npOutString = (char *)NPN_MemAlloc(strlen(outString) + 1);
  if (!npOutString)
      return false;
  strcpy(npOutString, outString);
  STRINGZ_TO_NPVARIANT(npOutString, *result);

  return true;
}