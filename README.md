# BetterQtcDRP
Discord Rich Presence plugin for Qt Creator, which adds an excellent Rich Presence to your Qt Creator.
# Screenshot
![Screenshot](https://raw.githubusercontent.com/TheMiksHacker/BetterQtcDRP/master/screenshot.png)
# Changes
This is a fork of [another plugin (but what’s funny, that plugin is also fork)](https://github.com/Clem-Fern/QtcDRP) that has been slightly modified. In this fork changed:
- Changed the images that are displayed in Rich Presence
- Improved code in some places
- Removed the ability to send invitations to Discord (anyway, it will not join them)
- Added support for many file formats (e.g. JavaScript, Python, and QML)

Note: All images in this plugin are taken from the [Papirus icon theme](https://github.com/PapirusDevelopmentTeam/papirus-icon-theme).
# Build and install
```
git clone https://github.com/TheMiksHacker/BetterQtcDRP.git
```
Copy qtcreator.local.pri.example to qtcreator.local.pri (and change it)

Copy discord-rpc.local.pri.example to discord-rpc.local.pri (and change it) (optional)

Copy broken-libs.local.pri.example to broken-libs.local.pri.example (and change it) (optional)
```
qmake
```
Go in builded release directory
```
sudo make install
```

# Releases
Perhaps you can download the already compiled binary. To do this, go to the [Releases page](https://github.com/TheMiksHacker/BetterQtcDRP/releases) and download the binary file that suits you. Then just put this file in the folder with Qt Creator plugins (on GNU/Linux, if you downloaded from the repositories - /usr/lib/qtcreator/plugins)
