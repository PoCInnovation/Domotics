MONITORING DES IMPRIMANTES
==========================

L'itération pour les imprimantes contient plusieurs étapes necessaires tel que l'installation de clients octoprint pour les imprimantes 3d (sur rasperry pi).

Octoprint permet alors de controller les differentes imprimantes ainsi qu'a transmettres les informations necessaire au monitoring (temp, status, ...).
Le monitoring se fait ensuite a l'aide de grafana et de client de recupération des information des imprimantes, Prometheus.

Un rasperry pi cera necessaire pour les differents clients octoprint (en fonction du nombre d'imprimantes) et un server cera necessaire pour grafana et les differents clients prometheus.


Installation d'Octoprint
^^^^^^^^^^^^^^^^^^^^^^^^

- Pour installer Octoprint

       https://octoprint.org/download/

- Pour l'installation des differents client octoprint

       http://thomas-messmer.com/index.php/14-free-knowledge/howtos/79-setting-up-octoprint-for-multiple-printers

Une fois installé, octoprint permet de controller les imprimantes, mais il faut ensuite pouvoir transmettre les informations qui nous interessent.

- Pour installer le plugin prometheus:

       https://github.com/sbelectronics/octoprint-prometheus

Les informations interessantes sont ensuite exportées sous forme de données scrapable par prometheus a l'adresse : http://0.0.0.0:8000 (par default)
il faudra ensuite installer des clients prometheus sur le server afin de pourvoir les "parser" et les traiter avec grafana

Pour cela il faudra créé autant de client prometheus que de client octoprint.
Afin de répondre à des soucis de maintenances, nous avons souhaité transformer les clients prometheus en services afin qu'il se lancent au démarrage du server.

- Installation des webcam (ProTip):

       Utilisez: Udev, lsusb, udevadm