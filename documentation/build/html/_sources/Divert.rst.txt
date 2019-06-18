Tips Diverts
============

Maintenances des impression 3D
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Ultimaker²
    Si l'extrudeur ne sort pas d'ABS, regarder au niveau du stepper d'insertion du filament si il na pas "creusé" le filament ce qui le bloque

Temperatures d'impression
^^^^^^^^^^^^^^^^^^^^^^^^^

Ultimaker² / ABS
    extrudeur : 200°c
    Bed : 60°c

Maintenance du server
^^^^^^^^^^^^^^^^^^^^^

Il arrive que le server plante: dans ce cas relancer le server.
IMPORTANT: le server restart avec un heure non correct pour fix::
    date ; sudo hwclock --hctosys ; date

Cela affiche la date, regle la date UTC sur la date hardware, reaffiche la date.
Les client prometheus auront alors probablement crash (dû a l'incoherence de l'heure) pour fix::
    systemctl stop prometheus1 ; systemctl stop prometheus2 ; systemctl stop prometheus3

    ou tapez "enable_printer"

rm les different dossier "data" localisé dans les clients octoprint (/home/pi/printers/...)
relancer les services prometheus::
    systemctl start prometheus1 ; systemctl start prometheus2 ; systemctl start prometheus3

    ou tapez "disable_printer"
