//////////////////////////////////////////////////
// CPlugin class implementation
//

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

#include <stdio.h>
#include "plugin.h"
#include "npfunctions.h"
#include "npsobjbase.h"
#include "npsobj.h"
#include "mylog.h"



CPlugin::CPlugin(NPP pNPInstance) :
      m_pNPInstance(pNPInstance),
      m_pNPStream(NULL),
      m_bInitialized(false),
      m_pScriptableObject(NULL)
{
  MYDBG(LF, "CPlugin::CPlugin");

#ifdef XP_WIN
  m_hWnd = NULL;
#endif

  pNPInstance->pdata = (void *)this;

}

CPlugin::~CPlugin()
{
  MYDBG(LF, "CPlugin::~CPlugin");

  if (m_pScriptableObject)
    NPN_ReleaseObject(m_pScriptableObject);
}



void 
CPlugin::shut()
{
  MYDBG(LF, "CPlugin::shut");

#ifdef XP_WIN
  m_hWnd = NULL;
#endif

  m_bInitialized = false;
}

int16_t 
CPlugin::handleEvent(void* event)
{
  MYDBG(LF, "CPlugin::handleEvent");

#ifdef XP_MAC
  NPEvent* ev = (NPEvent*)event;
  if (m_Window) {
    Rect box = { m_Window->y, m_Window->x,
                 m_Window->y + m_Window->height, m_Window->x + m_Window->width };
    if (ev->what == updateEvt) {
      ::TETextBox(m_String, strlen(m_String), &box, teJustCenter);
    }
  }
#endif
  return 0;
}


NPObject *
CPlugin::GetScriptableObject()
{
  MYDBG(LF, "CPlugin::GetScriptableObject");
  
  if (!m_pScriptableObject) {
    m_pScriptableObject =
      NPN_CreateObject(m_pNPInstance,
                       GET_NPOBJECT_CLASS(ScriptablePluginObject));
  }

  if (m_pScriptableObject) {
    NPN_RetainObject(m_pScriptableObject);
  }

  return m_pScriptableObject;
}
