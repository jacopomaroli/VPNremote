echo gdbinit script\n
set sysroot /opt/buildroot_toolchains/DD-WRT/staging
set solib-search-path /opt/buildroot_toolchains/DD-WRT/staging
set follow-fork-mode child
set detach-on-fork off
handle SIGINT nostop pass
info signals