# Wayhibitor

Dead simple program to manually inhibit the idle state of a Wayland session, written in C.

I used to mimic this by simply stopping my idle service, but that has the issue of also getting rid of automatic locking (e.g., before sleep). This can also be used as a replacement to [SwayAudioIdleInhibit](https://github.com/ErikReider/SwayAudioIdleInhibit), because the majority of browsers already do the inhibition themselves, and you can start Wayhibitor in the start script of gamemode, and kill it in the end script for games.

## Building

Requirements:
- Wayland development headers
- `libwayland-client`

Simply run:

```sh
make
```