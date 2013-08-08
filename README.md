osxinj
======

Another dylib injector.

- `mach_inject` was taken from `rentzsch/mach_inject`. Thanks!
- `testapp` is a sample app to inject into

Released under the MIT License.

Notes
-----

- Target 32bit: `qmake -spec macx-clang-32`
- Target 64bit: `qmake -spec macx-clang`
- Build debug/release: `-config [debug/release]`