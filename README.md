# Maison Connectée

Ce projet consiste à développer une maquette de maison connectée intégrant des capteurs, des actuateurs, et une application mobile pour un contrôle à distance.

---

## Table des Matières
1. [Présentation du Projet](#présentation-du-projet)
2. [Matériel Nécessaire](#matériel-nécessaire)
3. [Installation](#installation)
4. [Utilisation](#utilisation)

---

## Présentation du Projet

- **Objectif :** Créer une maquette fonctionnelle d’une maison connectée intégrant des capteurs (gaz, température), des actuateurs (servo-moteur, LEDs), et une application mobile pour le contrôle à distance.

- **Fonctionnalités principales :**
  - Détection de gaz inflammables avec alerte sonore et visuelle.
  - Surveillance de la température ambiante pour contrôler un radiateur simulé.
  - Verrouillage/déverrouillage via un tag NFC.
  - Contrôle des LEDs via l’application mobile.
  - Commandes vocales dans l’application pour une meilleure accessibilité.


 ## Matériel Nécessaire

### Électronique :
- Arduino Uno
- STM32 Nucleo F411-RE
- Module Bluetooth HC05
- Lecteur NFC (X-NUCLEO-NFC05A1)
- Capteur de gaz (MQ5)
- Capteur de température (MCP9808)
- Servo FS90
- LEDs (RGB et monochrome)
- Fils de connexion, breadboard, batterie externe

### Logiciels :
- [Arduino IDE](https://www.arduino.cc/en/software)
- [MIT App Inventor2](https://appinventor.mit.edu/)
#### Bibliothèques Arduino nécessaires :

##### À télécharger manuellement :
1. **Seeed_MCP9808**  
   - Pour le capteur de température MCP9808.  
   - [Lien de téléchargement](https://github.com/Seeed-Studio/Grove_Temperature_sensor_MCP9808).  

2. **Ultrasonic**  
   - Initialement prévu pour un capteur à ultrasons (non utilisé dans le projet final).  
   - [Lien de téléchargement](https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger/archive/master.zip).  

3. **Bibliothèques NFC** : Pour gérer le lecteur NFC X-NUCLEO-NFC05A1.  
   - **nfc_utils.h**  
     - [Lien de téléchargement](https://github.com/stm32duino/X-NUCLEO-NFC05A1).  
   - **rfal_nfc.h**  
     - [Lien de téléchargement](https://github.com/stm32duino/NFC-RFAL).
   - **ndef_class.h**
     - [Lien de téléchargement](https://github.com/stm32duino/ST25R3911B)

**Importation des bibliothèques téléchargées dans l’IDE Arduino :**
1. Télécharger le fichier `.zip` depuis les liens ci-dessus.
2. Ouvrir l’IDE Arduino.
3. Aller dans **Sketch > Inclure une bibliothèque > Ajouter la bibliothèque ZIP...**.
4. Sélectionner le fichier `.zip` téléchargé, puis cliquer sur **Ouvrir**.
5. La bibliothèque sera ajoutée et prête à être utilisée dans vos sketchs Arduino.
##### À installer via l’IDE Arduino :
1. **Servo**  
   - Pour le contrôle du servo-moteur.  
   - Aller dans **Outils > Gérer les bibliothèques**, rechercher **Servo**, et installer.

2. **SoftwareSerial**  
   - Inclus par défaut avec l’IDE Arduino pour gérer les communications série supplémentaires.

### Installation

#### Étape 1 : Cloner le dépôt
1. Téléchargez ou clonez ce dépôt GitHub sur votre machine locale.  
   ```bash
   git clone https://github.com/Alems8/ProjetObjetConnectes
   ```  

2. Ouvrez les fichiers `.ino` dans l’IDE Arduino :
   - `arduino_sensors.ino` : Pour la gestion des capteurs, LEDs, et Bluetooth.
   - `door_complete.ino` : Pour le NFC et le servo sur la Nucleo F411-RE.

3. Importez les bibliothèques téléchargées :
   - Suivez les instructions de la section [Logiciels](#logiciels) pour importer les bibliothèques nécessaires dans l’IDE Arduino.

---

#### Étape 2 : Configuration de la carte STM32 Nucleo
La configuration de la carte Nucleo nécessite quelques étapes spécifiques pour assurer une compatibilité avec l’IDE Arduino.

1. **Téléchargez les outils nécessaires :**
   - [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)  
   - [ST-Link USB Driver](https://www.st.com/en/development-tools/stsw-link009.html)  

2. **Configurer l’IDE Arduino :**
   - Allez dans **Fichiers > Préférences**.
   - Dans le champ **Additional Board Managers URLs**, ajoutez l’URL suivante :  
     ```
     https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
     ```
   - Cliquez sur **OK**.
    ![preferences setup](https://github.com/user-attachments/assets/13a0695f-9456-42a8-b64c-c185bb6fa0c7)

3. **Sélectionner et configurer la carte :**
   - Allez dans **Outils > Board > Board Manager**, puis recherchez et installez **STM32**.
   - Dans **Outils**, configurez les options suivantes :
     - **Board :** `STM32 Nucleo 64`.
     - **Board part number :** `Nucleo F411RE`.
     - **Upload method :** `STM32CubeProgrammer (SWD)`.

![Tools window](https://github.com/user-attachments/assets/6ce98d8a-5cb2-48ea-9de4-bf76897e5b0c)


---

#### Étape 3 : Connecter les composants matériels
1. **Modules connectés à la carte STM32 Nucleo :**  
   - Le module **X-NUCLEO-NFC05A1** doit être placé directement au-dessus de la carte Nucleo F411-RE.  
   - Connectez également le **servo-moteur FS90** à la Nucleo.

2. **Modules connectés à l’Arduino Uno :**  
   - **Capteur de température (MCP9808)**  
   - **Capteur de gaz (MQ5)**  
   - **LEDs (RGB et monochrome)**  
   - **Module Bluetooth HC05**

3. Assurez-vous de câbler les capteurs et actuateurs selon les schémas fournis sur les sites des produits.  
4. Alimentez le système via une batterie externe ou un adaptateur secteur pour garantir une alimentation stable.

---

#### Étape 4 : Installer l’application mobile
1. Téléchargez l’application mobile APK fournie dans ce dépôt GitHub via .  
2. Installez l’application sur votre smartphone Android.  
3. Connectez l’application au module Bluetooth HC05 de la maquette pour contrôler les dispositifs.

**NB:** *L'application a été créée par assemblage de blocs qui sont par la suite traduits en code JAVA pour le bon fonctionnement de l'application*

### Utilisation

#### Étape 1 : Allumer le système
1. Branchez les deux cartes :
   - **STM32 Nucleo F411-RE** : Connectée au module NFC et au servo-moteur.  
   - **Arduino Uno** : Connectée aux capteurs (gaz, température), LEDs, et au module Bluetooth HC05.
2. Assurez-vous que les deux cartes sont alimentées correctement via une batterie externe ou un adaptateur secteur.

---

#### Étape 2 : Connexion Bluetooth
1. Activez le Bluetooth sur votre smartphone.  
2. Recherchez le module Bluetooth HC05 et connectez-vous.  
   - **Mot de passe Bluetooth :** Le mot de passe sera probablement **1234** ou **0000** (selon la configuration par défaut).  

3. Ouvrez l’application mobile installée sur votre smartphone.  
4. Connectez-vous au module Bluetooth HC05 directement depuis l’application.


---

#### Étape 3 : Tester les fonctionnalités
Vous pouvez tester chaque fonctionnalité individuellement :

1. **Capteur de gaz :**
   - Tenez un briquet (en mode gaz uniquement, sans flamme) devant le capteur MQ5.  
   - Cela devrait activer la LED rouge et le buzzer pour signaler la détection de gaz.  
   - Les informations du capteur seront également envoyées à l’application mobile pour une lecture plus aisée.  

2. **Capteur de température :**
   - Placez le capteur MCP9808 dans un environnement plus froid (e.g., réfrigérateur ou simplement souffler de l’air froid).  
   - Si la température est inférieure au seuil défini, la LED verte (représentant le radiateur) s’allumera.
   - Les informations du capteur seront également envoyées à l’application mobile pour une lecture plus aisée.  


3. **Porte intelligente (NFC + Servo) :**
   - Approchez un tag NFC devant le lecteur.  
   - **Important :** Avant de tester, assurez-vous de définir l’UID du tag dans le fichier `door_complete.ino`.  
     - **Trouver l’UID du tag :**
       - Utilisez l’exemple fourni par la bibliothèque X-NUCLEO-NFC05A1.  
       - L’exemple affichera l’UID du tag dans la console série lorsque le tag est approché.  
     - Remplacez l’UID dans le code par celui du tag que vous souhaitez utiliser.  
   - Une fois le tag correctement configuré et reconnu, le servo-moteur déverrouillera la porte.

4. **(LED + RGB) et reconnaissance vocale :**
   - Dans l'application, positionnez vous sur la page dediée à l'éclairage
   - Veuillez vous connecter au module Bluetooth HC05 directement depuis l’application.
      - **Allumage des LEDS**
         - Deux modes d'activation se présentent à vous à savoir :

         ![Eclairage](https://private-user-images.githubusercontent.com/185907809/408369263-9e1d0f9a-66e5-4a35-9793-0b9cbb6373d4.jpg?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MzgyODkxMDcsIm5iZiI6MTczODI4ODgwNywicGF0aCI6Ii8xODU5MDc4MDkvNDA4MzY5MjYzLTllMWQwZjlhLTY2ZTUtNGEzNS05NzkzLTBiOWNiYjYzNzNkNC5qcGc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMTMxJTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDEzMVQwMjAwMDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1lYTQyMmI2ODNhYjQ0ODM1ZTRkODJmY2EwOGMxZTM5Y2NiYjlkNmJjNjczNWNmYzRjOWE5ZTE3NThlMjUwNzZiJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9._xmiWlpZK7OTVU_rRqMZ3wMrUYOEfEu7MRfi2KvcVCk)

         - **Utilisation du bouton switch**
            - Cliquez sur le bouton switch et la led s'allumera/s'éteindra selon son état précédant
         - **Utilisation de la reconnaissance vocale**
            - cliquez sur l'image du micro qui est en réalité un bouton
            - Le système de reconnaissance est ainsi déclenché
            - Dites alors "Allume cuisine" ou "Eteindre cuisine" selon votre désir
            - Votre commande sera alors automatiquement traduite et transféré à la carte Arduino.
      - **Changement de couleur des LEDS RGB**
         - Sur le cercle coloré en dessous de la page se trouve une sorte de petit cercle pouvant servir de pointeur
         - Déplacez ce pointeur en fonction de la couleur que vous souhaitez obtenir
         - La couleur sélectionnée sera visible dans le carré juste à droite
         - Une fois la couleur souhaitée obtenue, il suffit de cliquer sur le bouton "valider" et laisser la magie opérer

         ![Couleurs](https://private-user-images.githubusercontent.com/185907809/408368733-b0621f87-d66b-4519-a84c-88ddfd2beea7.jpg?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MzgyODkxMDcsIm5iZiI6MTczODI4ODgwNywicGF0aCI6Ii8xODU5MDc4MDkvNDA4MzY4NzMzLWIwNjIxZjg3LWQ2NmItNDUxOS1hODRjLTg4ZGRmZDJiZWVhNy5qcGc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMTMxJTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDEzMVQwMjAwMDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1iOTczMzFhOTExYzQ1Zjc1OWQzYmIzNzZlNTEyOWNhM2EyZDQ5ODU5YjRmMjI4ZTRjZjc2YzMxNGY4M2M3YTBiJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.fg32_VWkVXa39Mj-AhLRFQtUWoyUU32QvRmB1CQp3Vo)
---

#### Étape 4 : Résolution des problèmes
- **Bluetooth instable :** Si la connexion Bluetooth échoue ou se déconnecte fréquemment :
  - Débranchez et rebranchez le module HC05.  
  - Réessayez de connecter le module depuis l’application mobile.

- **NFC non reconnu :** Vérifiez que l’UID du tag correspond à celui défini dans le code. Si nécessaire, répétez le processus pour lire et configurer l’UID.

---

Avec ces étapes, vous pouvez explorer toutes les fonctionnalités de la maquette et les tester dans un environnement contrôlé !
