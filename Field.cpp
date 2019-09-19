#include "Field.h"
#include "Player.h"
#include "time.h"
#include <iostream>
#include <cmath>

Field::Field(){
    oBlueFlagHeld = false;
    oRedFlagHeld = false;
    oRun = false;
    oBlueWin = false;
    oRedWin = false;
    srand(time(0));
}

Field::Field(int Length, int Width, double ASpeed, double DSpeed)
    :oLength(Length), oWidth(Width), oASpeed(ASpeed), oDSpeed(DSpeed*oASpeed){
    oBlueFlagHeld = false;
    oRedFlagHeld = false;
    oRun = false;
    oBlueWin = false;
    oRedWin = false;
    srand(time(0));
}

Field::~Field(){}

void Field::CreatePlayers(int n){                                                                   //CREATE PLAYERS FUNCTION
    oPlayers.clear();                                                                                   //resets previous values
    oPlayerNum = n;
    oBlueFlagHeld = false;
    oRedFlagHeld = false;
    oBlueWin = false;
    oRedWin = false;

    for(int i = 0; i < oPlayerNum; i++){                                                                //creates oPlayerNum players per team
        double speed;
        bool attacker;
        if(i == 0 || i % 2 == 0){                                                                       //The first and every other player created is an attacker
            speed = oASpeed;
            attacker = true;
        }
        else{                                                                                           //The rest are defenders
            speed = oDSpeed;
            attacker = false;
        }
        XYCoordinate redPos(oWidth / 5, (i+1) * oLength / (oPlayerNum + 1));                           //set starting positions of attackers
        XYCoordinate bluePos(4 * oWidth / 5,(i+1) * oLength / (oPlayerNum + 1));

        XYCoordinate redRand(rand() % 11 - 5, rand() % 11 - 5);                                         //uses random number generator to randomize starting positions of players
        XYCoordinate blueRand (rand() % 11 - 5, rand() % 11 - 5);

        Player red(redPos + 0.5 * redRand, XYCoordinate(0,0), speed, false, false, false, attacker);          //create players
        Player blue(bluePos + 0.5 * blueRand, XYCoordinate(0,0), speed, false, true, false, attacker);

        oPlayers.push_back(red);                                                                        //add players to std vector, red team are even indices - blue are odd
        oPlayers.push_back(blue);
    }
    oRun = true;                                                                                        //program is ready to start running
}

