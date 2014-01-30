Palemoon-Preloader
==================

The firefox preloader, adapted for the palemoon fork.
Original source here: http://sourceforge.net/projects/ffpreloader/
All credit goes to sixxgate for this preloader. My git repo just contains modifications that allows it to be compiled in VS2013, update some depreciated C++ syntax, and include binaries for the palemoon fork of firefox.

Planned features:
 - Manually specify the exe name, so one build is not limited to specific firefox forks.

Known Bugs
 - The preloader cannot kill or "unload" the palemoon process as it is. I don't think I'm going to fix this, I'll just remove all options related to "unloading palemoon". The consequence of this is, if you exit the preloader while palemoon is not running, the preloaded palemoon process will remain running on your system. You can kill it, or let it be- it won't affect your saved browsing session (if you have one).
 - If you start the preloader while palemoon is running, the preloader will try and fail to preload palemoon, resulting in a window opening every 10 seconds or so. This can be avoided by not starting the preloader while your browser is already running. If it's happening, exit your browser and start it again.

How it works
 - Whenever it detects that palemoon.exe is not running, it creates starts palemoon, with no extensions or tabs loaded, in a hidden window. This speeds up the start up time considerably if you don't have that many extensions and tabs. 
