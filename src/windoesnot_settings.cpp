#include "windoesnot_settings.hpp"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

namespace windoesnot {

DesktopPrefs read_prefs() {
  DesktopPrefs prefs;

  QString config_home = qEnvironmentVariable("XDG_CONFIG_HOME");
  if (config_home.isEmpty()) {
    config_home = QDir::homePath() + "/.config";
  }

  QFile file(config_home + "/quickshell/default/settings.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return prefs;
  }

  QTextStream in(&file);
  while (!in.atEnd()) {
    const QString line = in.readLine();
    const int eq = line.indexOf('=');
    if (eq < 0) {
      continue;
    }
    const QString key = line.left(eq).trimmed();
    const QString value = line.mid(eq + 1).trimmed();

    if (key == "darkMode") {
      prefs.darkModeSet = true;
      prefs.dark = (value != "false");
    } else if (key == "uiLanguage") {
      prefs.language = value;
    }
  }

  fprintf(stderr, "[windoesnot] settings path=%s darkModeSet=%d dark=%d\n",
          qPrintable(file.fileName()), prefs.darkModeSet, prefs.dark);
  return prefs;
}

}  // namespace windoesnot
