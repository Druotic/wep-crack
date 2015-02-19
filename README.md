### WEP-crack

This is a simple tool that accepts a path to a WEP-40 packet/network log file.

Given the path to a log file, it exploits known security issues with  WEP-40 to compute
the private key which was originally used to encrypt.  Using this key, one could then decrypt 
all of the packets in the log file. Specifically, this script is an implementation of the 
statistical attack known as the [FMS attack](http://www.crypto.com/papers/others/rc4_ksaproc.pdf) (Fluhrer, Mantin, Shamir). 

### Usage:

1) **Compile:**

  `make`

2) **Run:**

  `./crack /path/to/logfile.wep`
 

### References: 

- [Weaknesses in Key Scheduling Algorithm in RC4](http://www.crypto.com/papers/others/rc4_ksaproc.pdf)
- [FMS Attack (Wikipedia - linked above)](http://en.wikipedia.org/wiki/Fluhrer,_Mantin_and_Shamir_attack)
