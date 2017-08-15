
Debian
====================
This directory contains files used to package bitcloudd/bitcloud-qt
for Debian-based Linux systems. If you compile bitcloudd/bitcloud-qt yourself, there are some useful files here.

## bitcloud: URI support ##


bitcloud-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcloud-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcloudqt binary to `/usr/bin`
and the `../../share/pixmaps/bitcloud128.png` to `/usr/share/pixmaps`

bitcloud-qt.protocol (KDE)

