#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};  // Connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9};  // Connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys),
                                   rowPins,
                                   colPins,
                                   ROWS, 
                                   COLS );

const int relayPin = A0;  // Connect to the control pin of the relay

char password[] = "240722";  // Change this to your desired password
char enteredPassword[7];
int passwordIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Initialize relay (door locked)
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (strcmp(enteredPassword, password) == 0) {
        unlockDoor();
      } else {
        Serial.println("Incorrect password!");
        resetPassword();
      }
    } else {
      enteredPassword[passwordIndex++] = key;
      Serial.print(key);
      
      if (passwordIndex == 6) {
        passwordIndex = 0;
      }
    }
  }
}

void unlockDoor() {
  Serial.println("\nDoor unlocked!");
  digitalWrite(relayPin, LOW);  // Activate the relay (unlock the door)
  delay(2000);                    // Keep the door unlocked for 2 seconds
  digitalWrite(relayPin, HIGH);   // Deactivate the relay (lock the door)
  resetPassword();
}

void resetPassword() {
  memset(enteredPassword, 0, sizeof(enteredPassword));
  passwordIndex = 0;
  delay(1000);  // Delay to prevent rapid password attempts
}
