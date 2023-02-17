# 3ds-template

This template is intended for use with VS Code and Docker to create a portable development environment. If you open the project in VS Code and use the DevContainer extension, it will take care of installing all dependencies through my custom docker image based on the official devkitpro image. Just run `make` from a terminal.

## Usage

| Targets     | Action                                                                                    |
| ------------| ----------------------------------------------------------------------------------------- |
| 3ds         | Builds `<project name>.3ds`. <sup>1</sup>
| 3dsx        | Builds `<project name>.3dsx` and `<project name>.smdh`.
| cia         | Builds `<project name>.cia`. <sup>1</sup>
| citra       | Builds and automatically runs `citra` for testing.<sup>2</sup>
| elf         | Builds `<project name>.elf`.
| release     | Release build, creates a `cia`, `3ds`, and a zip file containing the `smdh` and `3dsx`. <sup>3</sup>

## Creating a new project
1. Clone this repository and open in VS Code.
2. Ensure the extension Dev Containers is installed and hit `F1` to open the command menu.
3. Hit `Dev Containers: Open Folder in Container...`
4. (Only needed for cia/3ds builds) Edit the file `resources/AppInfo`
    1. Edit those values and ensure you choose a unique id see [unique_id_list].
    2. Replace the existing files in the `resources` directory to suit your needs.
    
**Note** please ensure that no folder/directory used in the project contains spaces. Devkitpro's Makefiles apparently does not like this.
That is, do not have it in a folder like `C:/3DS Hacking/3ds-template` rather `C:/3DS_Hacking/3ds-template`
  
## Credits
All of this would not have been possible without the work of
* [Smealum](https://github.com/smealum)
* [Steveice10](https://github.com/Steveice10) for the [buildtools]
* [amaredeus](https://github.com/amaredeus) for various improvements to the template (such as the formatting in this README)
* [TricksterGuy](https://github.com/TricksterGuy) for the original template


[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


[buildtools]: <https://github.com/Steveice10/buildtools>
[bannertool]: <https://github.com/Steveice10/buildtools>
[citra]: <https://github.com/citra-emu/citra>
[libbz2.dll]: <http://downloads.sourceforge.net/gnuwin32/zip-3.0-dep.zip>
[makerom]: <https://github.com/profi200/Project_CTR>
[unique_id_list]: <https://gbatemp.net/threads/homebrew-cias-uniqueid-collection.379362>
[wiki]: <https://wiki.gbatemp.net/wiki/3DS_Homebrew_Development#Install_devkitARM>
[zip]: <http://downloads.sourceforge.net/gnuwin32/zip-3.0-bin.zip>
