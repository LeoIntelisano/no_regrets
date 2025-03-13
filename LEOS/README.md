# LEOS
## Purpose
To educate the creator
## Build
makefile in root\
`make all` to build\
`make qemu`to run
## Capabilities
- Paging enabled
- VGA tty output
## Issues
Shhhh
## OS Structure
```
/
├── Makefile            # Makefile in the root directory
├── build/              # Build artifacts (git-ignored)
├── src/                # Source code tree
│   ├── arch/           # Architecture-specific code
│   │   ├── x86/
│   │   └── arm/
│   ├── include/        # Architecture-independent headers
│   ├── kernel/         # Kernel source code
│   ├── lib/            # Libraries, including freestanding libc
│   └── tools/          # Build tools and utilities
├── sys/                # System-specific files
│   ├── bin/            # Super user binaries
│   ├── dev/            # Device files
│   ├── etc/            # System configuration files
│   ├── proc/           # Process information
│   ├── sys/            # System information
│   └── tmp/            # Temporary files
└── usr/                # Userland programs and libraries
    ├── bin/            # User binaries
    ├── include/        # User-level headers
    ├── lib/            # User-level libraries
    ├── local/          # Local software installation
    └── sbin/           # System binaries
```
