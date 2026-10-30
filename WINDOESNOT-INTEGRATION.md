# EasyEffects → WinDoesNot Audio Integration

**Status**: App ID/branding rebrand done (commit b7af93b). Build/test NOT yet run.  
**Date**: 2026-10-30

## Done

- APPLICATION_ID/NAME: `me.windoesnot.Audio`
- D-Bus bus name + object paths rebranded in `src/tags_app.hpp`
- desktop.in, metainfo.xml.in, all icon svgs renamed
- `src/contents/CMakeLists.txt` install() rules updated to match

## Deliberately skipped (documented, not blocking)

- Binary target name stays `easyeffects` internally (17+ CMake call sites
  in src/CMakeLists.txt). Zero user-visible impact — desktop Exec= already
  points to it. Rename later if desired, low priority.
- metainfo.xml.in description/developer/license text left as upstream
  (GPL attribution requirement for a fork, not a rewrite).

## NOT done yet

- No build attempted — verify CMake config succeeds with new names
- CSS/QML theming to match WinDoesNot colors/radius
- Locale: check existing po/ files, no de/en-specific work done

## Current State

- Upstream easyeffects v8.3.1 cloned to `/home/benni/Projekte/WinDoesNot/audio/`
- CMake-based C++20/Qt6 project
- Ready for WinDoesNot branding & integration

## Next Steps (After ISO Test)

### Step 1: Configure CMake for WinDoesNot

Edit `CMakeLists.txt`:
```cmake
set(APPLICATION_DOMAIN "windoesnot-audio")
set(COMPONENT_NAME "windoesnot-audio")
set(ORGANIZATION_NAME "WinDoesNot")
set(ORGANIZATION_DOMAIN "windoesnot.me")
set(APPLICATION_ID "com.windoesnot.Audio")
set(APPLICATION_NAME "WinDoesNot Audio")
```

### Step 2: Branding Files

Create:
- `data/com.windoesnot.Audio.desktop.in`
- `data/com.windoesnot.Audio.metainfo.xml`
- `data/icons/` → WinDoesNot-styled icons (22x22, 64x64, 128x128)

### Step 3: Localization Setup

Existing easyeffects uses Qt Linguist (`.ts` files):
- Check `src/translations/` structure
- Add de/en translations
- Integrate with meson/CMake build

### Step 4: CSS Theming

Qt stylesheets in qss files:
- Match WinDoesNot button style (10px radius, orange accent)
- Match Settings app colors (dark/light mode support)
- Test with Settings app theme toggle

### Step 5: PKGBUILD Wrapper

Create `packaging/windoesnot-audio-PKGBUILD.in`:
- Depends: qt6-base, qt6-declarative, qt6-svg, pipewire
- Install to `/usr/bin/windoesnot-audio`
- Desktop file to `/usr/share/applications/`

### Step 6: ISO Integration

1. Add to `sources.json` with commit pin
2. Add to `iso/packages-extra.txt`
3. Create desktop launcher or Settings panel toggle

## Build Commands (Reference)

```bash
cmake -B build
cmake --build build
cmake --install build --prefix /usr
```

## Key Files to Modify

- `CMakeLists.txt` - App IDs, organization
- `src/` - C++ code (minimal changes needed)
- `src/ui/` - QML/UI files (styling)
- `src/translations/` - i18n (de.ts, en.ts)
- `data/` - Desktop, icons, metadata

## Notes

- easyeffects has very active upstream → periodic rebases needed
- Qt6 theming is straightforward (CSS-like)
- PipeWire integration already complete
- No custom Rust/GTK knowledge needed - Qt/C++ similar across WinDoesNot apps

## Blocked By

- [ ] New ISO test and validation
- [ ] Confirmation of audio integration approach (standalone vs. Settings panel)
