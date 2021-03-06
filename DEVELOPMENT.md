## Introduction

Penguin Subtitle Player is a Qt5 project.

## Building

#### 1. Clone the project & download dependencies

```
git clone --recurse-submodules https://github.com/carsonip/Penguin-Subtitle-Player
```
or
```
git clone https://github.com/carsonip/Penguin-Subtitle-Player
cd Penguin-Subtitle-Player
git submodule update --init --recursive
```

#### 2. Build

Use one of the following ways:

##### a. The easy way (GUI)

1. Download Qt with Qt Creator [here](http://www.qt.io/download-open-source/)
2. Open the .pro file in Qt Creator
3. Click on "Build"

##### b. The hard way (Command line)

1. Download Qt (without Qt Creator) [here](http://www.qt.io/download-open-source/)
2. Run qmake
  ```
  qmake PenguinSubtitlePlayer.pro
  ```
3. Build from the makefile generated by qmake
  * G++, Clang: ```make```
  * MSVC: ```nmake```
4. You should see the executable under ```build/debug``` or ```build/release```

To deploy a static build, build Qt statically and run `qmake "CONFIG+=static" PenguinSubtitlePlayer.pro`.

## Developing

#### Code formatting

This project uses [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) version 7 or higher. 

To format the code in this project, run:

```bash
find . -path "./src/uchardet" -prune -o \( -name '*.h' -o -name '*.cpp' \) -print | xargs clang-format -i -style=file
```

#### Libraries
* [uchardet](https://gitlab.freedesktop.org/uchardet/uchardet): Encoding detector

#### Deployment

Check [here](http://doc.qt.io/qt-5/deployment.html) for deployment details.

## Testing

1. Run `qmake "CONFIG+=test" PenguinSubtitlePlayer.pro`
2. Build from the makefile
3. Run the executable

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D
