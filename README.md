monit
=====

Monit (http://mmonit.com/monit/) is a free open source utility for managing and monitoring, processes, programs, files, directories and filesystems on a UNIX system. This fork add the following enhancements:

Sync commands
-------------

You can start/stop/restart/monitor/unmonitor a service waiting until the operation is completed.
When a sync operation is performed, the service is locked so no other operations are possible.

New commands added:
* sync_start name [attempts]     - Sync start the named service
* sync_stop name [attempts]      - Sync stop the named service
* sync_restart name [attempts]   - Sync restart the named service
* sync_monitor name [attempts]   - Sync enable monitoring of the named service
* sync_unmonitor name [attempts] - Sync disable monitoring of the named service

The status/summary commands accept the "service" parameter for displaying the status of only one service:
* status [service]  - Print full status information for each service
* summary [service] - Print short status information for each service

Communication over UNIX socket
------------------------------

The command and the daemon can communicate over UNIX socket (it works then the network is not configured).  
