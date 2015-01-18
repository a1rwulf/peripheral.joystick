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
#pragma once

#include "xbmc_peripheral_utils.hpp"

#include <map>
#include <stdint.h>
#include <string>

namespace ADDON
{
  // TODO
  typedef std::map<JOYSTICK_ID, std::string> ButtonLabels;
  typedef std::map<JOYSTICK_ID, std::string> ButtonColors;
  typedef std::map<JOYSTICK_ID, std::string> ButtonIcons;
}

namespace JOYSTICK
{
  class IPersistentJoystick
  {
  public:
    virtual ~IPersistentJoystick(void) { }

    virtual std::string Name(void) = 0;
    virtual std::string Provider(void) = 0;
    virtual uint16_t    VendorID(void) = 0;
    virtual uint16_t    ProductID(void) = 0;
    virtual std::string Icon(void) = 0;
    virtual std::string Diagram(void) = 0;
    virtual void        GetButtonMap(ADDON::ButtonMap& buttonMap) = 0;
    virtual void        GetButtonLabels(ADDON::ButtonLabels& labels) = 0;
    virtual void        GetButtonColors(ADDON::ButtonColors& colors) = 0;
    virtual void        GetButtonIcons(ADDON::ButtonIcons& icons) = 0;

    virtual void SetName(const std::string& name) = 0;
    virtual void SetProvider(const std::string& provider) = 0;
    virtual void SetVendorID(uint16_t vendorId) = 0;
    virtual void SetProductID(uint16_t productId) = 0;
    virtual void SetIcon(const std::string& name) = 0;
    virtual void SetDiagram(const std::string& name) = 0;
    virtual void SetButtonMap(const ADDON::ButtonMap& buttonMap) = 0;
    virtual void SetButtonLabels(const ADDON::ButtonLabels& labels) = 0;
    virtual void SetButtonColors(const ADDON::ButtonColors& colors) = 0;
    virtual void SetButtonIcons(const ADDON::ButtonIcons& icons) = 0;
  };
}
