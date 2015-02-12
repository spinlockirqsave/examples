/*
 * @author peterg
 */

#include <iostream>

class SpaceShip;
class Asteroid;

class GameObject {
public:
    //virtual void collide( GameObject& other) = 0;
    virtual void collide( SpaceShip& other) = 0;
    virtual void collide( Asteroid& other) = 0;
};

class SpaceShip : public GameObject {
public:
    virtual void collide( GameObject& other) { std::cout << "SpaceShip-GameObject\n";}
    virtual void collide( SpaceShip& other) { std::cout << "SpaceShip-SpaceShip\n";}
    virtual void collide( Asteroid& other) { std::cout << "SpaceShip-Asteroid\n";}
};

class Asteroid  : public GameObject {
public:
    virtual void collide( GameObject& other) { std::cout << "Asteroid-GameObject\n";}
    virtual void collide( SpaceShip& other) { std::cout << "Asteroid-SpaceShip\n";}
    virtual void collide( Asteroid& other) { std::cout << "Asteroid-Asteroid\n";}
};

int main(){
    SpaceShip s;
    Asteroid a;
    s.collide( a);              //SpaceShip-Asteroid

    GameObject *gp = &s;
    gp->collide( a);            //SpaceShip-Asteroid

    gp = &a;
    gp->collide( s);            //Asteroid-SpaceShip
}
