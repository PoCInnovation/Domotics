API
====

Les projets utilisant le NFC communiquent avec une API simple.
Un server mariadb tourne sur la VM de DOMOTICS pour stocker les utilisateurs.
Il y a une database nommée "flask_api" qui contient deux tables:
    - user: contient les différents utilisateurs enregistrés ainsi que l'UID de leur carte
    - history: qui contient l'historique de toutes les cartes scannées

Les routes pour interagir avec la DB sont:

add_user
^^^^^^^^
    - Ajoute un utilisateur dans la base de données

    - Methode: POST

    - Variables:

        - username: Nom de référence de l'utilisateur
        - uid: Unique ID de l'utilisateur (de sa carte)

Exemple ::

    curl -X POST 192.168.15.138:5000/add_user -d "usernmame=DOMOTICS&uid=0123456789"

remove_user
^^^^^^^^^^^

    - Description: ajoute un utilisateur dans la base de données

    - Methode: POST

    - Variables:

        - username: Nom de référence de l'utilisateur

Exemple ::

    curl -X POST 192.168.15.138:5000/remove_user -d "usernmame=DOMOTICS"

rename_user
^^^^^^^^^^^

    - Description: renomme un utilisateur dans la base de données

    - Methode: POST

    - Variables:

        - username: Ancien nom de référence de l'utilisateur
        - new_username: Nouveau nom de référence de l'utilisateur

Exemple ::

    curl -X POST 192.168.15.138:5000/rename_user -d "username=DOMOTICS&new_username=Domotics"
