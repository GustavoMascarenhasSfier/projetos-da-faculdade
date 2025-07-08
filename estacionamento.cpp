#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

#define Password_Length 5

Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const int IR1 = 11; // infra v 1 no pino 11
const int IR2 = 12; // infra v 2 no pino 12

int Slot = 4;
int flag1 = 0;
int flag2 = 0;

int pos = 0;
char Data[Password_Length];
char Master[Password_Length] = "1234";
byte data_count = 0;

bool door = false;
bool passwordAccepted = false; // vê a senha
char customKey;

/*---configra teclado---*/
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {3, 4, 5, 6}; /* pins do teclado*/
byte colPins[COLS] = {7, 8, 9, 10};/* pins do teclado*/

Keypad customKeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Carregando dados");
  loading("Loading");
  lcd.clear();

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo.attach(2);
  ServoClose();
}

void loop() {
  if (!passwordAccepted) {
    // solicita a senha
    Open();
  } else {
    // vê quantas vagas tem
    checkParking();
  }
}

void loading(char msg[]) {
  lcd.setCursor(0, 1);
  lcd.print(msg);

  for (int i = 0; i < 9; i++) {
    delay(1000);
    lcd.print(".");
  }
}

void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

void ServoClose() {
  for (pos = 90; pos >= 0; pos -= 10) {
    myservo.write(pos);
  }
}

void ServoOpen() {
  for (pos = 0; pos <= 90; pos += 10) {
    myservo.write(pos);
  }
}

void Open() {
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha");

  customKey = customKeypad.getKey();
  if (customKey) {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == Password_Length - 1) {
    if (!strcmp(Data, Master)) {
      lcd.clear();
      ServoOpen();
      lcd.print("Estacionamento ");
      passwordAccepted = true; // a senha foi aceita
      delay(1000);
      loading("Aberto, espere");
      lcd.clear();
      lcd.print("Estacion aberto");
      delay(3000);
    } else {
      lcd.clear();
      lcd.print("Senha Errada");
      delay(3000);
      lcd.clear();
    }
    clearData();
  }
}

void checkParking() {
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    flag1 = 1;
    if (Slot > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Carro detectado");
      lcd.setCursor(0, 1);
      lcd.print("Abrindo cancela");
      ServoOpen();
      delay(3000);
      lcd.clear();
      
      lcd.setCursor(0, 0);
      lcd.print("Carro entrou");
      lcd.setCursor(0, 1);
      lcd.print("Fechando cancela");
      delay(3000);
      ServoClose();
      Slot = Slot - 1;
      lcd.clear();
      
      lcd.setCursor(0, 0);
      lcd.print("Vaga ocupada: ");
      lcd.print(4 - Slot);
      lcd.setCursor(0, 1);
      lcd.print("Vagas res: ");
      lcd.print(Slot);
      delay(3000);
      lcd.clear();
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Carro detectado");
      lcd.setCursor(0, 1);
      lcd.print("Sem vagas");
      delay(3000);
      lcd.clear();
    }
  }

  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Carro detectado");
    lcd.setCursor(0, 1);
    lcd.print("Abrindo cancela");
    ServoOpen();
    delay(3000);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Carro saiu");
    lcd.setCursor(0, 1);
    lcd.print("Fechando cancela");
    delay(3000);
    ServoClose();
    Slot = Slot + 1;
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Volte sempre!");
    lcd.setCursor(0, 1);
    lcd.print("Vagas res: ");
    lcd.print(Slot);
    delay(3000);
    lcd.clear();
  }

  if (flag1 == 1 || flag2 == 1) {
    delay(1000);
    flag1 = 0;
    flag2 = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("Vagas res: ");
  lcd.print(Slot);
  delay(500);
}