/* Fork From : https://github.com/gauravmm/HT1632-for-Arduino
    Testé sur Arduino IDE 1.0.6 - 1.8.1
    Matériel Nécessaire :
        - Arduino UNO R3 : http://www.selectronic.fr/carte-arduino-uno.html?suggestion=produit
        - Câble USB : http://www.selectronic.fr/cordon-usb2-0-a-b-male-male-0-6m.html
        - Matrice LED : http://www.selectronic.fr/arduino-matrice-32x16-leds-bicolores-rouges-vertes.html
        - Interrupteur à bascule : http://www.selectronic.fr/interrupteur-a-bascule-rond-on-off-on-on.html
        - Câbles Prototypages Mâles / Femelles : http://www.selectronic.fr/fils-de-test-m-f-120mm-nappe-de-40.html
        - Découpe Laser 3mm ou 5mm disponible sur le repo github dans le dossier Boitier
        - 4 Vis et Boulons M3
*/

#include <HT1632.h> // On inclut la librairie pour la matrice
#include <font_5x4.h> // On inclut la librairie pour l'écriture en taille 5
#include <font_8x4.h> // On inclut la librairie pour l'écriture en taille 8
#include <images.h> // On inclut la librairie pour les images

#define DISPLAY_CLK  13 // On définit le port 13 de l'arduino comme CLK
#define DISPLAY_CS1  12 // On définit le port 12 de l'arduino comme CS1
#define DISPLAY_WR   10 // On définit le port 10 de l'arduino comme WR
#define DISPLAY_DATA 9 // On définit le port 9 de l'arduino comme DATA

int TIME = 0; // variable global TIME qui nous servira plus tard

void setup () {
  HT1632.setCLK(DISPLAY_CLK); //On indique à la librarie HT1632 quel pin utiliser pour CLK
  HT1632.begin(DISPLAY_CS1, DISPLAY_WR, DISPLAY_DATA); //On indique à la librarie HT1632 quels pins utiliser pour piloter la matrice
  pinMode(8, INPUT_PULLUP); // On définit le pin 8 comme un INPUT pour notre bouton
}

void loop () {
 if (digitalRead(8) == LOW) {// Si notre bouton est en position LOW.
    TIME = 100; //On change le temps d'attente
  }

  if (digitalRead(8) == HIGH) {// Si notre bouton est en position HIGH.
    TIME = 500; //On change le temps d'attente
  }

  HT1632.selectChannel(0); // On choisit d'écrire en vert.
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, (OUT_SIZE - IMG_HEART_WIDTH) / 2, 4);//On dessine notre coeur.
  HT1632.render();// On envoie le tout à la matrice
  delay(TIME);// Petite pause.

  HT1632.clear(); // On enlève l'affichage précédent.
  HT1632.render(); // On envoie le tout à la matrice
  delay(TIME); // Petite pause.

  HT1632.selectChannel(1); // Select the first channel
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, (OUT_SIZE - IMG_HEART_WIDTH) / 2, 4);//On dessine notre coeur.
  HT1632.render(); // On envoie le tout à la matrice
  delay(TIME); // Petite pause.

  HT1632.clear(); // On enlève l'affichage précédent.
  HT1632.render(); // On envoie le tout à la matrice
  delay(TIME); // Petite pause.

  HT1632.selectChannel(1); // On choisit d'écrire en rouge.
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, (OUT_SIZE - IMG_HEART_WIDTH) / 2, 4); //On dessine notre coeur.
  HT1632.selectChannel(0);// On choisit d'écrire en vert.
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, (OUT_SIZE - IMG_HEART_WIDTH) / 2, 4);// On dessine notre coeur.
  HT1632.render(); // On envoie le tout à la matrice
  delay(TIME); // Petite pause.

  HT1632.clear();// On enlève l'affichage précédent.
  HT1632.render(); // On envoie le tout à la matrice
  delay(TIME); // Petite pause.
}
