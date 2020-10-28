# Utinni
Utinni is a client plugin and injection framework which aims to provide an easier access to client and content development for Pre-CU Star Wars Galaxies and more specifically [SWGEmu](https://github.com/swgemu). 

Official plugins can be found [here](https://github.com/ptklatt/UtinniPlugins).

**Features**
* Gizmo implementation via ImGuizmo
* C# Plugin Framework
* C++ Plugin Framework
* Undo/Redo Framework in C#
* Hotkey Framework with rebindable hotkeys and a hotkey editor
* Settings handled via .ini
* Editor mode built in C# with Winforms, that natively hosts the Star Wars Galaxy client inside of a WinForms panel
* Custom WinForms form and control library
* Offline scene mode
* Game config override .cfg file
* Cmd passthrough for the launcher, enabling game settings being set via Windows shortcut
* FreeCam, including the ability to hide the player model (Only works in freecam)

**Key planned features**
* WinForm color themes (Almost done)
* Settings editor
* Game CUI Framework which allows the modification of existing UI elements and the creation of new
* Expanded FreeCam controls
* Setting to automatically attach Visual Studio on injection (Partly working)

**Third party libraries used:**

Please see licenses.txt for license information on libraries used.

* [CppSharp](https://github.com/mono/CppSharp)
* DetourXS
* [dearImgui](https://github.com/ocornut/imgui)
* [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
* [LeksysINI](https://github.com/Lek-sys/LeksysINI) -- Temporary, will most likely be replaced soon.
* [spdlog](https://github.com/gabime/spdlog)

**Credits**
* [James Webb (Sytner)](https://github.com/jdswebb) -- Pushing me to release and being a helping hand when I get absolutely stuck
* [Borrie BoBaka](https://modthegalaxy.com/index.php?members/helmedraven.3396/) -- Being there and supporting me from the very start of the development, invaluable testing, bug hunting and quality of life suggestions helped forge Utinni into what it now is
* [mezzanine](https://modthegalaxy.com/index.php?members/dsrules.896/) -- Being there and supporting me from the very start of the development, testing and experimenting with plugin development
