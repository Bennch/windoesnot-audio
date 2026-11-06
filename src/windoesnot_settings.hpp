/**
 * WinDoesNot desktop integration: read the shared desktop preferences file
 * (~/.config/quickshell/default/settings.txt) the same way the other
 * WinDoesNot apps (store, bluetooth, network) do, so dark/light mode and
 * language follow the system setting instead of KDE's own (unused here,
 * no color-schemes installed) scheme files.
 */
#pragma once

#include <QString>
#include <QStringList>

namespace windoesnot {

struct DesktopPrefs {
  bool darkModeSet = false;
  bool dark = false;
  QString language;  // "de" or "en", empty if not set
  QString accent;    // validated "#rrggbb", empty if not set
};

DesktopPrefs read_prefs();

/**
 * Languages for KLocalizedString from the desktop setting (German, or English
 * = the source language "C"). Empty when the setting is absent, so the system
 * language applies.
 */
QStringList ui_languages(const DesktopPrefs& prefs);

/**
 * Writes the WinDoesNot colour schemes with the desktop accent colour into the
 * user's colour-scheme directory and returns the id to activate for the
 * desktop's light/dark setting (empty when dark/light is not set).
 * Call this before KColorSchemeManager is first used so it finds the files.
 */
QString prepare_color_scheme(const DesktopPrefs& prefs);

}  // namespace windoesnot
