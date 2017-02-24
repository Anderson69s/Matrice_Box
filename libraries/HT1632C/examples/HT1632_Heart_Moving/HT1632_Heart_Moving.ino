/* Librarie à récupérer pour piloter la matrice de LED : https://github.com/gauravmm/HT1632-for-Arduino
    Testé sur Arduino IDE 1.0.6 - 1.8.1
    Matériel Nécessaire :
        - Arduino UNO R3 : http://www.selectronic.fr/carte-arduino-uno.html?suggestion=produit
        - Câble USB : http://www.selectronic.fr/cordon-usb2-0-a-b-male-male-0-6m.html
        - Matrice LED : http://www.selectronic.fr/arduino-matrice-32x16-leds-bicolores-rouges-vertes.html
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
#define DISPLAY_CS2  7 // On définit le port 7 de l'arduino comme CS2
#define DISPLAY_WR   10 // On définit le port 10 de l'arduino comme WR
#define DISPLAY_DATA 9 // On définit le port 9 de l'arduino comme DATA

int j = 0; // variable global j qui nous servira plus tard
int TIME = 0; // variable global TIME qui nous servira plus tard

void setup () {
  HT1632.setCLK(DISPLAY_CLK); //On indique à la librarie HT1632 quel pin utiliser pour CLK
  HT1632.begin(DISPLAY_CS1, DISPLAY_CS2, DISPLAY_WR, DISPLAY_DATA); //On indique à la librarie HT1632 quels pins utiliser pour piloter la matrice
  pinMode(8, INPUT_PULLUP); // On définit le pin 8 comme un INPUT pour notre bouton
}

void loop () {
  // Zero all data in all channels:
  if (digitalRead(8) == LOW) {
    TIME = 25;
  }

  if (digitalRead(8) == HIGH) {
    TIME = 100;
  }
  HT1632.renderTarget(0);
  HT1632.clear();

  HT1632.selectChannel(0); // Red heart on first screen:
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, j - IMG_HEART_WIDTH, 4);

  HT1632.selectChannel(1); // Green heart on first screen:
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, OUT_SIZE * 2 - j, 4);

  HT1632.render(); // This sends the data in both channels to the screen.

  HT1632.renderTarget(1);
  HT1632.clear();

  HT1632.selectChannel(0); // Red heart on second screen:
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, j - IMG_HEART_WIDTH - OUT_SIZE, 4);

  HT1632.selectChannel(1); // Green heart on second screen:
  HT1632.drawImage(IMG_HEART, IMG_HEART_WIDTH,  IMG_HEART_HEIGHT, OUT_SIZE - j, 4);

  HT1632.render();

  // Get the next number in the sequence, wrapping from 3 back to 0:
  j = (j + 1) % (OUT_SIZE * 2);

  delay(TIME);
}
