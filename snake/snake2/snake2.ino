#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MAP_WIDTH = 128;  // Ширина карты
const int MAP_HEIGHT = 32;  // Высота карты (ограничение)

// Двумерный массив для карты (128x32)
char GameMap[MAP_WIDTH][MAP_HEIGHT];

// Структура для фруктов
class Food {
public:
    void SetFoodPosition() {
        bool validPosition = false;
        while (!validPosition) {
            food_x = 1 + (rand() % (MAP_WIDTH - 3));  // Генерация случайной позиции по X
            food_y = 1 + (rand() % (MAP_HEIGHT - 2)); // Генерация случайной позиции по Y
            if (GameMap[food_x][food_y] == ' ') {  // Проверка, что позиция свободна
                validPosition = true;
            }
        }
    }

    void DrawFood() {
        GameMap[food_x][food_y] = '*'; // Отображаем фрукт на карте
    }

    void ClearFood() {
        GameMap[food_x][food_y] = ' '; // Очищаем позицию фрукта
    }

    int GetFoodPositionX() { return food_x; }
    int GetFoodPositionY() { return food_y; }

private:
    int food_x;
    int food_y;
};

Food apple; // Создаем объект фрукта

// Структура для змеи
class Snake {
public:
    // Структура для позиции змеи (головы и тела)
    struct Position {
        int x;
        int y;
    };

    Snake() {
        // Начальная позиция головы змеи
        snakeHead.x = 10;
        snakeHead.y = 10;
        snakeDirection = RIGHT;
        body.push_back(snakeHead); // Добавляем голову в тело змеи
    }

    // Отображение змеи на карте
    void DrawSnake() {
        // Очищаем старую позицию змеи на дисплее
        for (int i = 0; i < body.size(); ++i) {
            int x = body[i].x;
            int y = body[i].y + 32; // Сдвиг по оси Y для отображения на экране
            if (i == 0) {
                display.drawPixel(x, y, SSD1306_BLACK); // Очищаем старую голову
            } else {
                display.drawPixel(x, y, SSD1306_BLACK); // Очищаем старое тело
            }
        }

        // Отображаем голову и тело змеи
        for (int i = 0; i < body.size(); ++i) {
            int x = body[i].x;
            int y = body[i].y + 32; // Сдвиг по оси Y для отображения на экране
            if (i == 0) {
                display.drawPixel(x, y, SSD1306_WHITE); // Отображаем голову змеи
            } else {
                display.drawPixel(x, y, SSD1306_WHITE); // Отображаем тело змеи
            }
        }
    }

    // Перемещение змеи
    void Move() {
        // Сохраняем старое положение головы перед перемещением
        prevHead = snakeHead;

        // Перемещаем голову змеи в выбранном направлении
        switch (snakeDirection) {
            case UP:    snakeHead.y -= 1; break;
            case DOWN:  snakeHead.y += 1; break;
            case LEFT:  snakeHead.x -= 1; break;
            case RIGHT: snakeHead.x += 1; break;
        }

        // Добавляем новую голову в тело змеи
        body.insert(body.begin(), snakeHead);

        // Если змея не съела фрукт, удаляем последний сегмент тела
        if (!(snakeHead.x == apple.GetFoodPositionX() && snakeHead.y == apple.GetFoodPositionY())) {
            body.pop_back(); // Удаляем последний сегмент тела
        }
    }

    // Установка направления движения
    void SetDirection(int dir) {
        snakeDirection = dir;
    }

    // Получение текущей позиции головы змеи
    int GetHeadX() { return snakeHead.x; }
    int GetHeadY() { return snakeHead.y; }

    bool CheckCollision() {
        // Проверка на столкновение с границами
        if (snakeHead.x <= 0 || snakeHead.x >= MAP_WIDTH - 1 || snakeHead.y <= 0 || snakeHead.y >= MAP_HEIGHT - 1) {
            return true;
        }
        
        // Проверка на столкновение с собственным телом
        for (int i = 1; i < body.size(); ++i) {
            if (snakeHead.x == body[i].x && snakeHead.y == body[i].y) {
                return true;
            }
        }
        return false;
    }

