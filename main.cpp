#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MusicPlayer.hpp"
#include "History.hpp"

using namespace std;


int main(int argc, char ** argv) {

	cout << "Cachalot 2 - 2013" << endl;
	
	std::string historyPath, musicPath;
	
	// get history path
	if (argc >= 2)
		historyPath.assign(argv[1]);
	else {
		cout << "Usage : " << argv[0] << " <historic_file_path> [music_file_path]" << endl;
	}
	
	// get music path
	if (argc >= 3)
		musicPath.assign(argv[2]);
	
	// create GL context
	sf::Context context;
	
	MusicPlayer player("data/widget.png", "data/jennaSue.ttf");
	sf::Vector2u windowSize = player.getSize();
	
	std::string windowTitle = "Cachalot 2";
	
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle, sf::Style::Close);
    window.setFramerateLimit(60);
	
	History history(historyPath);
	
	// if there is no argument, play latest played music
	if (musicPath.empty())
		musicPath = history.getLast();
	
	// get saved time
	float inOut_offset = history.getTime(musicPath);
	
	// start playing
	bool musicValid = player.play(musicPath, inOut_offset);
	
	// change window title
	if (musicValid) {
		//windowTitle += " - " + musicPath;
		//window.setTitle(windowTitle);
		cout << "Playing music : '" << musicPath << "'" << endl;
	}
	
	bool windowHasFocus = true;
	
    // run the main loop
    bool running = true;
    while (running) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            } else if (event.type == sf::Event::GainedFocus) {
				windowHasFocus = true;
			} else if (event.type == sf::Event::LostFocus) {
				windowHasFocus = false;
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
                    running = false;
				} else if (event.key.code == sf::Keyboard::Space) {
					player.toggle();
				}  
            } else if (event.type == sf::Event::MouseMoved) {
            } else if (event.type == sf::Event::MouseButtonPressed) {
            } else if (event.type == sf::Event::MouseButtonReleased) {
            }
        }
		
		player.update(window.mapPixelToCoords(sf::Mouse::getPosition(window)),
					  sf::Mouse::isButtonPressed(sf::Mouse::Left) && windowHasFocus);
		
		// Drawing stuff
        window.clear(sf::Color::White);
		window.draw(player);
        window.display();
    }

	if (musicValid) {
		std::cout << "Final offset = " << inOut_offset << std::endl;
		history.setTime(musicPath, inOut_offset);
	}
	
    return EXIT_SUCCESS;
}

