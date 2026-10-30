/**
 * WinDoesNot desktop integration: read the shared desktop preferences file
 * (~/.config/quickshell/default/settings.txt) the same way the other
 * WinDoesNot apps (store, bluetooth, network) do, so dark/light mode and
 * language follow the system setting instead of KDE's own (unused here,
 * no color-schemes installed) scheme files.
 */
#pragma once

#include <QString>

namespace windoesnot {

struct DesktopPrefs {
  bool darkModeSet = false;
  bool dark = false;
  QString language;  // "de" or "en", empty if not set
};

DesktopPrefs read_prefs();

}  // namespace windoesnot
