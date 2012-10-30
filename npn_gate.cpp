////////////////////////////////////////////////////////////
//
// Implementation of Netscape entry points (NPN_*)
//
#ifdef XP_WIN
#include <windows.h>
#include <windowsx.h>
#endif

#include "npapi.h"
#include "npfunctions.h"
#include "mylog.h"

#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif

#ifndef LOBYTE
#define LOBYTE(W) ((W) & 0xFF)
#endif

extern NPNetscapeFuncs NPNFuncs;

void 
NPN_Version(int* plugin_major, int* plugin_minor, int* netscape_major,
            int* netscape_minor)
{
  MYDBG(LF, "NPN_Version");

  *plugin_major   = NP_VERSION_MAJOR;
  *plugin_minor   = NP_VERSION_MINOR;
  *netscape_major = HIBYTE(NPNFuncs.version);
  *netscape_minor = LOBYTE(NPNFuncs.version);
}

NPError 
NPN_GetURLNotify(NPP instance, const char *url, const char *target, void* notifyData)
{
  MYDBG(LF, "NPN_GetURLNotify");

	int navMinorVers = NPNFuncs.version & 0xFF;
  NPError rv = NPERR_NO_ERROR;

  if( navMinorVers >= NPVERS_HAS_NOTIFICATION )
		rv = NPNFuncs.geturlnotify(instance, url, target, notifyData);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

  return rv;
}

NPError 
NPN_GetURL(NPP instance, const char *url, const char *target)
{
  MYDBG(LF, "NPN_GetURL");

  NPError rv = NPNFuncs.geturl(instance, url, target);
  return rv;
}

NPError 
NPN_PostURLNotify(NPP instance, const char* url, const char* window, uint32_t len,
                  const char* buf, NPBool file, void* notifyData)
{
  MYDBG(LF, "NPN_PostURLNotify");

	int navMinorVers = NPNFuncs.version & 0xFF;
  NPError rv = NPERR_NO_ERROR;

	if( navMinorVers >= NPVERS_HAS_NOTIFICATION )
		rv = NPNFuncs.posturlnotify(instance, url, window, len, buf, file, notifyData);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

  return rv;
}

NPError 
NPN_PostURL(NPP instance, const char* url, const char* window, uint32_t len,
            const char* buf, NPBool file)
{
  MYDBG(LF, "NPN_PostURL");

  NPError rv = NPNFuncs.posturl(instance, url, window, len, buf, file);
  return rv;
}

NPError 
NPN_RequestRead(NPStream* stream, NPByteRange* rangeList)
{
  MYDBG(LF, "NPN_RequestRead");

  NPError rv = NPNFuncs.requestread(stream, rangeList);
  return rv;
}

NPError 
NPN_NewStream(NPP instance, NPMIMEType type, const char* target, NPStream** stream)
{
  MYDBG(LF, "NPN_NewStream");

	int navMinorVersion = NPNFuncs.version & 0xFF;

  NPError rv = NPERR_NO_ERROR;

	if( navMinorVersion >= NPVERS_HAS_STREAMOUTPUT )
		rv = NPNFuncs.newstream(instance, type, target, stream);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

  return rv;
}

int32_t 
NPN_Write(NPP instance, NPStream *stream, int32_t len, void *buffer)
{
  MYDBG(LF, "NPN_Write");

	int navMinorVersion = NPNFuncs.version & 0xFF;
  int32_t rv = 0;

  if( navMinorVersion >= NPVERS_HAS_STREAMOUTPUT )
		rv = NPNFuncs.write(instance, stream, len, buffer);
	else
		rv = -1;

  return rv;
}

NPError 
NPN_DestroyStream(NPP instance, NPStream* stream, NPError reason)
{
  MYDBG(LF, "NPN_DestroyStream");

	int navMinorVersion = NPNFuncs.version & 0xFF;
  NPError rv = NPERR_NO_ERROR;

  if( navMinorVersion >= NPVERS_HAS_STREAMOUTPUT )
		rv = NPNFuncs.destroystream(instance, stream, reason);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

  return rv;
}

void 
NPN_Status(NPP instance, const char *message)
{
  MYDBG(LF, "NPN_Status");

  NPNFuncs.status(instance, message);
}

const char* 
NPN_UserAgent(NPP instance)
{
  MYDBG(LF, "NPN_UserAgent");

  const char * rv = NULL;
  rv = NPNFuncs.uagent(instance);
  return rv;
}

void* 
NPN_MemAlloc(uint32_t size)
{
  MYDBG(LF, "NPN_MemAlloc");

  void * rv = NULL;
  rv = NPNFuncs.memalloc(size);
  return rv;
}

void 
NPN_MemFree(void* ptr)
{
  MYDBG(LF, "NPN_MemFree");

  NPNFuncs.memfree(ptr);
}

uint32_t 
NPN_MemFlush(uint32_t size)
{
  MYDBG(LF, "NPN_MemFlush");

  uint32_t rv = NPNFuncs.memflush(size);
  return rv;
}

void 
NPN_ReloadPlugins(NPBool reloadPages)
{
  MYDBG(LF, "NPN_ReloadPlugins");

  NPNFuncs.reloadplugins(reloadPages);
}

NPError 
NPN_GetValue(NPP instance, NPNVariable variable, void *value)
{
  MYDBG(LF, "NPN_GetValue");

  NPError rv = NPNFuncs.getvalue(instance, variable, value);
  return rv;
}

