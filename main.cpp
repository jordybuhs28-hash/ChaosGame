// ChaosGame - Sierpinski Triangle & Extra Credit Polygons
// Jordyn Buhs

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

float getRatio(int sides) {
    switch(sides) {
        case 3: return 0.5f;                // Triangle
        case 4: return 0.5f;                // Square
        case 5: return 1.0f / 1.618f;       // Pentagon (golden ratio)
        case 6: return 2.0f / 3.0f;         // Hexagon
        case 7: return 0.692f;              // Heptagon
        case 8: return 0.707f;              // Octagon
        case 9: return 0.742f;              // Nonagon
        case 10: return 0.764f;             // Decagon
        default: return 0.5f;               // Fallback
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chaos Game");
    window.setFramerateLimit(60);

    std::vector<sf::Vector2f> vertices;
    std::vector<sf::Vector2f> points;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1; // ensure font file exists
    }
    sf::Text instructions("Click N vertices, then a start point", font, 20);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(10, 10);

    sf::Vector2f startPoint;
    bool started = false;
    int lastIndex = -1;

    srand(static_cast<unsigned>(time(nullptr)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);

                // Collect vertices until user decides enough (>=3)
                if (!started) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        vertices.push_back(click);
                    } else if (event.mouseButton.button == sf::Mouse::Right && vertices.size() >= 3) {
                        // Right-click sets starting point
                        startPoint = click;
                        points.push_back(startPoint);
                        started = true;
                        instructions.setString("Generating Chaos Game...");
                    }
                }
            }
        }

        // Chaos Game algorithm
        if (started) {
            float r = getRatio(vertices.size());
            sf::Vector2f current = points.back();
            for (int i = 0; i < 100; i++) {
                int rIndex;
                do {
                    rIndex = rand() % vertices.size();
                } while(vertices.size() >= 4 && rIndex == lastIndex);

                current = current + r * (vertices[rIndex] - current);
                points.push_back(current);
                lastIndex = rIndex;
            }
        }

        // Draw everything
        window.clear(sf::Color::Black);
        window.draw(instructions);

        // draw vertices
        for (auto &v : vertices) {
            sf::CircleShape dot(4);
            dot.setFillColor(sf::Color::Red);
            dot.setPosition(v);
            window.draw(dot);
        }

        // draw chaos points
        for (auto &p : points) {
            sf::CircleShape dot(1);
            dot.setFillColor(sf::Color::Green);
            dot.setPosition(p);
            window.draw(dot);
        }

        window.display();
    }

    return 0;
}

