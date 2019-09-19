#include "Player.h"

Player::Player(){
    oIsTagged = false;
    oHasFlag = false;
}

Player::Player(const Player & p)
: oPosition(p.oPosition), oVelocity(p.oVelocity), oMaxSpeed(p.oMaxSpeed), oHasFlag(p.oHasFlag), oTeam(p.oTeam), oIsTagged(p.oIsTagged), oAttacker (p.oAttacker) {}

Player::Player(int index, XYCoordinate position, XYCoordinate velocity, double maxSpeed, bool hasFlag, bool team, bool isTagged, bool attacker, Field *field)
    :oPlayerIndex(index), oPosition(position), oVelocity(velocity), oMaxSpeed(maxSpeed), oHasFlag(hasFlag), oTeam(team), oIsTagged(isTagged),oAttacker(attacker), oField(field){}


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

void Player::FindPath(Field *field){
    XYCoordinate targetPos = XYCoordinate(0,0);                                                        //position of target player set = 0
    int targetIndex;
    XYCoordinate tarFlagVec;
    oHasTarget = false;

    if((oPosition.GetX() < 0) || (oPosition.GetX() > field->GetWidth()) || (oPosition.GetY() < 0) || (oPosition.GetY() > field->GetLength())){
        oIsTagged= true;
    }


    if(oAttacker == true){                                                                //Attacker -> find closest player
        for(int i = 0; i < (field->GetPlayerNum() * 2); i++){                                                         //loop to evaluate all players
            XYCoordinate evalPlayer = oPlayers[i];

            if((evalPlayer.GetTeam() != player->GetTeam()) && (evalPlayer.GetAttacker() == false)){        //if evaluated player is a defender on the other team take note
                XYCoordinate distVec = evalPlayer.GetPosition() - oPosition;                   //vector to evaluated player
                double distMag = distVec.Mag();                                                            //distance to evaluated player

                if((targetPos.GetX() == 0) && (targetPos.GetY() == 0)){                                    //if no target already set, set eval player = target
                    targetPos = evalPlayer.GetPosition();
                    player->SetHasTarget(true);
                }
                else{
                    XYCoordinate targetVec = targetPos - oPosition;                            //else only overwrite target if eval player is closer
                    double targetMag = targetVec.Mag();

                    if(distMag < targetMag){
                        targetPos = evalPlayer.GetPosition();
                        player->SetHasTarget(true);
                    }
                }
            }
        }
        XYCoordinate targetVec = targetPos - oPosition;                                        //Tagging -> if nearest defender close, drop flag and get tagged
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
            flagVec = oBlueFlagPos - oPosition;
        }
        else{
            flagVec = oRedFlagPos - oPosition;
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
                XYCoordinate distVec = evalPlayer.GetPosition() - oPosition;                //find vector to evaluated player
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
                        XYCoordinate tarVec = targetPos - oPosition;                        //else only overwrite target if sum of distances defender->attacker + attacker->flag is lesser than current target
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
            XYCoordinate moveVec = oRedFlagPos - oPosition;                 //player moves back toward their own flag
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
                XYCoordinate scoreVec = oRedFlagPos - oPosition;               //finds vector to own base to score
                double scoreMag = scoreVec.Mag();
                XYCoordinate targetVec = targetPos - oPosition;                //finds vector to nearest defender
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
                    XYCoordinate flagVec = oBlueFlagPos - oPosition;           //finds vector to enemy flag
                    double flagMag = flagVec.Mag();
                    XYCoordinate targetVec = targetPos - oPosition;            //finds vector to nearest defender
                    double targetMag = targetVec.Mag();

                    XYCoordinate moveVec = (flagVec / pow(flagMag, 1.0)) - (1.2 * targetVec / pow(targetMag,1.3)); //sets movement vector
                    velocity = player->GetMaxSpeed()  * moveVec / moveVec.Mag();
                }
                else{
                    XYCoordinate moveVec = oRedFlagPos - oPosition;            //if flag is taken move back to own base
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
                XYCoordinate targetVec = targetPos - oPosition;                //finds vector to target player
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
            XYCoordinate moveVec = oBlueFlagPos - oPosition;               //player moves back toward their own flag
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
                XYCoordinate scoreVec = oBlueFlagPos - oPosition;              //finds vector to own base to score
                double scoreMag = scoreVec.Mag();
                XYCoordinate targetVec = targetPos - oPosition;                //finds vector to nearest defender
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
                    XYCoordinate flagVec = oRedFlagPos - oPosition;            //finds vector to enemy flag
                    double flagMag = flagVec.Mag();
                    XYCoordinate targetVec = targetPos - oPosition;            //finds vector to nearest defender
                    double targetMag = targetVec.Mag();

                    XYCoordinate moveVec = (flagVec / pow(flagMag, 1.0)) - (1.2 * targetVec / pow(targetMag,1.3));//sets movement vector
                    velocity = player->GetMaxSpeed()  * moveVec / moveVec.Mag();
                }
                else{
                    XYCoordinate moveVec = oBlueFlagPos - oPosition;           //if flag is taken move back to own base
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
                XYCoordinate targetVec = targetPos - oPosition;            //finds vector to target player
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

void Player::Move(){ //Moves the player in the direction of the players velocity.
    XYCoordinate newPosition;
    newPosition = oPosition + oVelocity;
    oPosition = newPosition;
}


