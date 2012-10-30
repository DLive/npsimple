////////////////////////////////////////////////////////////
//
// Implementation of plugin entry points (NPP_*)
// most are just empty stubs for this particular plugin
//

#ifdef XP_WIN
#include <windows.h>
#include <windowsx.h>
#endif

#include "plugin.h"
#include "mylog.h"

char*
NPP_GetMIMEDescription(void)
{
  MYDBG(LF, "NPP_GetMIMEDescription");

  //this function is valid in unix and macos
  //format: "mimetype:postfix:description;mimetype:postfix:description"
  return "application/npsimple:*:npplugin simple code";
}

NPError 
NPP_Initialize(void)
{
  MYDBG(LF, "NPP_Initialize");

  return NPERR_NO_ERROR;
}

void 
NPP_Shutdown(void)
{
  MYDBG(LF, "NPP_Shutdown");
}

// here the plugin creates an instance of our CPlugin object which
// will be associated with this newly created plugin instance and
// will do all the neccessary job
NPError 
NPP_New(NPMIMEType pluginType,
        NPP instance,
        uint16_t mode,
        int16_t argc,
        char* argn[],
        char* argv[],
        NPSavedData* saved)
{
  MYDBG(LF, "NPP_New");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  CPlugin * pPlugin = new CPlugin(instance);
  if(pPlugin == NULL)
    return NPERR_OUT_OF_MEMORY_ERROR;

  instance->pdata = (void *)pPlugin;
  return rv;
}

// here is the place to clean up and destroy the CPlugin object
NPError 
NPP_Destroy (NPP instance, NPSavedData** save)
{
  MYDBG(LF, "NPP_Destroy");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  CPlugin * pPlugin = (CPlugin *)instance->pdata;
  if(pPlugin != NULL) {
    pPlugin->shut();
    delete pPlugin;
  }
  return rv;
}

// during this call we know when the plugin window is ready or
// is about to be destroyed so we can do some gui specific
// initialization and shutdown
NPError 
NPP_SetWindow (NPP instance, NPWindow* pNPWindow)
{
  MYDBG(LF,"NPP_SetWindow");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  return rv;
}

// ==============================
// ! Scriptability related code !
// ==============================
//
// here the plugin is asked by Mozilla to tell if it is scriptable
// we should return a valid interface id and a pointer to
// nsScriptablePeer interface which we should have implemented
// and which should be defined in the corressponding *.xpt file
// in the bin/components folder
NPError	
NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
  MYDBG(LF,"NPP_GetValue value = %d", variable);

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;

  if(instance == NULL)
    return NPERR_GENERIC_ERROR;

  CPlugin * plugin = (CPlugin *)instance->pdata;
  if(plugin == NULL)
    return NPERR_GENERIC_ERROR;

  switch (variable) {
  case NPPVpluginNameString:
    *((char **)value) = "NPRuntimeTest";
    break;
  case NPPVpluginDescriptionString:
    *((char **)value) = "NPRuntime scriptability API test plugin";
    break;

  case NPPVpluginNeedsXEmbed:
    *((NPBool *)value) = 1;  //otherwise the chrome on ubuntu dosn't work!
    break;

  // Here we indicate that the plugin is scriptable. See this page for details:
  // https://developer.mozilla.org/en/Gecko_Plugin_API_Reference/Scripting_plugins
  case NPPVpluginScriptableNPObject:
    *(NPObject **)value = plugin->GetScriptableObject();
    break;
  default:
    rv = NPERR_GENERIC_ERROR;
  }

  return rv;
}

NPError 
NPP_NewStream(NPP instance,
              NPMIMEType type,
              NPStream* stream,
              NPBool seekable,
              uint16_t* stype)
{
  MYDBG(LF, "NPP_NewStream");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;
  return rv;
}

int32_t 
NPP_WriteReady (NPP instance, NPStream *stream)
{
  MYDBG(LF, "NPP_WriteReady");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  int32_t rv = 0x0fffffff;
  return rv;
}

int32_t 
NPP_Write (NPP instance, NPStream *stream, int32_t offset, int32_t len, void *buffer)
{
  MYDBG(LF, "NPP_Write");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  int32_t rv = len;
  return rv;
}

NPError 
NPP_DestroyStream (NPP instance, NPStream *stream, NPError reason)
{
  MYDBG(LF, "NPP_DestroyStream");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;
  return rv;
}

void 
NPP_StreamAsFile (NPP instance, NPStream* stream, const char* fname)
{
  MYDBG(LF, "NPP_StreamAsFile");

  if(instance == NULL)
    return;
}

void 
NPP_Print (NPP instance, NPPrint* printInfo)
{
  MYDBG(LF, "NPP_Print");

  if(instance == NULL)
    return;
}

void 
NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
  MYDBG(LF, "NPP_URLNotify");

  if(instance == NULL)
    return;
}

NPError 
NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
  MYDBG(LF, "NPP_SetValue");

  if(instance == NULL)
    return NPERR_INVALID_INSTANCE_ERROR;

  NPError rv = NPERR_NO_ERROR;
  return rv;
}

int16_t
NPP_HandleEvent(NPP instance, void* event)
{
  MYDBG(LF, "NPP_HandleEvent");

  if(instance == NULL)
    return 0;

  int16_t rv = 0;
  CPlugin * pPlugin = (CPlugin *)instance->pdata;
  if (pPlugin)
    rv = pPlugin->handleEvent(event);

  return rv;
}

/*
NPObject *NPP_GetScriptableInstance(NPP instance)
{
  if(!instance)
    return 0;

  NPObject *npobj = 0;
  CPlugin * pPlugin = (CPlugin *)instance->pdata;
  if (pPlugin)
    npobj = pPlugin->GetScriptableObject();

  return npobj;
}

*/
