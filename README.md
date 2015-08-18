# Penguin Subtitle Player

Penguin Subtitle Player is an open-source, cross-platform standalone subtitle player, as an alternative to [Greenfish Subtitle Player](http://greenfish-subtitle-player.en.softonic.com/), [SrtViewer (Mac)](https://sourceforge.net/projects/srtviewer/), [SRTPlayer](https://sourceforge.net/projects/subtitleplayer/), [JustSubsPlayer](https://justsubsplayer.codeplex.com/) and [Free Subtitle Player](http://sourceforge.net/projects/freesubtitleplayer/).

You download the .srt file from any sites you like and load it into the subtitle player. The subtitle player provides a translucent window which always stays on the top so that subtitles can be shown on top of the video without blocking anything.

With Penguin Subtitle Player, just open your favorite online streaming site, load the srt into the player, and enjoy.

![Screenshot 1](https://a.fsdn.com/con/app/proj/penguinsubtitleplayer/screenshots/11087183_10207184638993421_1626182263_o.jpg)

## Features

* 700+ encoding supported (default: UTF8)
* Auto encoding detection
* Drag & drop SRT file
* Customizable layout (Frame size, Background color & Opacity, Font style)
* Time fine tuning (Fast forward / backward with customizable time interval)

## Download

Current Version: 0.2.1
* [Windows](https://sourceforge.net/projects/penguinsubtitleplayer/files/Penguin%20Subtitle%20Player/0.2.1/PenguinSubtitlePlayer-Windows.zip/download)
* [Linux](https://sourceforge.net/projects/penguinsubtitleplayer/files/Penguin%20Subtitle%20Player/0.2.1/PenguinSubtitlePlayer-Linux.tar.gz/download)
* [Mac OS X](https://sourceforge.net/projects/penguinsubtitleplayer/files/Penguin%20Subtitle%20Player/0.2.1/PenguinSubtitlePlayer-OSX.zip/download)

## Installation

No installation required.

## FAQ

#### Q: "MSVCP120.dll is missing from your computer." on Windows
A: Download and install [Visual C++ Redistributable for Visual Studio 2012](http://www.microsoft.com/download/details.aspx?id=30679)

#### Q: Does it show on the top of both HTML5 fullscreen and Flash fullscreen players?
A: It is tested and confirmed working in Windows, Linux and Mac OSX for both HTML5 and Flash.

## Developing

Penguin Subtitle Player is a Qt5 project. The executables include statically compiled Qt libraries.

####Libraries:
* [uchardet-enhanced](https://bitbucket.org/medoc/uchardet-enhanced): Auto charset detection. 

####Compilers:

* Windows: VC++ 2012
* Linux: G++
* Mac OSX: G++

Check [here](http://doc.qt.io/qt-5/deployment.html) for deployment details.

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History

0.2.1: Fixed subtitle delay problem

0.2.0: Added Charset Detection

0.1.0: First beta release

## Credits

Carson Ip, LMH, Kwanjai

## License

Code released under the GNU General Public License version 3.