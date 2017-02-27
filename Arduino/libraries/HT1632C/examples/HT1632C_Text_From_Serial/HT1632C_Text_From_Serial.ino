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

char chaine [] = "S\0";// On définit un tableau de char

void setup () {
  Serial.begin(9600);// On lance la liaison série
  HT1632.setCLK(DISPLAY_CLK); //On indique à la librarie HT1632 quel pin utiliser pour CLK
  HT1632.begin(DISPLAY_CS1, DISPLAY_WR, DISPLAY_DATA); //On indique à la librarie HT1632 quels pins utiliser pour piloter la matrice
  pinMode(8, INPUT_PULLUP); // On définit le pin 8 comme un INPUT pour notre bouton
}

void loop () {
    if (digitalRead(8) == LOW) {// Si notre bouton est en position LOW.
    HT1632.selectChannel(0); // On choisit d'écrire en vert.
  }

  if (digitalRead(8) == HIGH) {// Si notre bouton est en position HIGH.
    HT1632.selectChannel(1); // On choisit d'écrire en rouge.
  }
  static int ct2 = 1;//Pirouette pour décaler l'écriture
  if (Serial.available()) {// Si une console est ouverte
    chaine[0] = Serial.read();// On rentre la chaine de caractere dans notre tableau
    HT1632.drawText(chaine, ct2, 4, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);// On place un des caractère de la chaine reçue
    ct2 += 5; //On ce déplace de 5 LED
    HT1632.render();// On envoie le tout à la matrice
    if ((ct2 > 31) || (chaine[0] == 0x0a) || (chaine[0] == 0x0d)) {// Si la chaine utilise plus de 31 leds ou si on reçoit un backslash.
      HT1632.clear(); // On nettoie la matrice
      ct2 = 1;// On remet notre curseur à 1
    }
  }
}
