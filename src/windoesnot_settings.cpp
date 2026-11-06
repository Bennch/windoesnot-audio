#include "windoesnot_settings.hpp"

#include <QColor>
#include <QDir>
#include <QFile>
#include <QRegularExpression>
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
    } else if (key == "accentColor") {
      static const QRegularExpression hex(QStringLiteral("^#[0-9a-fA-F]{6}$"));
      if (hex.match(value).hasMatch()) {
        prefs.accent = value.toLower();
      }
    }
  }

  return prefs;
}


QStringList ui_languages(const DesktopPrefs& prefs) {
  const QString lang = prefs.language.trimmed().toLower();

  if (lang.isEmpty() || lang == "c" || lang == "posix") {
    return {};
  }

  if (lang.startsWith("de")) {
    return {QStringLiteral("de")};
  }

  // Anything else is English, which is the language the strings are written in.
  return {QStringLiteral("C")};
}

namespace {

// The accent colour used in the shipped schemes.
const QString default_accent_rgb = QStringLiteral("254,111,45");

QString schemes_dir() {
  return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/color-schemes";
}

// Writes "<base>Accent.colors" next to the user's schemes: the shipped scheme
// with the desktop accent colour in place of the default orange.
bool write_accent_scheme(const QString& base, const QString& accent_rgb) {
  const QString template_path = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                                       QStringLiteral("color-schemes/%1.colors").arg(base));

  QFile in(template_path);

  if (template_path.isEmpty() || !in.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }

  QString text = QString::fromUtf8(in.readAll());

  text.replace(default_accent_rgb, accent_rgb);
  text.replace(QStringLiteral("ColorScheme=%1\n").arg(base), QStringLiteral("ColorScheme=%1Accent\n").arg(base));

  QDir().mkpath(schemes_dir());

  QFile out(QStringLiteral("%1/%2Accent.colors").arg(schemes_dir(), base));

  if (out.open(QIODevice::ReadOnly) && out.readAll() == text.toUtf8()) {
    return true;  // already up to date, keep the file untouched
  }

  out.close();

  if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
    return false;
  }

  out.write(text.toUtf8());

  return true;
}

}  // namespace

QString prepare_color_scheme(const DesktopPrefs& prefs) {
  if (!prefs.darkModeSet) {
    return {};
  }

  QString accent_rgb = default_accent_rgb;

  if (!prefs.accent.isEmpty()) {
    const QColor color(prefs.accent);

    accent_rgb = QStringLiteral("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue());
  }

  // Both variants are written so that switching light/dark later finds its scheme.
  const bool dark_ok = write_accent_scheme(QStringLiteral("WinDoesNotDark"), accent_rgb);
  const bool light_ok = write_accent_scheme(QStringLiteral("WinDoesNotLight"), accent_rgb);

  const QString base = prefs.dark ? QStringLiteral("WinDoesNotDark") : QStringLiteral("WinDoesNotLight");
  const bool ok = prefs.dark ? dark_ok : light_ok;

  return ok ? base + QStringLiteral("Accent") : base;
}

}  // namespace windoesnot
