# VPN remote
This is a server which allows you to manage the most common VPN settings remotely through REST interface.

The project is mainly didactical and not intended for production usage.
At the current stage it's heavily unsafe.
Should be ok though if you put it on a router in a DMZ LAN you blindly trust (e.g. your home network).
The main reason why I decided to publish it, is because it was hard to find simple references and examples on how you could interact with iptables through iptc in C.

I'm running it on my netgear nighthawk DD-WRT router. 
I didn't have the related toolchain so I built it using [buildroot](https://buildroot.org/) specifying only the version of the kernel and the C library (musl libc).

In the config folder there's a simple service startup script responsible to manage the service. it's supposed to be placed in /opt/etc/init.d if used on DD-WRT.

The code can be roughly separated in the following main parts:
* Linux service
* Configuration
* REST server (based on [ulfius](https://github.com/babelouest/ulfius))
* iptables interaction

Currently is allowing you to query/add/remove iptables marks for specific ip:port through a simple js/html interface.
This allows you to enable/disable VPN tunneling for specific clients/ports.
 
The roadmap for the future is
* Split main file in some modules
* Improve security (basic HTTP auth, ip whitelist)
* Improve logging
* Improve config options
* Allow multiple iptables MARKS
* Query/add routes
* openvpn interaction (start/stop/query/pass options to process. e.g. change country from your VPN provider)
* list LAN clients
