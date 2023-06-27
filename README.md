# Bras robotisé joysticks

Ce programme gère le bras robotisé EEZYBotARM (v1) avec deux joysticks.

## Connexions à l'Arduino Nano Every

| Broche  | Périphérique connecté  | Nom dans le programme |
| ------- | ---------------------- | --------------------- |
| 2       | Servomoteur base       | `PIN_BASE_SERVO`      |
| 3       | Servomoteur hauteur    | `PIN_HEIGH_SERVO`     |
| 4       | Servomoteur avancement | `PIN_FRONT_SERVO`     |
| 5       | Servomoteur pince      | `PIN_CLAMP_SERVO`     |
| 6       | Bouton joystick gauche |                       |
| 7       | Bouton joystick droit  |                       |
| 14 / D0 | Axe X joystick gauche  | `PIN_X_JOYSTICK_A`    |
| 15 / D1 | Axe Y joystick gauche  | `PIN_Y_JOYSTICK_A`    |
| 16 / D2 | Axe X joystick droit   | `PIN_X_JOYSTICK_B`    |
| 17 / D3 | Axe Y joystick droit   | `PIN_Y_JOYSTICK_B`    |