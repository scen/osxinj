osxinj
======
Fixed version of osxinj!

Another dylib injector. Uses a bootstrapping module since `mach_inject` doesn't fully emulate library loading and crashes when loading complex modules.

- `mach_inject` was taken from `rentzsch/mach_inject`. Thanks!
- `testapp` is a sample app to inject into
- `testdylib` is a sample dylib to inject into an app
- `bootstrap` is a dylib that is initially injected to load another dylib (e.g. `testdylib`)

Released under the MIT License.

Notes
-----

- Build with scheme `BuildAll`
