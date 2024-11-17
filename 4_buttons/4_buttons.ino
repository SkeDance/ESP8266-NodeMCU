#define PIN_HIGH 5  // GPIO5, соответствует D1

void setup() {
  // Настройка GPIO5 как выходного
  pinMode(PIN_HIGH, OUTPUT);

  // Установка постоянного высокого уровня
  digitalWrite(PIN_HIGH, HIGH);

  // Сообщение для подтверждения
  Serial.begin(115200);
  Serial.println("GPIO5 (D1) установлен в высокий уровень.");
}

void loop() {
  // Основной цикл пуст, так как уровень постоянный
}

