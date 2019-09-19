#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "Player.h"

class Game {
public:
    Game();

    virtual ~Game();

    void CreatePlayers(int, Field*);
    void Simulate(Field*);

    inline int GetPlayerNum() const;
    inline Player GetPlayer(int n) const;
    inline std::vector<Player> GetPlayers() const;

    inline bool GetRun() const;
    inline bool GetBlueWin() const;
    inline bool GetRedWin() const;

    inline void SetPlayerNum(int);
    inline void SetRun(bool);

    Field oField;

private:
    std::vector<Player> oPlayers;
    int oPlayerNum;
    bool oRun, oBlueWin, oRedWin;

};

inline int Game::GetPlayerNum() const {return oPlayerNum;}
inline Player Game::GetPlayer(int n) const {return oPlayers[n];}
inline std::vector<Player> Game::GetPlayers() const {return oPlayers;}
inline bool Game::GetRun() const {return oRun;}
inline bool Game::GetBlueWin() const {return oBlueWin;}
inline bool Game::GetRedWin() const {return oRedWin;}

inline void Game::SetPlayerNum(int iNum){oPlayerNum = iNum;}
inline void Game::SetRun(bool iRun){oRun = iRun;}

#endif // FIELD_H
