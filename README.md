# chi_respiro_cosmico

## le due cartelle indicano i file da caricare su arduino ed i file da caricare su raspberry

Bisogna installare su raspy:

vnc server
Supercollider
Oscillator (forse credo boh)
pure data extended

in .config/lxsession/LXDE-pi/autostart bisogna, in quest'ordine
far partire vnc (e poi commentarlo, solo per debug)
far partire launcher.sh che c'è in drago
mettere uno sleep di 10 secondi
far partire pure data che carica drago.pd

PROFIT!
