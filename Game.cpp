#include "Game.h"
#include "time.h"
#include <iostream>
#include <cmath>

Game::Game(){
    oRun = false;
    oBlueWin = false;
    oRedWin = false;
    srand(time(0));
}

Game::~Game(){}

void Game::CreatePlayers(int n, Field *field){                                                                   //CREATE PLAYERS FUNCTION
    oPlayers.clear();                                                                                   //resets previous values
    oPlayerNum = n;
    oBlueWin = false;
    oRedWin = false;

    for(int i = 0; i < oPlayerNum; i++){                                                                //creates oPlayerNum players per team
        double speed;
        bool attacker;
        if(i == 0 || i % 2 == 0){                                                                       //The first and every other player created is an attacker
            speed = field->GetASpeed();
            attacker = true;
        }
        else{                                                                                           //The rest are defenders
            speed = field->GetDSpeed();
            attacker = false;
        }
        XYCoordinate redPos(field->GetWidth() / 5, (i+1) * field->GetLength() / (oPlayerNum + 1));                           //set starting positions of attackers
        XYCoordinate bluePos(4 * field->GetWidth() / 5,(i+1) * field->GetLength() / (oPlayerNum + 1));

        XYCoordinate redRand(rand() % 11 - 5, rand() % 11 - 5);                                         //uses random number generator to randomize starting positions of players
        XYCoordinate blueRand (rand() % 11 - 5, rand() % 11 - 5);

        Player red(2 * i, redPos + 0.5 * redRand, XYCoordinate(0,0), speed, false, false, false, attacker, field);          //create players
        Player blue(2 * i + 1, bluePos + 0.5 * blueRand, XYCoordinate(0,0), speed, false, true, false, attacker, field);

        oPlayers.push_back(red);                                                                        //add players to std vector, red team are even indices - blue are odd
        field->oPositions.push_back(red.GetPosition());
        oPlayers.push_back(blue);
        field->oPositions.push_back(blue.GetPosition());
    }
    oRun = true;                                                                                        //program is ready to start running
}

void Game::Simulate(Field *field){                     //SIMULATE FUNCTION
    for(int i = 0; i < oPlayerNum*2; i++){      //loops FindPath function for all players
        oPlayers[i].FindPath(field);
    }

    for(int i = 0; i < oPlayerNum*2; i++){      //loops Move function for all players
        oPlayers[i].Move();
    }
}



