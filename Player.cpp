#include "Player.h"
#include <iostream>

Player::Player(){
    oIsTagged = false;
    oHasFlag = false;
}

Player::Player(const Player & p)
: oPosition(p.oPosition), oVelocity(p.oVelocity), oMaxSpeed(p.oMaxSpeed), oHasFlag(p.oHasFlag), oTeam(p.oTeam), oIsTagged(p.oIsTagged), oAttacker (p.oAttacker) {}

Player::Player(XYCoordinate Position, XYCoordinate Velocity, double MaxSpeed, bool HasFlag, bool Team, bool IsTagged, bool Attacker)
    :oPosition(Position), oVelocity(Velocity), oMaxSpeed(MaxSpeed), oHasFlag(HasFlag), oTeam(Team), oIsTagged(IsTagged),oAttacker(Attacker){}


Player::~Player(){}

void Player::Print() const { //Prints the players details
    std::cout << "Position - ";
    oPosition.Print();
    std::cout << "Velocity - ";
    oVelocity.Print();
    std::cout << "MaxSpeed - " << oMaxSpeed << std::endl;
    std::cout << std::boolalpha << "HasFlag - " << oHasFlag << std::endl;
    std::cout << std::boolalpha << "Team - " << oTeam << std::endl;
    std::cout << std::boolalpha << "IsTagged - " << oIsTagged << std::endl;
    std::cout << std::boolalpha << "Attacker - " << oAttacker << std::endl;
}

void Player::Move(){ //Moves the player in the direction of the players velocity.
    XYCoordinate newPosition;
    newPosition = oPosition + oVelocity;
    oPosition = newPosition;
}
