#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <stdexcept>

namespace michLeag
{
    class Team
    {
        public:
        std::string TeamName;
        double level;
        int totalWinPoint;
        int totalLosePoint;
        int totalWin;
        int totalLose;

        Team(const std::string& newName, double newLevel);
    };

    class Leauge
    {
        private:
        struct Schedule
        {
            struct Game
            {
                ulong HomeTeam;
                ulong OutTeam;
                int HomePoint;
                int OutPoint;
                int win;
                Game()
                {
                    this->HomeTeam = 0;
                    this->OutTeam = 0;
                    this->HomePoint = 0;
                    this->OutPoint= 0;
                    this->win = 0;
                }
                Game(ulong NewHome, ulong NewOut)
                {
                    this->HomeTeam = NewHome;
                    this->OutTeam = NewOut;
                    this->HomePoint = 0;
                    this->OutPoint = 0;
                    this->win = 0;
                }
                void set_points(int NewHomePoint, int NewOutPoint)
                {
                    this->HomePoint = NewHomePoint;
                    this->OutPoint = NewOutPoint;
                    if(this->HomePoint>OutPoint)
                    {
                        win = 1;
                    }
                    else
                    {
                       win = -1;
                    }
                }
            };

            std::vector<std::vector<Game>> my_games;
            static const int play_days = 38;
            static const int Games_in_day = 10;
            Schedule():my_games(play_days, std::vector<Game>(Games_in_day))
            {
                int range = int(this->my_games.size()/2);
                for(int i=range; i>0; i--)
                {
                    {
                        this->my_games[ulong(range-i)][0] = Game(0,ulong(i));
                        this->my_games[ulong(range+i-1)][0] = Game(ulong(i),(0));
                    }
                    for(int k = 1; k<((range+1)/2) ; k++)
                    {   
                        if(i+k<range+1)
                        {
                            if(i-k>0)
                            {
                                this->my_games[ulong(range-i)][ulong(k)] = Game(ulong(i+k),ulong(i-k));
                                this->my_games[ulong(range+i-1)][ulong(k)] = Game(ulong(i-k),ulong(i+k));
                            }
                            else
                            {
                                this->my_games[ulong(range-i)][ulong(k)] = Game(ulong(i+k),(ulong((i-k+range)%(range+1))));
                                this->my_games[ulong(range+i-1)][ulong(k)] = Game(ulong((i-k+range)%(range+1)),ulong(i+k));
                            }
                        }
                        else
                        {
                            if(i-k>0)
                            {
                                    this->my_games[ulong(range-i)][ulong(k)] = Game(ulong((i+k+1)%(range+1)),ulong((i-k)));
                                    this->my_games[ulong(range+i-1)][ulong(k)] = Game((ulong(i-k)),ulong((i+k+1)%(range+1)));
                            }
                            else
                            {
                                this->my_games[ulong(range-i)][ulong(k)] = Game(ulong((i+k+1)%(range+1)),ulong((i-k+range)%(range+1)));
                                this->my_games[ulong(range+i-1)][ulong(k)] = Game(ulong((i-k+range)%(range+1)),ulong((i+k+1)%(range+1)));
                            }
                        }
                    }
                }
            }
        };

        static const int group_number = 20;
        static const int max = 100;
        static const int outmin = 50;
        static const int homemin = 55;
        static const int teambounus = 10;
        bool played;
        Schedule my_Schedule;
        std::vector<Team> my_teams;

        public:
        Leauge();
        Leauge(std::vector<Team> new_teams);
        void play();
        
        std::vector<Team> results();

        std::vector<Team> top_lead(int number);

        int longest_win();

        int longest_lose();

        int numeber_more_score();

        int team_longest_win(ulong teamNum);

        int team_longest_lose(ulong teamNum);
        };

}