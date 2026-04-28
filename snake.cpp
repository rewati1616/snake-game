#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

using namespace sf;
using namespace std;

int main() {
    srand(time(0));

    const int width = 600;
    const int height = 600;
    const int size = 20;

    RenderWindow window(VideoMode(width, height), "Snake Game (Shapes)");
    window.setFramerateLimit(10);

    // Snake body
    vector<Vector2i> snake;
    snake.push_back(Vector2i(10, 10));

    int dir = 0; // 0-down, 1-left, 2-right, 3-up

    // Fruit
    Vector2i fruit(rand() % (width / size), rand() % (height / size));

    RectangleShape snakeBlock(Vector2f(size, size));
    snakeBlock.setFillColor(Color::Green);

    RectangleShape fruitBlock(Vector2f(size, size));
    fruitBlock.setFillColor(Color::Red);

    while (window.isOpen()) {

        // ---------------- EVENTS ----------------
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // ---------------- CONTROLS ----------------
        if (Keyboard::isKeyPressed(Keyboard::Left))  dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up))    dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down))  dir = 0;

        // ---------------- MOVE SNAKE ----------------
        for (int i = snake.size() - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        if (dir == 0) snake[0].y += 1;
        if (dir == 1) snake[0].x -= 1;
        if (dir == 2) snake[0].x += 1;
        if (dir == 3) snake[0].y -= 1;

        // ---------------- COLLISION WITH FRUIT ----------------
        if (snake[0] == fruit) {
            snake.push_back(Vector2i(-1, -1));
            fruit = Vector2i(rand() % (width / size), rand() % (height / size));
        }

        // ---------------- WALL WRAP ----------------
        if (snake[0].x < 0) snake[0].x = width / size;
        if (snake[0].x > width / size) snake[0].x = 0;
        if (snake[0].y < 0) snake[0].y = height / size;
        if (snake[0].y > height / size) snake[0].y = 0;

        // ---------------- DRAW ----------------
        window.clear(Color::Black);

        // draw fruit
        fruitBlock.setPosition(fruit.x * size, fruit.y * size);
        window.draw(fruitBlock);

        // draw snake
        for (int i = 0; i < snake.size(); i++) {
            snakeBlock.setPosition(snake[i].x * size, snake[i].y * size);
            window.draw(snakeBlock);
        }

        window.display();
    }

    return 0;
}