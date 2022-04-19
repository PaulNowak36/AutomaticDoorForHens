#include <Arduino.h>
#line 1 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
//moteur + relais + LCD + cellule + capteurs

//Modif: Travaux avec VSCode + création fichier Github

#include <LiquidCrystal.h>
#include <millisDelay.h>

// Création de l'objet lcd (avec les différents ports numériques qu'il utilise)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Programmation des délais de fermeture et d'ouverture
millisDelay Execution_Delai_fermeture; 
millisDelay Execution_Delai_ouverture; 

//variables
int lcd_key     = 0;
int adc_key_in  = 0;
int TensionBAS  = 0;
int TensionHAUT  = 0;
float TensionCelluleSolaire = 0;
float TensionMoteur = 0;

//constantes
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define RelayPin1 2 //le port numérique D2 est connecté au relais 1
#define RelayPin2 3 //le port numérique D3 est connecté au relais 2
#define CapteurBAS 11 //le port numérique D11 est connecté au capteur BAS
#define CapteurHAUT 12 //le port numérique D12 est connecté au capteur HAUT

#define debugTxtVar(myParameterText, variableName) \
  Serial.print(#myParameterText " = "); \
  Serial.println(variableName);

#define debugTxtVar2(myParameterText1, variableName1, myParameterText2, variableName2) \
  Serial.print(#myParameterText1 " = "); \
  Serial.print(variableName1); \
  Serial.print(" " #myParameterText2 " = "); \
  Serial.println(variableName2);

int Etat_fonctionnement_manuel = 0;//Indique l'état du programme de test manuel
int Etat_fermeture_auto = 0;//Indique l'état du programme de fermeture automatique
int Etat_ouverture_auto = 0;//Indique l'état du programme d'ouverture automatique

unsigned long temps_fonctionnement_manuel = 0;
unsigned long temps_mesures = 0;
unsigned long temps_serie = 0;
unsigned long temps_actuel;

unsigned long Temporisation_SOIR = 10000;//temporisation du SOIR avant fermeture
unsigned long Temporisation_MATIN = 10000;//temporisation du MATIN avant fermeture

boolean JourVrai;   // indique si c'est le jour ou la nuit
boolean PorteOuverte = false; // indique si la porte est en position ouverte ou non
boolean PorteFermee = false; // indique si la porte est en position fermee ou non
boolean Test_manuel_demarrage = false; //indique si le test manuel de la porte est en cours ou non
boolean AUTO_Fermeture = false; //indique si la fermeture automatique de la porte est en cours ou non
boolean AUTO_Ouverture = false; //indique si l'ouverture automatique test manuel de la porte est en cours ou non

int backLight = 10;

#line 67 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void setup();
#line 90 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void loop();
#line 107 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void task_mesure_tensions();
#line 159 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void Affichage_serie();
#line 185 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void AppuiBouton();
#line 200 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void QuelJour();
#line 212 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void FermerMoteur();
#line 217 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void ArretMoteur();
#line 222 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void OuvrirMoteur();
#line 229 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void Activation_capteurBAS();
#line 245 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void Activation_capteurHAUT();
#line 264 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void AutoFermerMoteur();
#line 275 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void AutoOuvrirMoteur();
#line 285 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void Activation_delais();
#line 349 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void task_fonctionnement_manuel();
#line 428 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
int read_LCD_buttons();
#line 67 "c:\\Users\\PaulNOWAK\\Desktop\\Automatic door for hens\\Stage Eurl TOULET\\Mission\\Programmes\\Programme principal\\Fonctionnement_AutoVSCode\\Fonctionnement_AutoVSCode.ino"
void setup()
{
  // On met les pin de chaque relais en sortie
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);

  ArretMoteur();

  // On met les pin de chaque capteur en entrée
  pinMode(CapteurBAS, INPUT);
  pinMode(CapteurHAUT, INPUT);

  Serial.begin(9600);// ouvre le port série et fixe le debit de communication à 9600 bauds
  Serial.println("test1");

  lcd.begin(16, 2);              // Démarrage de l'écran
  //pinMode(backLight, OUTPUT);
  //digitalWrite(backLight, HIGH);
  lcd.setCursor(0, 0);           // Positionnement du curseur au début
  lcd.print("Test porte"); // Message

}

void loop()
{
  // Sous traite les différentes tâches
  lcd_key = read_LCD_buttons();  // Lecture des touches
  task_mesure_tensions();
  Affichage_serie();
  task_fonctionnement_manuel();
  AutoFermerMoteur ();
  AutoOuvrirMoteur ();
  QuelJour();
  Activation_capteurBAS();
  Activation_capteurHAUT();
  AppuiBouton();
  Activation_delais();

}//loop

void task_mesure_tensions()//permet de prendre des mesures de tensions et d'afficher des données sur l'écran LCD
{
  temps_actuel = millis();//fonction non bloquante qui indique le temps passé en millisecondes

  if ( (temps_actuel - temps_mesures) >= 250ul ) //la boucle se réinitialise toutes les 250 ms
  {
    temps_mesures = temps_actuel;

    // Transforme la mesure (nombre entier) en tension via un produit en croix
    int CelluleSolaireCAN = analogRead(A1); // Mesure la tension aux bornes de la cellule solaire
    int MoteurCAN = analogRead(A2); // Mesure la tension consommée par le moteur

    float TensionV1 = (float)CelluleSolaireCAN * (5.0 / 1023.0);
    float TensionV2 = (float)MoteurCAN * (5.0 / 1023.0);

    lcd.setCursor(0, 1);           // Positionnement du curseur début de ligne

    //affiche les différentes données sur l'écran LCD

    if (JourVrai)
    {
      lcd.print("J"); //affiche "J" pour jour
    }
    else // if (!JourVrai)
    {
      lcd.print("N"); //affiche "N" pour nuit
      //digitalWrite(backLight, LOW);
    }

    lcd.print(" m");
    lcd.print(Etat_fonctionnement_manuel); //affiche la valeur de la variable

    lcd.print(" F");
    lcd.print(Etat_fermeture_auto); //affiche la valeur de la variable
    
    lcd.print(" f");
    lcd.print(AUTO_Fermeture); //affiche la valeur de la variable
    
    lcd.print(" O");
    lcd.print(Etat_ouverture_auto); //affiche la valeur de la variable

    lcd.print(" o");
    lcd.print(AUTO_Ouverture); //affiche la valeur de la variable
    
    TensionCelluleSolaire = TensionV1;

    TensionMoteur = TensionV2;

  }//if

}//task_mesure_tensions

void Affichage_serie() {//fait tourner le moteur dans un sens pour fermer la porte
  temps_actuel = millis();//fonction non bloquante qui indique le temps passé en millisecondes

  if ( (temps_actuel - temps_serie) >= 1000ul )//la boucle se réinitialise à chaque seconde
  {
    temps_serie = temps_actuel;

    //affiche les différentes données sur le moniteur série

    debugTxtVar2(TensionCelluleSolaire , TensionCelluleSolaire, TensionMoteur , TensionMoteur);

    debugTxtVar(JourVrai , JourVrai);

    debugTxtVar2(Etat_fonctionnement_manuel , Etat_fonctionnement_manuel, Test_manuel_demarrage , Test_manuel_demarrage);

    debugTxtVar2(AUTO_Fermeture , AUTO_Fermeture, Etat_fermeture_auto , Etat_fermeture_auto);

    debugTxtVar2(AUTO_Ouverture , AUTO_Ouverture, Etat_ouverture_auto , Etat_ouverture_auto);

    debugTxtVar2(PorteOuverte , PorteOuverte, PorteFermee , PorteFermee);

    debugTxtVar(temps_actuel , temps_actuel);

  }
}

void AppuiBouton() {//fait tourner le moteur dans un sens pour fermer la porte
  switch (lcd_key)               // Action en cas de touche pressée
  {
    case btnRIGHT: //en appuyant sur le bouton RIGHT
      {
        if (Etat_fonctionnement_manuel == 0 && PorteOuverte) {
          Etat_fonctionnement_manuel = 1; //on affecte la variable à 1
          Test_manuel_demarrage = true;
          
        }
        break;
      }
  }
}

void QuelJour() {//fait tourner le moteur dans un sens pour fermer la porte
  if (TensionCelluleSolaire < 1.0  )
  { // une tension basse signifie qu'il commence à faire sombre
    JourVrai = false; //la variable passe à false lorsqu'il fait nuit
  }

  else
  { // une tension haute signifie que le soleil se lève
    JourVrai = true;  //la variable passe à true lorsqu'il fait jour
  }
}

void FermerMoteur() {//fait tourner le moteur dans un sens pour fermer la porte
  digitalWrite(RelayPin1, LOW); //le relais 1 est actif
  digitalWrite(RelayPin2, HIGH); //le relais 2 est inactif
}

void ArretMoteur() {//met le moteur en pause et stoppe la porte
  digitalWrite(RelayPin1, HIGH); //le relais 1 est inactif
  digitalWrite(RelayPin2, HIGH); //le relais 2 est inactif
}

void OuvrirMoteur() {//fait tourner le moteur dans l'autre sens pour ouvrir la porte
  digitalWrite(RelayPin1, HIGH); //le relais 1 est inactif
  digitalWrite(RelayPin2, LOW); //le relais 2 est actif
}



void Activation_capteurBAS() {//fait tourner le moteur dans l'autre sens pour ouvrir la porte
  if ( digitalRead(CapteurBAS) == LOW )//lorsque le contact du capteur BAS est fermé...
  {
    PorteFermee = true;//la porte est en position fermée
    if (AUTO_Fermeture)
    {//lorsque le programme de fermeture automatique est en route
      ArretMoteur();//on arrête le moteur
      AUTO_Fermeture = false;
    }
  }
  else
  {
    PorteFermee = false; //la porte n'est pas en position fermée
  }
}

void Activation_capteurHAUT() {//fait tourner le moteur dans l'autre sens pour ouvrir la porte
  if ( digitalRead(CapteurHAUT) == LOW  )//lorsque le contact du capteur HAUT est fermé...
  {
    PorteOuverte = true; //la porte est en position ouverte
    if (AUTO_Ouverture)
    {//lorsque le programme d'ouverture automatique est en route
      ArretMoteur();//on arrête le moteur
      AUTO_Ouverture = false;
    }
  }

  else
  {
    PorteOuverte = false; //la porte n'est pas en position ouverte
  }
}



void AutoFermerMoteur () { //va faire fermer le moteur automatiquement au bout de 10 s

  if (AUTO_Fermeture)
  {
    Etat_fermeture_auto = 2; //on affecte la variable à 2
    //on fait fermer la porte
    FermerMoteur();
    //digitalWrite(backLight, LOW);
  }
}

void AutoOuvrirMoteur () { //va faire ouvrir le moteur automatiquement au bout de 10 s

  if (AUTO_Ouverture)
  {
    Etat_ouverture_auto = 2; //on affecte la variable à 2
    //on fait ouvrir la porte
    OuvrirMoteur();
  }
}

void Activation_delais() {//met le moteur en pause et stoppe la porte
  if (Execution_Delai_fermeture.justFinished()) { 
    //Execution_Delai_fermeture only returns true once after start()
    // do something here
    AUTO_Fermeture = true;  // only do this once even if condition remains true for a long time
  }

  if (Execution_Delai_ouverture.justFinished()) { 
    //Execution_Delai_fermeture only returns true once after start()
    // do something here
    AUTO_Ouverture = true;  // only do this once even if condition remains true for a long time
  }

  if (PorteOuverte)  // La porte n'est pas en position fermée...
  
    if (!JourVrai) //  ...mais il fait nuit
    {
        if (!Execution_Delai_fermeture.isRunning() && (!AUTO_Fermeture)) 
        {
            //si les conditions sont réunies...
            //tant que l'exécution du délai de fermeture est en cours
            Execution_Delai_fermeture.start(Temporisation_SOIR);
            //on active la temporisation du soir
            Etat_fermeture_auto = 1; //on affecte la variable à 1
            Etat_ouverture_auto = 0; //on affecte la variable à 0      
        }     
      
    }
    else   // mais il fait jour
    {
      // si les conditions ne sont plus respectées alors que la tempo du soir n'est pas fini
      Execution_Delai_fermeture.stop();
      // on annule le délai de fermeture et on réinitialise la tempo du soir
      Etat_fermeture_auto = 0; //on affecte la variable à 0
      Etat_ouverture_auto = 0; //on affecte la variable à 0
    } 

  if (PorteFermee)   //  La porte n'est pas en position fermée...
  {
    if (JourVrai) //  ...mais il fait nuit
    {
      if (!Execution_Delai_ouverture.isRunning() && (!AUTO_Ouverture)) 
        {
            //si les conditions sont réunies...
            //tant que l'exécution du délai d'ouverture est en cours
            Execution_Delai_ouverture.start(Temporisation_MATIN);
            //on active la temporisation du matin
            Etat_ouverture_auto = 1; //on affecte la variable à 1
            Etat_fermeture_auto = 0; //on affecte la variable à 0      
        }
      
    }
    else  // mais il fait nuit
    {
      // si les conditions ne sont plus respectées alors que la tempo du matin n'est pas fini
      Execution_Delai_ouverture.stop();
      // on annule le délai d'ouverture et on réinitialise la tempo du matin
      Etat_ouverture_auto = 0; //on affecte la variable à 0
      Etat_fermeture_auto = 0; //on affecte la variable à 0
      
    }
  }
}

void task_fonctionnement_manuel()//permet d'activer le test de fonctionnement manuel de la porte
{
  temps_actuel = millis();//fonction non bloquante qui indique le temps passé en millisecondes

  switch ( Etat_fonctionnement_manuel )
  {
    case    1:
      // Après l'appui du bouton, le moteur tourne dans un sens et la porte commence à se fermer...
      FermerMoteur();
      temps_fonctionnement_manuel = temps_actuel;//on réinitialise le temps passé à 0 ms
      Etat_fonctionnement_manuel++;// on incrémente la variable de 1

      break;

    case    2:
      if (PorteFermee) //lorsqu'on détecte la porte en position fermée...
      {
        //on lance une temporisation d'une seconde pour être sûr qu'elle soit bien fermée
        temps_fonctionnement_manuel = temps_actuel;//on réinitialise le temps passé à 0 ms
        Etat_fonctionnement_manuel++;// on incrémente la variable de 1

      }//if

      break;

    case    3:
      if ((temps_actuel - temps_fonctionnement_manuel) >= 1000ul) //une fois la temporisation achevée...
      {
        //...le moteur se met en pause et la porte s'arrête
        ArretMoteur();
        temps_fonctionnement_manuel = temps_actuel;//on réinitialise le temps passé à 0 ms
        Etat_fonctionnement_manuel++;// on incrémente la variable de 1

      }//if

      break;

    case    4:
      if ( (temps_actuel - temps_fonctionnement_manuel) >= 3000ul )
      {
        // une fois les 3 secondes de pause passées, on ouvre la porte
        OuvrirMoteur();
        temps_fonctionnement_manuel = temps_actuel;//on réinitialise le temps passé à 0 ms
        Etat_fonctionnement_manuel++;// on incrémente la variable de 1

      }//if

      break;

    case    5:
      if (PorteOuverte) //lorsqu'on détecte la porte en position ouverte...
      {
        //on lance une temporisation d'une seconde pour être sûr qu'elle soit bien ouverte
        temps_fonctionnement_manuel = temps_actuel;//on réinitialise le temps passé à 0 ms
        Etat_fonctionnement_manuel++;// on incrémente la variable de 1

      }//if

      break;

    case    6:
      if ( (temps_actuel - temps_fonctionnement_manuel) >= 1000ul )//une fois la temporisation achevée...
      {
        //...le moteur se met en pause et la porte s'arrête
        ArretMoteur();
        temps_fonctionnement_manuel = temps_actuel;//on réinitialise le temps passé à 0 ms
        Etat_fonctionnement_manuel = 0;//on affecte la variable à 0
        Test_manuel_demarrage = false; //le test manuel de la porte est terminé

      }//if

      break;

  }//switch

}//task_fonctionnement_manuel


// Fonction de lecture des touches
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);   // Lecture du port analogique

  // Les valeurs qui suivent doivent être adaptées au shield
  if (adc_key_in > 1000) return btnNONE;   // En principe 1023 quand aucune touche n'est pressée
  if (adc_key_in < 50)   return btnRIGHT;     // 0
  if (adc_key_in < 195)  return btnUP;        // 99
  if (adc_key_in < 380)  return btnDOWN;      // 255
  if (adc_key_in < 555)  return btnLEFT;      // 409
  if (adc_key_in < 790)  return btnSELECT;    // 640

  return btnNONE;
}

