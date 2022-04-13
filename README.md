# ProjetAcademiques : Aerte par mail



# Principe

Dans ce projet, l’on utilise un Raspberry Pi sur lequel est connecté une caméra v2 et un capteur de distance HC-SR04. Le principe est que le capteur HC-SR04 détecte une présence à une certaine distance. Dès qu’un objet se retrouve à cette distance, le capteur HC-SR04 laisse le relai à la caméra v2 qui prendra une photo de l’objet et pour finir, cette photo sera envoyée sous forme d’alerte au mail qui sera renseigné dans le script. 

## Connexion ssh
Ici j'utilise une connexion ssh afin de me connecter a distance sur la raspberry Pi. Pour ce fair, apres avoir installer une image () sur une carte SD, j'ai dû placer un fichier nommé ssh vide sans extension sur cette carte SD . J'ai aussi placé un fichier wpa_supplicant.conf qui comporte un minimum de configuration pour pouvoir se connecter au reseau de mon téléphone ou sur celui de ma box. Cette configuration peut être trouvé ci-dessous

## Schema Connexion SSH

![schema ssh](https://github.com/Moussa75011/ProjetAcademiques/blob/master/sendMail/images/PPIssh.png)


## Fichier config connexion ssh

![wpa_supplicant.conf](https://github.com/Moussa75011/ProjetAcademiques/blob/master/sendMail/images/wpa_supplicant.png)

