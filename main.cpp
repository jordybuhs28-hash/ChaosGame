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
//the two  commetted out lines are to make the creen opne up to full screen size.
//	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
//	sf::RenderWindow window(desktop, "Chaos Game", sf::Style::Fullscreen);

	 window.setFramerateLimit(60);

    std::vector<sf::Vector2f> vertices;
    std::vector<sf::Vector2f> points;

    sf::Font font;
    if (!font.loadFromFile("modeseven.ttf")) {
        return -1; // ensure font file exists in project folder
    }
    sf::Text instructions("Click N vertices (>=3), then right-click to set start point", font, 20);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(10, 10);

    sf::Vector2f startPoint;
    bool started = false;
    bool finished = false;
    int lastIndex = -1;
    const int MAX_POINTS = 20000; // threshold for completion (adjust as needed)

    srand(static_cast<unsigned>(time(nullptr)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);

                if (!started) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        vertices.push_back(click);
                    } else if (event.mouseButton.button == sf::Mouse::Right && vertices.size() >= 3) {
                        startPoint = click;
                        points.push_back(startPoint);
                        started = true;
                        instructions.setString("Generating Chaos Game...");
                    }
                }
            }


            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    // reset everything
                    vertices.clear();
                    points.clear();
                    started = false;
                    finished = false;
                    lastIndex = -1;
                    instructions.setString("Click N vertices (>=3), then right-click to set start point");
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Chaos Game algorithm
        if (started && !finished) {
            float r = getRatio(vertices.size());
            sf::Vector2f current = points.back();

            for (int i = 0; i < 500 && !finished; i++) { // generate 500 points per frame
                if (points.size() >= MAX_POINTS) {
                    finished = true;
                    instructions.setString("Fractal complete! Press R to restart or Esc to quit.");
                    break;
                }

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

	// draw lines between vertices (polygon outline)
	if (!started && vertices.size() >= 2) {
		for (size_t i = 0; i < vertices.size() - 1; ++i) {
			sf::Vertex line[] = {
				sf::Vertex(vertices[i], sf::Color::Yellow),
				sf::Vertex(vertices[i + 1], sf::Color::Yellow)
			};
			window.draw(line, 2, sf::Lines);
		}
            	// close the shape
		sf::Vertex closingLine[] = {
                	sf::Vertex(vertices.back(), sf::Color::Yellow),
                	sf::Vertex(vertices[0], sf::Color::Yellow)
		};
		window.draw(closingLine, 2, sf::Lines);
	}

		//draw vertices
   //	 for (auto &v : vertices) {
    //   		 outline.push_back(sf::Vertex(v, sf::Color::Yellow));
    //	}
    	// close the shape by connecting last to first
    //	outline.push_back(sf::Vertex(vertices[0], sf::Color::Yellow));
  //  		window.draw(&outline[0], outline.size(), sf::LinesStrip);
//	}

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

