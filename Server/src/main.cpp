/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <dlfcn.h>
#include <thread>


int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode(800, 600), "R-TYPE");
        Registry registry = Registry();
        Entity entity;
        entity = registry.createEntity();
        entity = registry.addComponent(entity, Position(std::make_pair(200, 600)));
        // registry.addComponent(entity, Velocity());
        // registry.addComponent(entity, Speed(0));
        // registry.addComponent(entity, HealthPoint(100));
        // registry.addComponent(entity, Damage(0));
        // registry.addComponent(entity, Shooter());
        entity = registry.addComponent(entity, Renderer("../Client/assets/Cars/cars/1.png"));
        entity = registry.addComponent(entity, Type(std::any_cast<EntityType>(Player)));
        // if (registry.hasComponent(entity, Position());

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Mettre à jour le jeu ici

            // Effacer l'écran
            window.clear();

            // Dessiner les éléments du jeu ici

            // Afficher la fenêtre


            registry.systemsManager(window);
            window.display();
        }

        Server server;


        std::thread serverThread(&Server::startListening, &server);
        std::thread serverThread2(&Server::startSending, &server);
        serverThread.join();
        serverThread2.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
