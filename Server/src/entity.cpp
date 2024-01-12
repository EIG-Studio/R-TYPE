/*
** EPITECH PROJECT, 2024
** 3
** File description:
** entity
*/

#include "server.hpp"

void Server::createBullet(Registry& registry, int posx, int posy)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    auto positionComponent = Position(std::make_pair(posx, posy));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(15);
    Type typeComponent = std::any_cast<EntityType>(Player_Projectile);
    HealthPoint healthPoint(1);
    Damage damage(3);
    Velocity velocityComponent = Velocity();

    velocityComponent.setVelocity(1, 0);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, damage);
    entity = registry.addComponent(entity, velocityComponent);
    entity = registry.addComponent(entity, HitBox(positionComponent.getPosition(), std::make_pair(50, 50)));

    std::ostringstream newPlayerProjectile;
    newPlayerProjectile << "PLAYER_PROJECTILE " << static_cast<int>(registry.getComponent(entity, idComponent).getID())
                        << " " << positionComponent.getPosition().first << " " << positionComponent.getPosition().second
                        << " " << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
                        << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayerProjectile.str());
}

std::size_t Server::createPlayer(Registry& registry)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(100, 100));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(5);
    Type typeComponent = std::any_cast<EntityType>(Player);
    HealthPoint healthPoint(20);
    HitBox hb = HitBox(positionComponent.getPosition(), std::make_pair(100, 40));
    Velocity velocityComponent = Velocity();
    velocityComponent.setVelocity(0, 0);
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, hb);
    entity = registry.addComponent(entity, velocityComponent);
    entity = registry.addComponent(entity, Damage(100));

    std::ostringstream newPlayer;
    newPlayer << "NEW_PLAYER " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
              << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
              << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
              << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer.str());
    return registry.getComponent(entity, idComponent).getID();
}

void Server::createArrow(Registry& registry)
{
    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});

    ID idComponent = ID();
    auto positionComponent = Position(playerPos);
    Size sizeComponent = Size(std::make_pair(1, 1));

    Entity entity = registry.createEntityWithID(idComponent);
    entity = registry.addComponent(entity, Position(playerPos));
    entity = registry.addComponent(entity, Renderer("../Client/assets/arrow.png"));
    entity = registry.addComponent(entity, Size(std::make_pair(1, 1)));
    entity = registry.addComponent(entity, Type(std::any_cast<EntityType>(Arrow_Player)));


    std::ostringstream arrowStr;
    arrowStr << "ARROW_PLAYER " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
             << " " << sizeComponent.getSize().first << " " << sizeComponent.getSize().second << "\n";
    addMessage(arrowStr.str());
}

int randNb(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}

void Server::createEnemy(Registry& registry)
{
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(randNb(1200, 2000), randNb(0, 500)));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(randNb(5, 10));
    Type typeComponent = std::any_cast<EntityType>(Enemy);
    HealthPoint healthPoint(5);
    HitBox hb = HitBox(positionComponent.getPosition(), std::make_pair(100, 50));
    Damage damage(1);

    Entity entity = registry.createEntity();
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, hb);
    entity = registry.addComponent(entity, damage);

    std::ostringstream newPlayer2;
    newPlayer2 << "NEW_ENEMY " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
               << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
               << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
               << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer2.str());
}

void Server::createBoss(Registry& registry)
{
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(randNb(1000, 1100), randNb(0, 500)));
    Size sizeComponent = Size(std::make_pair(2, 2));
    HitBox hitboxComponent = HitBox(positionComponent.getPosition(), std::make_pair(100, 100));
    Speed speedComponent(randNb(1, 3));
    Type typeComponent = std::any_cast<EntityType>(Boss);
    HealthPoint healthPointComponent(50);
    Damage damageComponent(1);

    Entity entity = registry.createEntity();
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, hitboxComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPointComponent);
    entity = registry.addComponent(entity, damageComponent);

    std::ostringstream newPlayer2;
    newPlayer2 << "NEW_BOSS " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
               << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
               << healthPointComponent.getHealthPoint() << " " << sizeComponent.getSize().first << " "
               << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer2.str());
}

void Server::createWall(Registry& registry, int posx, int posy, int sizex, int sizey)
{
    Entity wall = registry.createEntity();
    Position position = Position{std::make_pair(posx, posy)};
    Size size = Size{std::make_pair(sizex, sizey)};
    Type type = Type{std::any_cast<EntityType>(Wall)};
    HitBox hitbox = HitBox{position.getPosition(), size.getSize()};
    HealthPoint healthPoint = HealthPoint{10000};
    ID idComponent = ID();

    wall = registry.addComponent(wall, idComponent);
    wall = registry.addComponent(wall, position);
    wall = registry.addComponent(wall, healthPoint);
    wall = registry.addComponent(wall, type);
    wall = registry.addComponent(wall, hitbox);
}
