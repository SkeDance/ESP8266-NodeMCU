#define LED_PIN_D8 15     // Пин, к которому подключен светодиод
#define BUTTON_PIN_D0 16  // Пин, к которому подключена кнопка
#define BUTTON_PIN_D1 5  // Пин, к которому подключена кнопка
#define BUTTON_PIN_D2 4  // Пин, к которому подключена кнопка
#define BUTTON_PIN_D3 0  // Пин, к которому подключена кнопка
void setup() {
  pinMode(LED_PIN_D8, OUTPUT);           // Настраиваем пин светодиода как выход
  pinMode(BUTTON_PIN_D0, INPUT_PULLUP);  // Настраиваем пин кнопки как вход с подтягивающим резистором
  pinMode(BUTTON_PIN_D1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_D2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_D3, INPUT_PULLUP);
}

void loop() {
//  if (digitalRead(BUTTON_PIN_D0) == LOW) {  // Кнопка нажата (сигнал LOW из-за подтягивающего резистора)
//    digitalWrite(LED_PIN_D8, HIGH);         // Включаем светодиод
//  } else {
//    digitalWrite(LED_PIN_D8, LOW);          // Выключаем светодиод
//  }
//  if (digitalRead(BUTTON_PIN_D1) == LOW) {  // Кнопка нажата (сигнал LOW из-за подтягивающего резистора)
//    digitalWrite(LED_PIN_D8, HIGH);         // Включаем светодиод
//  } else {
//    digitalWrite(LED_PIN_D8, LOW);          // Выключаем светодиод
//  }
//  if (digitalRead(BUTTON_PIN_D2) == LOW) {  // Кнопка нажата (@сигнал LOW из-за подтягивающего резистора)
//    digitalWrite(LED_PIN_D8, HIGH);         // Включаем светодиод
//  } else {
//    digitalWrite(LED_PIN_D8, LOW);          // Выключаем светодиод
//  }
  if (digitalRead(BUTTON_PIN_D3) == LOW) {  // Кнопка нажата (сигнал LOW из-за подтягивающего резистора)
    digitalWrite(LED_PIN_D8, HIGH);         // Включаем светодиод
  } else {
    digitalWrite(LED_PIN_D8, LOW);          // Выключаем светодиод
  }
}