NPError 
NPN_SetValue(NPP instance, NPPVariable variable, void *value)
{
  MYDBG(LF, "NPN_SetValue");

  NPError rv = NPNFuncs.setvalue(instance, variable, value);
  return rv;
}

void 
NPN_InvalidateRect(NPP instance, NPRect *invalidRect)
{
  MYDBG(LF, "NPN_InvalidateRect");

  NPNFuncs.invalidaterect(instance, invalidRect);
}

void 
NPN_InvalidateRegion(NPP instance, NPRegion invalidRegion)
{
  MYDBG(LF, "NPN_InvalidateRegion");

  NPNFuncs.invalidateregion(instance, invalidRegion);
}

void 
NPN_ForceRedraw(NPP instance)
{
  MYDBG(LF, "NPN_ForceRedraw");

  NPNFuncs.forceredraw(instance);
}

NPIdentifier 
NPN_GetStringIdentifier(const NPUTF8 *name)
{
  MYDBG(LF, "NPN_GetStringIdentifier");

  return NPNFuncs.getstringidentifier(name);
}

void 
NPN_GetStringIdentifiers(const NPUTF8 **names, uint32_t nameCount,
                              NPIdentifier *identifiers)
{
  MYDBG(LF, "NPN_GetStringIdentifiers");

  return NPNFuncs.getstringidentifiers(names, nameCount, identifiers);
}

NPIdentifier 
NPN_GetStringIdentifier(int32_t intid)
{
  MYDBG(LF, "NPN_GetStringIdentifier");

  return NPNFuncs.getintidentifier(intid);
}

bool 
NPN_IdentifierIsString(NPIdentifier identifier)
{
  MYDBG(LF, "NPN_IdentifierIsString");

  return NPNFuncs.identifierisstring(identifier);
}

NPUTF8 *
NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
  MYDBG(LF, "NPN_UTF8FromIdentifier");

  return NPNFuncs.utf8fromidentifier(identifier);
}

int32_t 
NPN_IntFromIdentifier(NPIdentifier identifier)
{
  MYDBG(LF, "NPN_IntFromIdentifier");

  return NPNFuncs.intfromidentifier(identifier);
}

NPObject *
NPN_CreateObject(NPP npp, NPClass *aClass)
{
  MYDBG(LF, "NPN_CreateObject");

  return NPNFuncs.createobject(npp, aClass);
}

NPObject *
NPN_RetainObject(NPObject *obj)
{
  MYDBG(LF, "NPN_RetainObject");

  return NPNFuncs.retainobject(obj);
}

void 
NPN_ReleaseObject(NPObject *obj)
{
  MYDBG(LF, "NPN_ReleaseObject");

  return NPNFuncs.releaseobject(obj);
}

bool 
NPN_Invoke(NPP npp, NPObject* obj, NPIdentifier methodName,
           const NPVariant *args, uint32_t argCount, NPVariant *result)
{
  MYDBG(LF, "NPN_Invoke");

  return NPNFuncs.invoke(npp, obj, methodName, args, argCount, result);
}

bool 
NPN_InvokeDefault(NPP npp, NPObject* obj, const NPVariant *args,
                  uint32_t argCount, NPVariant *result)
{
  MYDBG(LF, "NPN_InvokeDefault");

  return NPNFuncs.invokeDefault(npp, obj, args, argCount, result);
}

bool 
NPN_Evaluate(NPP npp, NPObject* obj, NPString *script,
             NPVariant *result)
{
  MYDBG(LF, "NPN_Evaluate");

  return NPNFuncs.evaluate(npp, obj, script, result);
}

bool 
NPN_GetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
                NPVariant *result)
{
  MYDBG(LF, "NPN_GetProperty");

  return NPNFuncs.getproperty(npp, obj, propertyName, result);
}

bool 
NPN_SetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
                const NPVariant *value)
{
  MYDBG(LF, "NPN_SetProperty");

  return NPNFuncs.setproperty(npp, obj, propertyName, value);
}

bool 
NPN_RemoveProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
  MYDBG(LF, "NPN_RemoveProperty");

  return NPNFuncs.removeproperty(npp, obj, propertyName);
}

bool 
NPN_Enumerate(NPP npp, NPObject *obj, NPIdentifier **identifier,
              uint32_t *count)
{
  MYDBG(LF, "NPN_Enumerate");

  return NPNFuncs.enumerate(npp, obj, identifier, count);
}

bool 
NPN_Construct(NPP npp, NPObject *obj, const NPVariant *args,
              uint32_t argCount, NPVariant *result)
{
  MYDBG(LF, "NPN_Construct");

  return NPNFuncs.construct(npp, obj, args, argCount, result);
}

bool 
NPN_HasProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
  MYDBG(LF, "NPN_HasProperty");

  return NPNFuncs.hasproperty(npp, obj, propertyName);
}

bool 
NPN_HasMethod(NPP npp, NPObject* obj, NPIdentifier methodName)
{
  MYDBG(LF, "NPN_HasMethod");

  return NPNFuncs.hasmethod(npp, obj, methodName);
}

void 
NPN_ReleaseVariantValue(NPVariant *variant)
{
  MYDBG(LF, "NPN_ReleaseVariantValue");

  NPNFuncs.releasevariantvalue(variant);
}

void 
NPN_SetException(NPObject* obj, const NPUTF8 *message)
{
  MYDBG(LF, "NPN_SetException");

  NPNFuncs.setexception(obj, message);
}
