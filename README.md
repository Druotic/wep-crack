This is a simple tool that accepts a path to a WEP-40 packet/network log file.

Given the path, it exploits known security issues with  WEP-40 to extract
the 40-bit key.  Using this key, one could then decrypt all of the packets in the
log file. Specifically, this script is an implementation of the statistical attack
known as the FMS attack (Fluhrer, Mantin, Shamir). 

Usage:
 Compile:
 `make`

  Run:
  `./crack /path/to/logfile.wep`
 
