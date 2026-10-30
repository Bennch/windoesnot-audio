# WinDoesNot fork of easyeffects, rebranded (me.windoesnot.Audio) with a
# WinDoesNot dark color scheme. See WINDOESNOT-INTEGRATION.md.
# Upstream: https://github.com/wwmm/easyeffects

pkgname=windoesnot-audio
pkgver=8.3.1
pkgrel=1
pkgdesc='Audio effects, equalizer and filters for WinDoesNot'
arch=(x86_64)
url='https://github.com/Bennch/windoesnot-audio'
license=('GPL3')
depends=(
  'kcolorscheme'
  'kirigami'
  'kirigami-addons'
  'kiconthemes'
  'kconfigwidgets'
  'qqc2-desktop-style'
  'breeze-icons'
  'qt6-base'
  'qt6-graphs'
  'pipewire-pulse'
  'lilv'
  'libsndfile'
  'zita-convolver'
  'libebur128'
  'rnnoise'
  'soundtouch'
  'libbs2b'
  'nlohmann-json'
  'tbb'
  'speexdsp'
  'gsl'
  'webrtc-audio-processing'
  'libmysofa'
)
makedepends=('cmake' 'extra-cmake-modules' 'git' 'ninja' 'intltool' 'appstream' 'mold' 'ladspa')
optdepends=('calf: exciter, bass enhancer and others'
            'lsp-plugins-lv2: limiter, equalizer, compressor, loudness and others'
            'zam-plugins-lv2: maximizer'
            'mda.lv2: bass loudness'
            'x42-plugins-lv2: autotune'
            'libdeep_filter_ladspa: deep noise remover'
            'hush-mic: DPDFNet noise remover'
            'rakarrack-plus: harmonizer'
            'breeze: kde breeze style')
conflicts=(easyeffects)
provides=(easyeffects)
replaces=('pulseeffects')
source=()
sha256sums=()

build() {
  cd "$pkgname-$pkgver"
  cmake \
    -B build \
    -S . \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX:PATH='/usr' \
    -Wno-dev
  cmake --build build
}

package() {
  cd "$pkgname-$pkgver"
  DESTDIR="${pkgdir}" cmake --install build
}
