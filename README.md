# Wayhibitor

Dead simple program to manually inhibit the idle state of a Wayland session, written in C.

I used to mimic this by simply stopping my idle service, but that has the issue of also getting rid of automatic locking (e.g., before sleep). This can also be used as a replacement to [SwayAudioIdleInhibit](https://github.com/ErikReider/SwayAudioIdleInhibit) by for example starting the program in the start script of gamemode, and killing it in the end script.