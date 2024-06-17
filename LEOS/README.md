# LEOS
## Purpose
To educate the creator
## Build
makefile in root\
`make install` to build
## Capabilities
None
## Issues
Many
## OS Structure
```
/
├── .gitignore          # Git ignore file
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
Thanks, chat gpt for generating that tree
