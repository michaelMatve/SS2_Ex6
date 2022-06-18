#include "doctest.h"
#include "sources/Leauge.hpp"
#include <string>

TEST_CASE("good inputs"){
        michLeag::Leauge my_leg;
        my_leg.play();
        CHECK_NOTHROW(my_leg.results());
        CHECK_NOTHROW(my_leg.longest_lose());
        CHECK_NOTHROW(my_leg.longest_win());
        CHECK_NOTHROW(my_leg.team_longest_lose(1));
        CHECK_NOTHROW(my_leg.team_longest_win(2));
        CHECK_NOTHROW(my_leg.top_lead(5));
        CHECK_NOTHROW(my_leg.numeber_more_score());

        for(ulong i=0 ; i < 20 ; i++)
        {
            CHECK_GT(my_leg.team_longest_lose(i)+my_leg.team_longest_win(i),0);
        }

        CHECK_GT(my_leg.longest_lose(),0);
        CHECK_GT(my_leg.longest_win(),0);

        std::vector<michLeag::Team> bestfive = my_leg.top_lead(5);
        std::vector<michLeag::Team> allteam = my_leg.results();
        for(ulong i=0 ; i< 5 ; i++)
        {
            CHECK_EQ(bestfive[i].TeamName,allteam[i].TeamName);
        }
        for(ulong i=0 ; i<19 ; i++)
        {
            CHECK_GE(allteam[i].totalWin,allteam[i+1].totalWin);
        }
        
    }

TEST_CASE("bad inputs"){
        michLeag::Leauge my_leg;
        CHECK_THROWS(my_leg.results());
        CHECK_THROWS(my_leg.longest_lose());
        CHECK_THROWS(my_leg.longest_win());
        CHECK_THROWS(my_leg.team_longest_lose(1));
        CHECK_THROWS(my_leg.team_longest_win(2));
        CHECK_THROWS(my_leg.top_lead(5));
        CHECK_THROWS(my_leg.numeber_more_score());

        std::vector<michLeag::Team> teams;
        for(ulong i =0 ; i<21; i++)
        {
            teams.push_back(michLeag::Team("new",0.5));
        }
        CHECK_THROWS(michLeag::Leauge my_leg2(teams));

        std::vector<michLeag::Team> teams3;
        teams3.push_back(michLeag::Team("new",5));
        CHECK_THROWS(michLeag::Leauge my_leg2(teams));

    
}