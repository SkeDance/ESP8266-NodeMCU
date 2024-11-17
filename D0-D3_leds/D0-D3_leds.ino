#define D0 16 //  соответствует D0
#define D1 5  //  соответствует D1
#define D2 4  //  соответствует D2
#define D3 0  //  соответствует D3

void setup() {
  // Настройка GPIO5 как выходного
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);



  // Установка постоянного высокого уровня
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  // Сообщение для подтверждения
  Serial.begin(115200);
  Serial.println("GPIO5 (D1) установлен в высокий уровень.");
}

void loop() {
  // Основной цикл пуст, так как уровень постоянный
}