void Field::PlayerMove(int i){                                                                      //MOVEMENT FUNCTION
    Player* player = &oPlayers[i];
    XYCoordinate targetPos = XYCoordinate(0,0);                                                        //position of target player set = 0
    int targetIndex;
    XYCoordinate tarFlagVec;
    player->SetHasTarget(false);

    if((player->GetPosition().GetX() < 0) || (player->GetPosition().GetX() > oWidth) || (player->GetPosition().GetY() < 0) || (player->GetPosition().GetY() > oLength)){
        player->SetIsTagged(true);
    }


    if(player->GetAttacker() == true){                                                                //Attacker -> find closest player
        for(int i = 0; i < (oPlayerNum * 2); i++){                                                         //loop to evaluate all players
            Player evalPlayer = oPlayers[i];

            if((evalPlayer.GetTeam() != player->GetTeam()) && (evalPlayer.GetAttacker() == false)){        //if evaluated player is a defender on the other team take note
                XYCoordinate distVec = evalPlayer.GetPosition() - player->GetPosition();                   //vector to evaluated player
                double distMag = distVec.Mag();                                                            //distance to evaluated player

                if((targetPos.GetX() == 0) && (targetPos.GetY() == 0)){                                    //if no target already set, set eval player = target
                    targetPos = evalPlayer.GetPosition();
                    player->SetHasTarget(true);
                }
                else{
                    XYCoordinate targetVec = targetPos - player->GetPosition();                            //else only overwrite target if eval player is closer
                    double targetMag = targetVec.Mag();

                    if(distMag < targetMag){
                        targetPos = evalPlayer.GetPosition();
                        player->SetHasTarget(true);
                    }
                }
            }
        }
        XYCoordinate targetVec = targetPos - player->GetPosition();                                        //Tagging -> if nearest defender close, drop flag and get tagged
        double targetMag = targetVec.Mag();                                                                    //distance to nearest defender
        if(targetMag < 1){                                                                                     //if less than one get tagged
            player->SetIsTagged(true);
            player->SetMaxSpeed(oASpeed);
            if(player->GetHasFlag() == true){                                                                  //drop and reset flag
                player->SetHasFlag(false);
                if(player->GetTeam() == false){
                    oBlueFlagHeld = false;
                }
                else{
                    oRedFlagHeld = false;
                }
            }
        }
        XYCoordinate flagVec;                                                                              //Flag - if close to flag, pick up flag
        if(player->GetTeam() == false){                                                                        //vector to flag, flagvec depends on team
            flagVec = oBlueFlagPos - player->GetPosition();
        }
        else{
            flagVec = oRedFlagPos - player->GetPosition();
        }
        double flagMag = flagVec.Mag();                                                                        //distance to flag

        if(flagMag < 1){
            player->SetHasFlag(true);
            player->SetMaxSpeed(0.95 * oASpeed);                                                                    //If holding flag slow down

            if(player->GetTeam() == false){
                oBlueFlagHeld = true;
            }
            else{
                oRedFlagHeld = true;
            }
        }
    }

    else {                                                                                          //Defender -> find 'high priority' player
        for(int i = 0; i < (oPlayerNum * 2); i++){                                                      //loop to evaluate all players
            Player evalPlayer = oPlayers[i];

            if((evalPlayer.GetTeam() != player->GetTeam()) && (evalPlayer.GetAttacker() == true) && (evalPlayer.GetIsTagged() == false)){//if player is an attacker on the other team take note
                XYCoordinate distVec = evalPlayer.GetPosition() - player->GetPosition();                //find vector to evaluated player
                double distMag = distVec.Mag();

                XYCoordinate evalFlagVec;                                                               //find distance between evaluated player and flag

                if(evalPlayer.GetHasFlag() == true){                                                    //If evalPlayer holds flag, target
                    targetPos = evalPlayer.GetPosition();
                    targetIndex = i;
                    tarFlagVec = evalFlagVec;
                    player->SetHasTarget(true);
                }
                else if(((player->GetTeam() == false) && (evalPlayer.GetPosition().GetX() < oWidth/2)) || ((player->GetTeam() == true) && (evalPlayer.GetPosition().GetX() > oWidth/2))){
                    if(evalPlayer.GetTeam() == false){                                                  //find vector possible target and flag
                        evalFlagVec = oBlueFlagPos - evalPlayer.GetPosition();
                    }
                    else{
                        evalFlagVec = oRedFlagPos - evalPlayer.GetPosition();
                    }

                    double evalFlagMag = evalFlagVec.Mag();

                    if((targetPos.GetX() == 0)&&(targetPos.GetY() == 0)){                               //if no target set, set target
                        targetPos = evalPlayer.GetPosition();
                        targetIndex = i;
                        tarFlagVec = evalFlagVec;
                        player->SetHasTarget(true);
                    }
                    else{
                        XYCoordinate tarVec = targetPos - player->GetPosition();                        //else only overwrite target if sum of distances defender->attacker + attacker->flag is lesser than current target
                        double tarMag = tarVec.Mag();
                        double tarFlagMag = tarFlagVec.Mag();

                        if((0.5 * evalFlagMag + distMag) < (0.5 * tarFlagMag + tarMag)){
                            targetPos = evalPlayer.GetPosition();
                            targetIndex = i;
                            tarFlagVec = evalFlagVec;
                            player->SetHasTarget(true);
                        }
                    }
                }
            }
        }
    }

    if(player->GetTeam() == false){                                             //MOVE -> red team
        if(player->GetIsTagged() == true){                                          //Tagged player
            XYCoordinate moveVec = oRedFlagPos - player->GetPosition();                 //player moves back toward their own flag
            XYCoordinate velocity = player->GetMaxSpeed()  * moveVec/ moveVec.Mag();    //sets velocity magnitude to player maxspeed
            player->SetVelocity(velocity);
            player->Move();                                                             //updates players position

            if(moveVec.Mag() < 1){                                                      //if back to own flag get untagged
                player->SetIsTagged(false);
            }
        }
        else if(player->GetAttacker() == true){                                     //Attacker
            if(player->GetHasTarget() == false){
                targetPos = oBlueFlagPos;                                               //if attacker has no target, set flag as target
            }

            else if(player->GetHasFlag() == true){                                      //Player has flag
                XYCoordinate scoreVec = oRedFlagPos - player->GetPosition();               //finds vector to own base to score
                double scoreMag = scoreVec.Mag();
                XYCoordinate targetVec = targetPos - player->GetPosition();                //finds vector to nearest defender
                double targetMag = targetVec.Mag();

                XYCoordinate moveVec = (scoreVec / scoreMag) - (targetVec / targetMag);    //sets movement vector
                XYCoordinate velocity = player->GetMaxSpeed()  * moveVec/ moveVec.Mag();
                player->SetVelocity(velocity);
                player->Move();                                                            //updates players position

                if(scoreMag < 1){                                                          //if player scores stop running
                    oRun = false;
                    oRedWin = true;
                }
            }
            else{                                                                      //Default: active player
                XYCoordinate velocity = XYCoordinate(0,0);
                if(oBlueFlagHeld == false){
                    XYCoordinate flagVec = oBlueFlagPos - player->GetPosition();           //finds vector to enemy flag
                    double flagMag = flagVec.Mag();
                    XYCoordinate targetVec = targetPos - player->GetPosition();            //finds vector to nearest defender
                    double targetMag = targetVec.Mag();

                    XYCoordinate moveVec = (flagVec / pow(flagMag, 1.0)) - (1.2 * targetVec / pow(targetMag,1.3)); //sets movement vector
                    velocity = player->GetMaxSpeed()  * moveVec / moveVec.Mag();
                }
                else{
                    XYCoordinate moveVec = oRedFlagPos - player->GetPosition();            //if flag is taken move back to own base
                    if(moveVec.Mag() > oASpeed){
                        velocity = player->GetMaxSpeed() * moveVec / moveVec.Mag();
                    }
                }
                player->SetVelocity(velocity);
                player->Move();                                                            //updates players position
            }
        }
        else{                                                                      //Defender
            if(player->GetHasTarget() == true){
                XYCoordinate targetVec = targetPos - player->GetPosition();                //finds vector to target player
                double targetMag = targetVec.Mag();
                Player target = oPlayers[targetIndex];                                     //finds target player from index
                XYCoordinate tarVelVec = target.GetVelocity();                             //finds targets velocity

                XYCoordinate moveVec = (targetVec / targetMag) + (tarVelVec * 10);        //aims slightly ahead of target
                XYCoordinate velocity = player->GetMaxSpeed()  * moveVec/ moveVec.Mag();
                player->SetVelocity(velocity);
                player->Move();                                                            //updates players position
            }
        }
    }
    else{                                                                      //MOVE -> blue team
        if(player->GetIsTagged() == true){                                         //Tagged player
            XYCoordinate moveVec = oBlueFlagPos - player->GetPosition();               //player moves back toward their own flag
            XYCoordinate velocity = player->GetMaxSpeed()  * moveVec/ moveVec.Mag();   //sets velocity magnitude equal to maxspeed
            player->SetVelocity(velocity);
            player->Move();                                                            //updates players position

            if(moveVec.Mag() < 1){
                player->SetIsTagged(false);                                            //if back at own flag untag
            }
        }
        else if(player->GetAttacker() == true){                                    //Attacker
            if(player->GetHasTarget() == false){
                targetPos = oRedFlagPos;                                               //if player has no target set flag as target
            }

            else if(player->GetHasFlag() == true){                                     //Player has flag
                XYCoordinate scoreVec = oBlueFlagPos - player->GetPosition();              //finds vector to own base to score
                double scoreMag = scoreVec.Mag();
                XYCoordinate targetVec = targetPos - player->GetPosition();                //finds vector to nearest defender
                double targetMag = targetVec.Mag();

                XYCoordinate moveVec = (scoreVec/scoreMag)-(targetVec/targetMag);          //sets movement vector
                XYCoordinate velocity = player->GetMaxSpeed()  * moveVec/ moveVec.Mag();
                player->SetVelocity(velocity);
                player->Move();                                                            //updates players position

                if(scoreMag < 1){
                    oRun = false;                                                          //if player scores stop program running
                    oBlueWin = true;
                }
            }
            else{                                                                      //Default: active player
                XYCoordinate velocity = XYCoordinate(0,0);
                if(oRedFlagHeld == false){
                    XYCoordinate flagVec = oRedFlagPos - player->GetPosition();            //finds vector to enemy flag
                    double flagMag = flagVec.Mag();
                    XYCoordinate targetVec = targetPos - player->GetPosition();            //finds vector to nearest defender
                    double targetMag = targetVec.Mag();

                    XYCoordinate moveVec = (flagVec / pow(flagMag, 1.0)) - (1.2 * targetVec / pow(targetMag,1.3));//sets movement vector
                    velocity = player->GetMaxSpeed()  * moveVec / moveVec.Mag();
                }
                else{
                    XYCoordinate moveVec = oBlueFlagPos - player->GetPosition();           //if flag is taken move back to own base
                    if(moveVec.Mag() > oASpeed){
                        velocity = player->GetMaxSpeed() * moveVec / moveVec.Mag();
                    }
                }
                player->SetVelocity(velocity);
                player->Move();                                                            //updates players position
            }
        }
        else{                                                                      //Defender
            if(player->GetHasTarget() == true){
                XYCoordinate targetVec = targetPos - player->GetPosition();            //finds vector to target player
                double targetMag = targetVec.Mag();
                Player target = oPlayers[targetIndex];                                 //finds target player from index
                XYCoordinate tarVelVec = target.GetVelocity();                         //finds targets velocity

                XYCoordinate moveVec = (targetVec / targetMag) + (tarVelVec * 10);    //aims slightly ahead of target
                XYCoordinate velocity = player->GetMaxSpeed()  * moveVec/ moveVec.Mag();
                player->SetVelocity(velocity);
                player->Move();                                                        //updates players position
            }
        }
    }
}

void Field::Simulate(){                     //SIMULATE FUNCTION
    for(int i = 0; i < oPlayerNum*2; i++){      //loops PlayerMove function for all players
        this->PlayerMove(i);
    }
}



