# BHMorse

Morse Code generator and trainer.  BHMorse can generate random characters, random groups of characters, and random moderately-plausible QSOs.  You can change the character speed (in WPM), the overall speed (in WPM), the difficulty of characters that are sent in the random characters and random groups (1 for the shortest letters, to 7 for infrequently used punctuation symbols), and pitch (in Hz).  Settings are stored to EEPROM when made, and restored from on power-up.

This is an Arduino library;  install it like you would any other user-contributed library.

The code is fairly easy to follow, so I won't include documentation, until the crowd clamors for it.

Each turn of the loop() calls SendNextElem(), which sends one element (a dit-long character mark or space, or an inter-character space).

See the 1CPO project on GitHub at https://github.com/wm8s/1CPO for a sketch that uses BHMorse to implement a full-featured CW trainer.

Also see the 1CPO project at https://hackaday.io/project/11212-1cpo for a hardware implementation that fits in an Altoids Smalls tin.

For the timing in the BHMorse library, I used the ARRL's Morse code speed calculations published in April 1990's QST (A Standard for Morse Timing Using the Farnsworth Technique by Jon Bloom, KE3Z) to convert character speed in WPM (c in the ARRL's calculations) and overall speed in WPM (s in the ARRL's calculations) to determine the total Farnsworth delay (t(a)) that must be spread out over the inter-character space (t(c)) and inter-word space (t(w)), the dit mark / space time (i.e., one element time, or u in the ARRL calculations), and the dah mark time, all maintaining the standard 1:1:3:7 ratio:

http://www.arrl.org/files/file/Technology/x9004008.pdf

The ARRL uses the more-or-less standard word PARIS, with 31 units of element mark and element space time plus 19 units of inter-character and inter-word space, or 50 total elements, for its calculations.

In order to see if PARIS and its 50 total elements still represented a decent "word" for words-per-minute calculations of a common amateur radio QSO, I took:

* 1,000 of the most common English words,
* the words making up the names of the 100 largest cities in the world,
* the numbers 1 through 30,
* eight of what I considered common power levels (5W, 10W, 25W, 50W, 100W, 200W, 500W, and 1KW),
* the most common Morse prosigns,
* the 200 highest scoring callsigns from the 2014 IARU HF contest results, and
* what I think are the 25 most common Q-signals, and 150 common Morse abbreviations (like PSE, UR, ES, etc.),

and I determined that the mean number of elements per word is 49.489. So as it turns out, in that regard, at least, PARIS is still a pretty good word for our purposes.
