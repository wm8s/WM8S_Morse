# BHMorse

Morse Code generator and trainer.  BHMorse can generate random characters, random groups of characters, an random moderately-plausible QSOs.  You can change the character speed (in WPM), the overall speed (in WPM), the difficulty of characters that are sent in the random characters and random groups (1 for the shortest letters, to 7 for infrequently used punctuation symbols), and pitch (in Hz).  Settings are stored to EEPROM when made, and restored from on power-up.

This is an Arduino library;  install it like you would any other user-contributed library.

The code is fairly easy to follow, so I won't include documentation, until the crowd clamors for it.

Each turn of the loop() sends one element (a dit-long character mark or space, or an inter-character space).

See the BH_1CPO project on GitHub for a sketch that uses BHMorse to implement a full-featured CW trainer.

Also see the 1CPO project at https://hackaday.io/project/11212-1cpo for a hardware implementation that fits in an Altoids Smalls tin.
