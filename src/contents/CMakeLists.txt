install(FILES
    icons/${APPLICATION_ID}.svg
    DESTINATION ${KDE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps
)

install(FILES
    icons/me.windoesnot.Audio-symbolic.svg
    icons/me.windoesnot.Audio-off-symbolic.svg
    DESTINATION ${KDE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps
)

configure_file(me.windoesnot.Audio.metainfo.xml.in
    me.windoesnot.Audio.metainfo.xml.in
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/me.windoesnot.Audio.metainfo.xml.in
    DESTINATION ${KDE_INSTALL_METAINFODIR}
    RENAME ${APPLICATION_ID}.metainfo.xml
)

configure_file(me.windoesnot.Audio.desktop.in
    me.windoesnot.Audio.desktop.in
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/me.windoesnot.Audio.desktop.in
    DESTINATION ${KDE_INSTALL_APPDIR}
    RENAME ${APPLICATION_ID}.desktop
)

# Proper KDE theming path: a real color-scheme file Kirigami/KColorSchemeManager
# can activate, instead of forcing QPalette by hand (which Kirigami QML content
# only partially follows). See src/windoesnot_settings.cpp / main.cpp.
install(FILES
    color-schemes/WinDoesNotDark.colors
    color-schemes/WinDoesNotLight.colors
    DESTINATION ${KDE_INSTALL_FULL_DATADIR}/color-schemes
)
