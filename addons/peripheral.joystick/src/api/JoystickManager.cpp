/*
 *      Copyright (C) 2014 Garrett Brown
 *      Copyright (C) 2014 Team XBMC
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "JoystickManager.h"
#include "Joystick.h"
#if defined(HAVE_DIRECT_INPUT)
  #include "directinput/JoystickInterfaceDirectInput.h"
#endif
#if defined(HAVE_XINPUT)
  #include "xinput/JoystickInterfaceXInput.h"
#endif
#if defined(HAVE_LINUX_JOYSTICK)
  #include "linux/JoystickInterfaceLinux.h"
#endif
#if defined(HAVE_SDL)
  #include "sdl/JoystickInterfaceSDL.h"
#endif
#include "log/Log.h"

using namespace ADDON;
using namespace JOYSTICK;
using namespace PLATFORM;

CJoystickManager& CJoystickManager::Get(void)
{
  static CJoystickManager _instance;
  return _instance;
}

bool CJoystickManager::Initialize(void)
{
  CLockObject lock(m_joystickMutex);

#if defined(HAVE_DIRECT_INPUT)
  m_interfaces.push_back(new CJoystickInterfaceDirectInput);
#endif
#if defined(HAVE_XINPUT)
  m_interfaces.push_back(new CJoystickInterfaceXInput);
#endif
#if defined(HAVE_LINUX_JOYSTICK)
  m_interfaces.push_back(new CJoystickInterfaceLinux);
#endif
#if defined(HAVE_SDL)
  m_interfaces.push_back(new CJoystickInterfaceSDL);
#endif

  for (std::map<unsigned int, IJoystick*>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
  {
    if (!it->second->Initialize())
    {
      esyslog("Failed to initialize API");


      CLog::Log(LOGERROR, "%s - failed to initialise bus %s", __FUNCTION__, PeripheralTypeTranslator::BusTypeToString(m_busses.at(iBusPtr)->Type()));

  return !m_joysticks.empty();
}

void CJoystickManager::Deinitialize(void)
{
  CLockObject lock(m_joystickMutex);

  for (std::map<unsigned int, IJoystick*>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
    delete it->second;

  m_joysticks.clear();
}

bool CJoystickManager::PerformDeviceScan(std::vector<PeripheralScanResult>& scanResults)
{
  CLockObject lock(m_joystickMutex);

  bool bReturn(true);

  for (std::map<unsigned int, IJoystick*>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
    bReturn &= (*it)->PerformJoystickScan(scanResults);
  
  return bReturn;
}

bool CJoystickManager::GetJoystickInfo(unsigned int index, ADDON::JoystickInfo& info) const
{
  std::map<unsigned int, IJoystick*>::const_iterator it = m_joysticks.find(index);
  if (it != m_joysticks.end())
  {
    it->second->GetInfo(info);
    return true;
  }
  return false;
}

/*!
* @brief Get all events that have occurred since the last call to GetEvents()
*/
bool CJoystickManager::GetEvents(std::vector<ADDON::PeripheralEvent>& events)
{
  CLockObject lock(m_joystickMutex);

  bool bResult(true);

  for (std::map<unsigned int, IJoystick*>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
    bResult &= it->second->GetEvents(events);

  return bResult;
}