    // Получение тела змеи
    std::vector<Position> GetBody() {
        return body;
    }

    enum Direction { UP, DOWN, LEFT, RIGHT };

private:
    Position snakeHead;  // Голова змеи
    Position prevHead;   // Предыдущее положение головы (для очистки)
    int snakeDirection;  // Направление змеи
    std::vector<Position> body;  // Вектор для тела змеи
};

Snake snake;  // Создаем объект змеи

void setup() {
    Serial.begin(115200);

    // Инициализация дисплея
    Wire.begin(14, 12);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);  // Останавливаем выполнение, если дисплей не найден
    }

    display.clearDisplay();
    display.setTextSize(1); // Устанавливаем размер текста
    display.setTextColor(SSD1306_WHITE); // Цвет текста — белый

    // Инициализация карты (по умолчанию всё пусто)
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            GameMap[x][y] = ' '; // Пустой символ
        }
    }

    // Пример отрисовки рамки карты
    for (int x = 0; x < MAP_WIDTH; ++x) {
        GameMap[x][0] = '#'; // Верхняя граница
        GameMap[x][MAP_HEIGHT - 1] = '#'; // Нижняя граница
    }

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        GameMap[0][y] = '#'; // Левая граница
        GameMap[MAP_WIDTH - 1][y] = '#'; // Правая граница
    }

    // Установка позиции фрукта на карте
    apple.SetFoodPosition();
    apple.DrawFood(); // Отображаем фрукт

    // Отображаем карту с фруктом
    DrawGameMap();
}

void DrawGameMap() {
    display.clearDisplay(); // Очистить экран

    // Отображаем только игровую карту (128x32)
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            char tile = GameMap[x][y];
            if (tile == '#') {
                display.drawPixel(x, y + 32, SSD1306_WHITE); // Отображаем стены
            } else if (tile == ' ') {
                display.drawPixel(x, y + 32, SSD1306_BLACK); // Пустые клетки
            } else if (tile == '*') {
                display.drawPixel(x, y + 32, SSD1306_WHITE); // Отображаем фрукт
            }
        }
    }

    // Отображаем змейку (с помощью функции)
    snake.DrawSnake(); 

    // Отображаем дополнительную информацию на верхней части экрана
    display.setCursor(0, 0); // Устанавливаем курсор в верхнюю часть экрана
    display.setTextSize(1); // Размер текста
    display.print(F("Score: "));
    display.print(snake.GetBody().size() - 1); // Пример для отображения счета (минус 1 за голову)

    display.display(); // Обновляем экран
}

void loop() {
    // Чтение данных с монитора порта и управление направлением змеи
    if (Serial.available() > 0) {
        char input = Serial.read();  // Чтение введенной команды
        if (input == 'w') {
            snake.SetDirection(Snake::UP);
        } else if (input == 's') {
            snake.SetDirection(Snake::DOWN);
        } else if (input == 'a') {
            snake.SetDirection(Snake::LEFT);
        } else if (input == 'd') {
            snake.SetDirection(Snake::RIGHT);
        }
    }

    // Логика игры (например, перемещение объектов и обновление карты)
    snake.Move();  // Перемещаем змею

    // Проверка на съедение фрукта
    if (snake.GetHeadX() == apple.GetFoodPositionX() && snake.GetHeadY() == apple.GetFoodPositionY()) {
        apple.ClearFood();  // Очищаем старый фрукт
        apple.SetFoodPosition();  // Генерация нового фрукта
        apple.DrawFood();  // Отображаем новый фрукт
    }

    // Проверка на столкновение с границей или с собой
    if (snake.CheckCollision()) {
        Serial.println(F("Game Over!"));
        while (true);  // Завершаем игру
    }

    snake.DrawSnake();  // Отображаем змеиное тело как точку

    // Отображаем обновленную игровую карту
    DrawGameMap();

    delay(100);  // Задержка для замедления игры
}

