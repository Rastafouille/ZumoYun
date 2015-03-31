
# Tuto ZUMO YUN
Ce tuto permet de réaliser un petit robot à chenilles type « sumo », pilotable en wifi via une page HTML, avec caméra embarquée.

##Matériels :
- Arduino YUN
	<http://arduino.cc/en/Main/ArduinoBoardYun?from=Main.ArduinoYUN>
	<http://www.generationrobots.com/fr/401462-connecteurs-pour-empiler-des-shields-arduino.html>
- Un kit ZUMO + moteurs à monter
	<http://www.generationrobots.com/en/196-zumo-mini-robot-for-arduino>
- WebCam  “TRUST WIDESCREEN HD” (par exemple)
	<http://www.trust.com/fr-fr/all-products/16530-widescreen-hd-720p-webcam> 
- Connectique 
	<http://www.generationrobots.com/en/401462-shield-stacking-headers-for-arduino.html>
- Une carte micro SD
- Un objectif Fisheye téléphone
	<http://www.priceminister.com/offer/buy/156063688/objectif-photo-fish-eye-180-magnetique-pour-apple-iphone-4-4s-ipod-touch.html>
- 4 piles AA

##Montage et connections
- Monter les connecteurs de shield Arduino sur la shield Zumo, puis insérer la carte YUN. Les connecteurs sont utilisés pour surélever la carte YUN.
- Connecter la caméra sur le port USB de la YUN.
- Mettez en place les 4 piles et positionner l’interrupteur du shield ZUMO sur « ON ».
- Attention, pour l’utilisation du buzzer avec une carte Yun (ATmega32u4) le « buzzer control jumper » doit être sur 32U4.
 
![alt text](https://github.com/Rastafouille/ZumoYun/raw/master/Galerie/ZumoYunv1.png)


##Coté YUN
Une fois la Yun alimentée, branchez un câble RJ45 entre celle-ci est votre box. Se connecter en SSH (putty.exe ou autre) à la YUN, adresse : <http://arduino.local>, login : `root`, mot de passe : `arduino`. De cette manière votre Yun sera connectée à Internet et sera accessible par votre ordinateur.

Se connecter en SSH (putty.exe ou autre) à la YUN, adresse : <http://arduino.local> ou <http://192.168.240.1>, login :`root`, mot de passe : `arduino`.
![alt text](https://github.com/Rastafouille/ZumoYun/raw/master/Galerie/linino.png)

###Installation package de base :
	opkg update
	opkg install bzip2
	opkg install unzip
	opkg install tar
	opkg install wget
	opkg install fdisk
	opkg install e2fsprogs
	opkg install openssh-sftp-server
	opkg install distribute
	opkg install pyopenssl
	opkg install python-openssl
	opkg install python-crypto
	opkg install python-bzip2
	opkg install python-sqlite3
	opkg install python-ncurses

###Installation packages video:
	opkg install kmod-video-uvc
	wget  http://www.custommobileapps.com.au/downloads/mjpg-streamer.ipk
	opkg install mjpg-streamer.ipk
	opkg install fswebcam

###Configuration vidéo :
Une fois les packages installés nous allons faire en sorte que le streamer se lance dès le démarrage de la Yun. Pour cela il faut insérer la ligne de démarrage du streamer dans un fichier de config.
- Dans le dossier :
	`cd /etc/rc.d`
- Créer et ouvrir un nouveau fichier :
	`vim S999lancement_video` 
- Y écrire la ligne suivante :
	`mjpg_streamer -i "input_uvc.so -d /dev/video0 -r 640x480 -f 25" -o "output_http.so -p 8080 -w /www/webcam" &`
- Fermer et sauvegarder le fichier :
	- Echap puis `:wq`
	- Puis `chmod +x S999lancement_video`

Le stream vidéo sera maintenant accessible sur le port 8080 de la carte Yun

##Coté Arduino
Télécharger et installer les librairies Arduino Zumo dans l'IDE arduino: <https://github.com/pololu/zumo-shield>

A partir de l’IDE Arduino 1.5.6-r2 : <http://arduino.cc/en/main/software>, téléverser « ZumoYun.ide »
Ce code permet d’interpréter les trames envoyées par la page HTML via le bridge.

##Coté carte SD 
A la racine de la carte SD, préalablement formatée en FAT32, créez un dossier « arduino »
Copier le dossier « ZumoYunHTML » dans ce dossier « arduino».
Si vous n’avez pas de carte SD, vous pouvez copier le dossier à l’emplacement /www de la Yun, avec Filezilla.exe par exemple.

##Démarrage 
Plus besoin de faire de mise à jour donc plus besoin de connexion Internet sur la Yun. Vous pouvez vous connecter en wifi. Une fois la Yun alimentée, attendre 1 à 2min et connectez votre matériel (ordinateur, tablette, smartphone…) en wifi au réseau YUN (SSID : Arduino Yún-XXXXXXXXXXXX).

Si besoin, vous pouvez vous connecter en SSH (putty.exe ou autre) à la Yun, adresse : <http://arduino.local> ou <http://192.168.240.1>, login :`root`, mot de passe : `arduino`.

Une fois connecté en wifi à la carte Yun, ouvrez la page :
- <http://192.168.240.1/sd/ZumoYunHTML> si le dossier « ZumoYunHTML » est sur la carte SD
- <http://192.168.240.1/ZumoYunHTML> si le dossier « ZumoYunHTML » est sur la carte Yun (/www)
A la première connexion, l’explorateur internet vous demandera un code : arduino.
Enjoy !!
![alt text](https://github.com/Rastafouille/ZumoYun/raw/master/Galerie/interfaceHTML.png)

##Finition
En utilisant les fichiers de modèle 3D vous pouvez réaliser en impression 3D les 3 pièces Capot-Sup, Capot-Inf et Lame comme ci-dessous :
![alt text](https://github.com/Rastafouille/ZumoYun/raw/master/Galerie/vue3D.png)
![alt text](https://github.com/Rastafouille/ZumoYun/raw/master/Galerie/photo.png)

