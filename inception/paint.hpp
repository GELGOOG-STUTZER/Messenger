/*
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iterator>


#define path_to_melody_one "data/sounds/sp-cheers.wav"
#define path_to_background "data/image/fon_memecria3.jpg"
#define path_to_sound "data/image/icon_sound.jpg"

//эти глобальные переменные необходимы для проигрывания саунда
//issue: add melody in global_variables
sf::Sound ringthone_one;
sf::SoundBuffer melody_one;
sf::Vector2u pos;
*/

#include "global_variables.hpp"
#include "personal_settings.hpp"

namespace screen {                                                                              // Everything required for screen operation is stored here
    class Point {                                                                               // Class for storing information about a single 2D point
        private:                                                                                //
            double x, y;                                                                        // Coordinates
        public:                                                                                 //
            Point(double _x, double _y) : x(_x), y(_y) {}                                       // Constructor
            Point() : x(0), y(0) {}                                                             // Another constructor
    };                                                                                          //
    
    class Icons {                                                                               // Everything required for operations with images is stored here
        private:                                                                                //
            std::string path_to_image;                                                          // Path to the file containing image
            double height, width;                                                               // Image's height and width in pixels
            Point vertex;                                                                       // This point represents the upper left corner of the image
        public:                                                                                 //
            Icons(std::string path);                                                            // 3 different constructors
            Icons(std::string path, Point _vertex);                                             //
            Icons(std::string path, Point _vertex, double _height, double _width) : path_to_image(path), vertex(_vertex), height(_height), width(_width) {}
    };

    class Button {                                                                              // Everything required for operations with buttons is stored here
        private:                                                                                //
            std::vector<Icons> Buttons;                                                         // Single vector contains information about all buttons
        public:                                                                                 //
            Button(Icons _icon);                                                                // 2 constructors
            Button();                                                                           //
    };                                                                                          //

    class Background {                                                                          // Class used for operations with background
        private:                                                                                //
            sf::RenderWindow window;                                                            // Reference: https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
            void play_sound();                                                                  // Different functions used for interaction with the active window
            void my_clear();                                                                    //
        public:                                                                                 //
            Background(int height, int width) : window(sf::VideoMode(height, width), "MEMECRIA") {}
            void draw_on_window(const char path_to_image[]);                                    //
            void draw_on_window(const char path_to_image[], int x, int y);                      //
            void draw_on_window(sf::Color colour);                                              //
            void handler_button();                                                              //
            bool is_open() const;                                                               //
            void display();                                                                     //
            void enter_button(sf::Vector2i vec);                                                //
    };

    Icons::Icons(std::string path, Point _vertex) {
        sf::Texture image;
        image.loadFromFile(path);
        sf::Vector2u pos = image.getSize();
        path_to_image = path;
        vertex = _vertex;
        height = pos.y;
        width = pos.x;
    }

    Icons::Icons(std::string path) {
        Point p;
        Icons(path, p);
    }
    
    Button::Button() {
        Icons _icon = {0};
        Buttons.push_back(_icon);
    }

    Button::Button(Icons _icon) {
        Buttons.push_back(_icon);
    }

    void Background::draw_on_window(const char path_to_image[]) {
        sf::Texture image;
        image.loadFromFile(path_to_image);
        sf::Sprite sprite_image;
        sprite_image.setTexture(image);
        sprite_image.setPosition(0, 0);
        window.draw(sprite_image);
    }
    
    void Background::draw_on_window(const char path_to_image[], int x, int y) {
        sf::Texture image;
        image.loadFromFile(path_to_image);
        sf::Sprite sprite_image;
        sprite_image.setTexture(image);
        sprite_image.setPosition(x, y);
        window.draw(sprite_image);
    }
    
    void Background::draw_on_window(sf::Color colour) {
        window.clear(colour);
    }

    void Background::my_clear() {
        window.clear();
        window.close();
        window.display();
    }

    void Background::handler_button() {
        sf::Event event;
        while ( window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }
            else if ( event.type == sf::Event::KeyPressed ) {
                play_sound();
            }
            else if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
                //std::cout << "LEFT CLICK" << std::endl;
                sf::Vector2i position_mouse = sf::Mouse::getPosition(window);
                //std::cout << position_mouse.x << "= x\n" << position_mouse.y << "= y\n" << std::endl;
                enter_button(position_mouse);
            }
        }
    }

    bool Background::is_open() const {
        pos = window.getSize();
        return window.isOpen();
    }

    void Background::display() {
        window.display();
    }
    /*
    //эти глобальные переменные необходимы для проигрывания саунда
    //issue: add melody in global_variables
    sf::Sound ringthone_one;
    sf::SoundBuffer melody_one;
    */
    void Background::play_sound() {
        if ( !melody_one.loadFromFile(path_to_melody_one) ) {
            std::cout << "ERROR. Melody_one isn't detected" << std::endl;
        }
        ringthone_one.setBuffer(melody_one);
        ringthone_one.play();
    }

    void Background::enter_button(sf::Vector2i position) {
        float X = position.x;
        float Y = position.y;
        //add kx, ky in global variables
        float kx = pos.x / 1240.0;
        float ky = pos.y / 800.0;
        //std::cout << kx << " = kx\n" << ky << " = ky\n";
        if ( (X > 345 * kx) & (Y > 70 * ky) & (X < 965 * kx) & (Y < 175 * ky) ) {
            std::cout << "SIGN IN/SIGN UP\n";
        }
        else if ( (X > 340 * kx) & (Y > 210 * ky) & (X < 975 * kx) & (Y < 285 * ky) ) {
            //std::cout << "PERSONAL SETTINGS\n";
            window.clear();
            personal_settings();
        }
        
    }
}


