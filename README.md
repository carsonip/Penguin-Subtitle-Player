# Penguin Subtitle Player [![GitHub release](https://img.shields.io/github/release/carsonip/Penguin-Subtitle-Player.svg)](https://github.com/carsonip/Penguin-Subtitle-Player/releases) [![Build Status](https://travis-ci.org/carsonip/Penguin-Subtitle-Player.svg?branch=master)](https://travis-ci.org/carsonip/Penguin-Subtitle-Player) [![SourceForge](https://img.shields.io/sourceforge/dt/PenguinSubtitlePlayer.svg)](https://sourceforge.net/projects/penguinsubtitleplayer/) [![Github All Releases](https://img.shields.io/github/downloads/carsonip/Penguin-Subtitle-Player/total.svg)](https://github.com/carsonip/Penguin-Subtitle-Player/releases) [![penguin-subtitle-player](https://snapcraft.io//penguin-subtitle-player/badge.svg)](https://snapcraft.io/penguin-subtitle-player)

Penguin Subtitle Player is an open-source, cross-platform standalone subtitle player, as an alternative to [Greenfish Subtitle Player](http://www.softpedia.com/get/Multimedia/Video/Other-VIDEO-Tools/Greenfish-Subtitle-Player.shtml), [SrtViewer (Mac)](https://sourceforge.net/projects/srtviewer/), [SRTPlayer](https://sourceforge.net/projects/subtitleplayer/), [JustSubsPlayer](https://justsubsplayer.codeplex.com/) and [Free Subtitle Player](http://sourceforge.net/projects/freesubtitleplayer/).

You download the subtitle file (`.srt`, `.ssa`, `.ass`) from any sites you like and load it into the subtitle player. The subtitle player provides a translucent window which always stays on the top so that subtitles can be shown on top of the video without blocking anything.

With Penguin Subtitle Player, just open your favorite online streaming site, load the subtitle file into the player, and enjoy.

![Screenshot 1](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/Windows_03.png)
![Screenshot 2](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/Windows_00.png)
![Screenshot 3](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/Arch%20Linux_01.png)

## Features

* 700+ encoding supported (default: UTF8)
* Auto encoding detection
* Multiple subtitle formats supported (`.srt`, `.ssa`, `.ass`)
* Drag & drop file
* Customizable layout (Frame size, Background color & Opacity, Font style)
* Time fine tuning (Fast forward / backward with customizable time interval)
* Skip to specified time (by clicking on the time display)
* Skip to previous / next subtitle

## Download

To download the latest version of Penguin Subtitle Player for Windows, macOS (aka Mac OS X), and Linux, visit one of the download mirrors:

* [SourceForge](https://sourceforge.net/projects/penguinsubtitleplayer/)
* [GitHub Release](https://github.com/carsonip/Penguin-Subtitle-Player/releases)

For Linux, it is recommended to download from your package manager instead of using the standalone version. There is also a snap available:

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-white.svg)](https://snapcraft.io/penguin-subtitle-player)

* Ubuntu

```
sudo add-apt-repository ppa:nilarimogard/webupd8
sudo apt update
sudo apt install penguin-subtitle-player
```
* [Arch Linux](https://aur.archlinux.org/packages/penguin-subtitle-player-git/)

## Release Notes

See [GitHub Release](https://github.com/carsonip/Penguin-Subtitle-Player/releases).

## Installation

No installation required.

## FAQ

#### Q: "MSVCP120.dll is missing from your computer." on Windows
A: Download and install [Visual C++ Redistributable for Visual Studio 2012](http://www.microsoft.com/download/details.aspx?id=30679)

#### Q: Does it show on the top of both HTML5 fullscreen and Flash fullscreen players?
A: It is tested and confirmed working in Windows, Linux and Mac OSX for both HTML5 and Flash.

#### Q: Why does the transparency/opacity feature not work for me on Linux?
A: You need to have a [compositing window manager](https://github.com/carsonip/Penguin-Subtitle-Player/issues/19) set up and enabled.

## Developing

Penguin Subtitle Player is a Qt5 project. The executables include statically compiled Qt libraries.

#### Code formatting

This project uses ClangFormat. To format the code in this project, run:

```bash
find . -path "./src/libcharsetdetect" -prune -o \( -name '*.h' -o -name '*.cpp' \) -print | xargs clang-format -i -style=llvm
```

#### Libraries
* [uchardet-enhanced](https://bitbucket.org/medoc/uchardet-enhanced): Auto charset detection. 

#### Compilers

* Windows: VC++ 2012
* Linux: G++
* Mac OSX: G++

Check [here](http://doc.qt.io/qt-5/deployment.html) for deployment details.

## Building

#### The easy way

1. Download Qt with Qt Creator [here](http://www.qt.io/download-open-source/)
2. Open the .pro file in Qt Creator
3. You should be good to go (In case of some weird compilation errors, turn off the shadow build option in projects build settings)

#### The hard way

1. Download Qt (Qt Creator is not required) [here](http://www.qt.io/download-open-source/)
2. Run qmake
  ```
  qmake PenguinSubtitlePlayer.pro
  ```
3. Build from the makefile generated by qmake
  * G++ (Linux, Mac OSX): ```make```
  * VC++ (Windows): ```nmake```
  * MinGW (Windows): ```mingw32-make```
4. You should see the executable under ```build/debug``` or ```build/release```

In case you would like to deploy a version which does not require Qt libraries in the client's system, consider statically build Qt then `qmake` with the `static` option, or change the config line in `PenguinSubtitlePlayer.pro` to
```
CONFIG += static \
          c++11
```

## Testing

1. Run `qmake "CONFIG+=test" PenguinSubtitlePlayer.pro`
2. Build from the makefile as described in the Building part
3. Run the executable

Note: This project is using [TravisCI](https://travis-ci.org/carsonip/Penguin-Subtitle-Player) for testing.

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Credits

Carson Ip, LMH, Kwanjai

## License

Code released under the GNU General Public License version 3.

## Alternatives

If Penguin Subtitle Player does not work for you, feel free to try these alternatives:

* [Subtitle Buddy](https://github.com/vincemann/Subtitle-Buddy)
