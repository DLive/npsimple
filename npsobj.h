#ifndef _NPSOBJ_H_
#define _NPSOBJ_H_

#include "npapi.h"
#include "npruntime.h"
#include "npsobjbase.h"

class ScriptablePluginObject : public ScriptablePluginObjectBase
{
public:
    ScriptablePluginObject(NPP npp)
        : ScriptablePluginObjectBase(npp)
    {
    }

    virtual bool HasMethod(NPIdentifier name);
    virtual bool HasProperty(NPIdentifier name);
    virtual bool GetProperty(NPIdentifier name, NPVariant *result);
    virtual bool Invoke(NPIdentifier name, const NPVariant *args,
        uint32_t argCount, NPVariant *result);
    virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
        NPVariant *result);
};

NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *aClass);


DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject,
                                 AllocateScriptablePluginObject);

#endif