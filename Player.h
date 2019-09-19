#ifndef PLAYER_H
#define PLAYER_H

#include "XYCoordinate.h"

class Player
{
public:
    Player();                                                                       //Constructors

    Player(const Player &);

    Player(XYCoordinate Position, XYCoordinate Velocity, double MaxSpeed, bool HasFlag, bool Team, bool IsTagged, bool Attacker);

    virtual ~Player();                                                             //Destructor

    void Print() const;
    void Move();

    inline void SetPosition(XYCoordinate);                                          //Set method declarations
    inline void SetVelocity(XYCoordinate);
    inline void SetMaxSpeed(double);
    inline void SetHasFlag(bool);
    //inline void SetTeam(bool);
    inline void SetIsTagged(bool);
    //inline void SetAttacker(bool);
    inline void SetHasTarget(bool);

    inline XYCoordinate GetPosition() const;                                        //Get method declarations
    inline XYCoordinate GetVelocity() const;
    inline double GetMaxSpeed() const;
    inline bool GetHasFlag() const;
    inline bool GetTeam() const;
    inline bool GetIsTagged() const;
    inline bool GetAttacker() const;
    inline bool GetHasTarget() const;

private:
    XYCoordinate oPosition, oVelocity;                                              //Define private members
    double oMaxSpeed;
    bool oHasFlag, oTeam, oIsTagged, oAttacker, oHasTarget;

};

inline void Player::SetPosition(XYCoordinate iPosition){oPosition = iPosition;}
inline void Player::SetVelocity(XYCoordinate iVelocity){oVelocity = iVelocity;}     //Get and set definitions
inline void Player::SetHasFlag(bool iHasFlag){oHasFlag = iHasFlag;}
inline void Player::SetIsTagged(bool iIsTagged){oIsTagged = iIsTagged;}
inline void Player::SetHasTarget(bool iHasTarget){oHasTarget = iHasTarget;}
inline void Player::SetMaxSpeed(double iMaxSpeed){oMaxSpeed = iMaxSpeed;}

inline XYCoordinate Player::GetPosition() const {return oPosition;}
inline XYCoordinate Player::GetVelocity() const {return oVelocity;}
inline double Player::GetMaxSpeed() const {return oMaxSpeed;}
inline bool Player::GetHasFlag() const {return oHasFlag;}
inline bool Player::GetTeam() const {return oTeam;}
inline bool Player::GetIsTagged() const {return oIsTagged;}
inline bool Player::GetAttacker() const {return oAttacker;}
inline bool Player::GetHasTarget() const {return oHasTarget;}


#endif // PLAYER_H
