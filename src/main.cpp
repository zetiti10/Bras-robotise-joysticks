/**
 * @file main.cpp
 * @author Louis L
 * @brief Fichier principal du bras robotisé (contrôle avec les joysticks).
 * @version 1.0
 * @date 2023-06-23
 */

// Ajout des bibliothèques au programme.
#include <Arduino.h>
#include <Servo.h>

// Autres fichiers du programme.
#include <pinDefinitions.hpp>

// Création des 4 servomoteurs du bras robotisé.
Servo baseServo;
Servo heighServo;
Servo frontServo;
Servo clampServo;

// Variables globales.
int XJoystickAHome;
int YJoystickAHome;
int XJoystickBHome;
int YJoystickBHome;

// Création du constructeur qui servira à stocker les angles maximums des servomoteurs.
struct ServoMaxAngle
{
  int minDegree;
  int maxDegree;
};

// Définition des limites d'angle pour les servomoteurs.
const struct ServoMaxAngle baseServoMaxAngle = {0, 180};
const struct ServoMaxAngle heighServoMaxAngle = {0, 100};
const struct ServoMaxAngle frontServoMaxAngle = {0, 160};
const struct ServoMaxAngle clampServoMaxAngle = {20, 100};

void setup()
{

  // Définition des modes des broches des capteurs.
  pinMode(PIN_X_JOYSTICK_A, INPUT);
  pinMode(PIN_Y_JOYSTICK_A, INPUT);
  pinMode(PIN_X_JOYSTICK_B, INPUT);
  pinMode(PIN_Y_JOYSTICK_B, INPUT);

  // Définition de la position initiale des joysticks.
  XJoystickAHome = analogRead(PIN_X_JOYSTICK_A);
  YJoystickAHome = analogRead(PIN_Y_JOYSTICK_A);
  XJoystickBHome = analogRead(PIN_X_JOYSTICK_B);
  YJoystickBHome = analogRead(PIN_Y_JOYSTICK_B);

  // Initialisation des servomoteurs.
  baseServo.attach(PIN_BASE_SERVO);
  heighServo.attach(PIN_HEIGH_SERVO);
  frontServo.attach(PIN_FRONT_SERVO);
  clampServo.attach(PIN_CLAMP_SERVO);
}

// Fonction de mouvement d'un servomoteur en fonction du mouvement d'un joystick.
void moveServo(Servo &servo, int joystickHome, int joystickPos, struct ServoMaxAngle maxAngle)
{
  // On vérifie que le joystick a bien bougé.
  if (joystickHome == joystickPos)
  {
    return;
  }

  // Mise en place des variables
  int action = 0;
  float speed = 0;

  // On vérifie dans quel sens le joystick a été orienté, ainsi que sa force.
  if (joystickPos < (joystickHome - 100))
  {
    speed = (joystickHome - joystickPos) / 100;

    if (maxAngle.minDegree <= (servo.read() - speed))
    {
      action = -1;
    }
  }

  else if (joystickPos > (joystickHome + 100))
  {
    speed = (joystickPos - joystickHome) / 100;

    if (maxAngle.maxDegree >= (servo.read() - speed))
    {
      action = 1;
    }
  }

  // Si le mouvement n'a pas été assez fort ou que le servomoteur est déjà en bout de course, on ne produit pas de mouvement.
  if (action == 0)
  {
    return;
  }

  // On effectue le déplacement.
  servo.write(servo.read() + (speed * action));
}

void loop()
{
  // Récupération de l'état des joysticks.
  int XJoystickAPos = analogRead(PIN_X_JOYSTICK_A);
  int YJoystickAPos = analogRead(PIN_Y_JOYSTICK_A);
  int XJoystickBPos = analogRead(PIN_X_JOYSTICK_B);
  int YJoystickBPos = analogRead(PIN_Y_JOYSTICK_B);

  // Le joystick qui contrôle le servomoteur "frontServo" doit être inversé.
  YJoystickBPos = 1024 - YJoystickBPos;

  // En fonction de des positions des joysticks, on effectue des mouvements des servomoteurs.
  moveServo(baseServo, XJoystickAHome, XJoystickAPos, baseServoMaxAngle);
  moveServo(heighServo, YJoystickAHome, YJoystickAPos, heighServoMaxAngle);
  moveServo(frontServo, YJoystickBHome, YJoystickBPos, clampServoMaxAngle);
  moveServo(clampServo, XJoystickBHome, XJoystickBPos, frontServoMaxAngle);

  // Le délais permet aux servomoteurs de ne pas se déplacer trop vite, ce qui ferait perdre de la précision à l'utilisateur.
  delay(50);
}