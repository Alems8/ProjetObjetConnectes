# Maison Connectée

## Membres de l'équipe
- **Alessio Masi** : Responsable de la partie physique du projet, incluant le câblage, la programmation sur Arduino, et l'intégration des capteurs et actuateurs.
- **Gisele Lauren Ambassa Assene** : Responsable du développement de l'application mobile, utilisant MIT App Inventor pour interagir avec les composants matériels via Bluetooth.

## Table des Matières
- [Brève Description du Projet](#brève-description-du-projet)
- [Problématique](#problématique)
- [Matériel Utilisé](#matériel-utilisé)
- [Scénario d’Utilisation](#scénario-dutilisation)
- [Budget](#budget)
- [Bilan](#bilan)
- [Plan Futur](#plan-futur)
- [Références](#références)

---

## Brève Description du Projet
La réalisation de ce projet vise à développer une maison connectée capable d'améliorer la sécurité, le confort, et l'efficacité énergétique. 

### Fonctionnalités principales :
- Surveillance et contrôle de capteurs (température et gaz).  
- Détection de fumée avec notifications visuelles via des LEDs.  
- Sécurité renforcée avec un verrou NFC.  
- Contrôle via une application mobile Bluetooth.

---

## Problématique

Le projet répond aux défis suivants :

1. **Simplification des interactions :**  
Offrir une interface intuitive et accessible pour contrôler les dispositifs connectés dans une maison.  

2. **Accessibilité pour tous :**  
Concevoir une solution utilisable par des personnes âgées ou peu familières avec la technologie.

3. **Sécurité et confort :**  
Démontrer les avantages des capteurs intelligents pour améliorer la vie quotidienne.

---

## Matériel Utilisé

### Boards :
- **Arduino Uno** : Plateforme principale pour l'intégration des capteurs et actuateurs.
- **Nucleo F411-RE** : Utilisé pour les fonctionnalités avancées, comme la communication NFC.

### Capteurs :
- **Capteur de température (MPC9808)** : Mesure précise de la température ambiante.
- **Capteur de gaz (MQ5)** : Détection des gaz potentiellement dangereux.

### Actuateurs :
- **Servo-moteur FS90** : Actionne le verrouillage et le déverrouillage de la porte.
- **LEDs** : Utilisées pour des notifications visuelles en fonction des capteurs.

### Dispositifs de communication :
- **NFC Reader (X-NUCLEO-NFC05A1)** : Contrôle d'accès à l'aide de tags NFC.
- **Module Bluetooth HC05** : Permet l'échange de données entre les capteurs et l'application mobile.

---

## Scénario d’Utilisation

### Fonctionnalités :
1. **Surveillance de l'environnement :**  
   - Le capteur de température et le capteur de gaz surveillent les variations et détectent les anomalies.  
   - Les LEDs s’allument pour signaler des alertes comme la présence de gaz.

2. **Interaction via Bluetooth :**  
   - L’utilisateur peut contrôler les dispositifs à distance via une application mobile connectée par Bluetooth.  

3. **Contrôle d’accès NFC :**  
   - L’utilisation d’un tag NFC permet de verrouiller ou déverrouiller la porte.  
   - Le servo-moteur agit selon les commandes reçues.  

### Implémentation Technique
- **Arduino IDE :**
  - Le projet comporte deux fichiers de code principaux :
    1. Un fichier pour l’Arduino Uno, responsable de la gestion des capteurs (température, gaz) et des LEDs.
    2. Un fichier pour la Nucleo F411-RE, utilisé pour le contrôle du NFC et du servo-moteur pour la porte.
  - Chaque fichier est documenté pour faciliter la compréhension et la maintenance.

- **MIT App Inventor :**
  - L’application mobile, développée avec MIT App Inventor, permet de :
    - Recevoir les données des capteurs via Bluetooth.
    - Envoyer des commandes pour interagir avec le système (par exemple, activer/désactiver des fonctionnalités).

**Vidéo de démonstration :** Une vidéo est incluse pour présenter toutes les fonctionnalités en action.

---

## Budget
| **Description**        | **Prix (€/unité)** |  
|-------------------------|--------------------|  
| Arduino UNO            | 29,30             |  
| Nucleo F411-RE         | 15,65             |  
| MPC9808                | 5,75              |  
| MQ5                    | 5,09              |  
| Servo FS90             | 4,90              |  
| LEDs (x3)              | 3,49              |  
| X-NUCLEO-NFC05A1       | 11,54             |  
| Bluetooth HC05         | 15,50             |  
| Fils et autres         | 4,00              |  
| Batterie externe (x2)  | 40,00             |  
| **Total**              | **135,22 €**      |

### Temps de Travail
Le projet a nécessité un total de **36 heures**, réparties comme suit :
- **18 heures** de cours en classe (à raison de 6 séances de 3 heures chacune).
- **18 heures** de travail individuel effectué en dehors des heures de cours.

L’ensemble du travail a principalement été réalisé dans le **Fablab**.

---

## Bilan

### Points positifs :
- Les résultats sont conformes aux objectifs initiaux.  
- La communication Bluetooth et les capteurs fonctionnent sans problèmes.  
- Interface mobile intuitive, accessible à tous les utilisateurs.

### Points négatifs :
- Les fonctionnalités actuelles sont limitées par l’absence de connectivité à distance.  
- Dépendance au Bluetooth pour contrôler la maison.

---

## Plan Futur

### Améliorations possibles :
1. **Ajout de capteurs :**
   - Intégration de capteurs de mouvement et d’humidité pour enrichir la maquette.

2. **Amélioration de l’application mobile :**
   - Notifications en temps réel.
   - Contrôle à distance via le cloud.

3. **Application à une maison réelle :**
   - Tester et déployer les fonctionnalités sur une maison connectée grandeur nature.  
   - Créer une solution potentiellement commercialisable.

---

## Références
[1] [Arduino Uno](https://store.arduino.cc/en-fr/products/arduino-uno-rev3)  
[2] [Nucleo F411-RE](https://www.st.com/en/evaluation-tools/nucleo-f411re.html)  
[3] [MPC9808 Capteur de Température](https://wiki.seeedstudio.com/Grove-I2C_High_Accuracy_Temperature_Sensor-MCP9808/)  
[4] [MQ5 Capteur de Gaz](https://www.waveshare.com/mq-5-gas-sensor.htm)  
[5] [Servo FS90](https://www.gotronic.fr/art-servomoteur-analogique-miniature-fs90-25826.htm)  
[6] [X-NUCLEO-NFC05A1](https://www.st.com/en/ecosystems/x-nucleo-nfc05a1.html)  
[7] [Module Bluetooth HC05](https://www.gotronic.fr/art-module-bluetooth-hc05-26097.htm)
