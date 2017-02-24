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

char chaine [] = "S\0";

void setup () {
  Serial.begin(9600);
  HT1632.setCLK(DISPLAY_CLK); //On indique à la librarie HT1632 quel pin utiliser pour CLK
  HT1632.begin(DISPLAY_CS1, DISPLAY_CS2, DISPLAY_WR, DISPLAY_DATA); //On indique à la librarie HT1632 quels pins utiliser pour piloter la matrice
  pinMode(8, INPUT_PULLUP); // On définit le pin 8 comme un INPUT pour notre bouton
}

void loop () {
    if (digitalRead(8) == LOW) {
    HT1632.selectChannel(0); // Green heart on first screen:
  }

  if (digitalRead(8) == HIGH) {
    HT1632.selectChannel(1); // Green heart on first screen:
  }
  static int ct2 = 1;
  if (Serial.available()) {
    chaine[0] = Serial.read();
    HT1632.drawText(chaine, ct2, 4, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
    ct2 += 5;
    HT1632.render();
    if ((ct2 > 31) || (chaine[0] == 0x0a) || (chaine[0] == 0x0d)) {
      HT1632.clear();
      ct2 = 1;
    }
  }
}
