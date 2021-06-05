# Penguin Subtitle Player [![GitHub release](https://img.shields.io/github/release/carsonip/Penguin-Subtitle-Player.svg)](https://github.com/carsonip/Penguin-Subtitle-Player/releases) [![Build Status](https://travis-ci.com/carsonip/Penguin-Subtitle-Player.svg?branch=master)](https://travis-ci.com/github/carsonip/Penguin-Subtitle-Player) [![SourceForge](https://img.shields.io/sourceforge/dt/PenguinSubtitlePlayer.svg)](https://sourceforge.net/projects/penguinsubtitleplayer/) [![Github All Releases](https://img.shields.io/github/downloads/carsonip/Penguin-Subtitle-Player/total.svg)](https://github.com/carsonip/Penguin-Subtitle-Player/releases) [![penguin-subtitle-player](https://snapcraft.io//penguin-subtitle-player/badge.svg)](https://snapcraft.io/penguin-subtitle-player)

Penguin Subtitle Player is an open-source, cross-platform standalone subtitle player, as an alternative to [Greenfish Subtitle Player](http://www.softpedia.com/get/Multimedia/Video/Other-VIDEO-Tools/Greenfish-Subtitle-Player.shtml), [SrtViewer (Mac)](https://sourceforge.net/projects/srtviewer/), [SRTPlayer](https://sourceforge.net/projects/subtitleplayer/), [JustSubsPlayer](https://justsubsplayer.codeplex.com/) and [Free Subtitle Player](http://sourceforge.net/projects/freesubtitleplayer/).

You download the subtitle file (`.srt`, `.ssa`, `.ass`, `.vtt`) from any sites you like and load it into the subtitle player. The subtitle player provides a translucent window which always stays on the top so that subtitles can be shown on top of the video without blocking anything.

With Penguin Subtitle Player, just open your favorite online streaming site, load the subtitle file into the player, and enjoy.

![Screenshot 1](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/Windows_03.png)
![Screenshot 2](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/Windows_00.png)
![Screenshot 3](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/Arch%20Linux_01.png)

## Features

* 700+ encoding supported (default: UTF8)
* Auto encoding detection (See [uchardet](https://www.freedesktop.org/wiki/Software/uchardet/) website for supported encodings)
* Multiple subtitle formats supported (`.srt`, `.ssa`, `.ass`, `.vtt`)
* Drag & drop file
* Customizable layout (Frame size, Background color & Opacity, Font style)
* Time fine tuning (Fast forward / backward with customizable time interval)
* Skip to specified time (by clicking on the time display)
* Skip to previous / next subtitle

## Download

To download the latest version of Penguin Subtitle Player for Windows, macOS (aka Mac OS X), and Linux, visit one of the download mirrors:

* [SourceForge](https://sourceforge.net/projects/penguinsubtitleplayer/)
* [GitHub Release](https://github.com/carsonip/Penguin-Subtitle-Player/releases)

For Linux, it is recommended to download from your package manager instead of using the standalone version.

* [![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-white.svg)](https://snapcraft.io/penguin-subtitle-player)

* [Arch Linux](https://aur.archlinux.org/packages/penguin-subtitle-player-git/)

## Installation

No installation required.

## Release Notes

See [GitHub Release](https://github.com/carsonip/Penguin-Subtitle-Player/releases).

## FAQ

#### Q: "MSVCP120.dll is missing from your computer." on Windows
A: Download and install [Visual C++ Redistributable for Visual Studio 2012](http://www.microsoft.com/download/details.aspx?id=30679)

#### Q: Does it show on the top of both HTML5 fullscreen and Flash fullscreen players?
A: It is tested and confirmed working in Windows, Linux and macOS for both HTML5 and Flash.

#### Q: Why does the transparency/opacity feature not work for me on Linux?
A: You need to have a [compositing window manager](https://github.com/carsonip/Penguin-Subtitle-Player/issues/19) set up and enabled.

## Developing

To develop, see [DEVELOPMENT.md](DEVELOPMENT.md).

## Credits

Carson Ip, LMH, Kwanjai

## License

Code released under the GNU General Public License version 3.

## Alternatives

Alternative Subtitle Players:

* [Subtitle Buddy](https://github.com/vincemann/Subtitle-Buddy)
