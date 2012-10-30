
#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "npapi.h"
#include "npruntime.h"


class CPlugin
{
private:
  NPP m_pNPInstance;

#ifdef XP_WIN
  HWND m_hWnd; 
#endif

  NPWindow * m_Window;
  NPStream * m_pNPStream;
  NPObject * m_pScriptableObject;
  NPBool     m_bInitialized;

public:
  char m_String[128];

public:
  CPlugin(NPP pNPInstance);
  ~CPlugin();

  void shut();

  int16_t handleEvent(void* event);

  NPObject *GetScriptableObject();
};

#endif // __PLUGIN_H__
