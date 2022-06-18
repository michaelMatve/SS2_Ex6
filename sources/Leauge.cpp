#include "Leauge.hpp"
namespace michLeag{

    Team::Team(const std::string& newName, double newLevel)
    {
        this->TeamName = newName;
        this->level = newLevel;
        this->totalWinPoint = 0;
        this->totalLosePoint = 0;
        this -> totalWin = 0;
        this -> totalLose = 0;
    }

    Leauge::Leauge()
    {
        this->played=false;
        for(int i=0 ; i<group_number; i++)
        {
            std::string name= "group";
            name+= std::to_string(i);
            this->my_teams.push_back(Team(name,i/double(group_number)));
           
        }
    }
    Leauge::Leauge(std::vector<Team> new_teams)
    {
        this->played=false;
        if(new_teams.size()>group_number)
        {
            std::__throw_invalid_argument("to many teams");
        }
        for(ulong i=0 ; i<new_teams.size(); i++)
        {
        if(new_teams[i].level>1)
        {
            std::__throw_invalid_argument("bad level number");
        }
           this->my_teams.push_back(Team(new_teams[i].TeamName,new_teams[i].level)); 
        }
        ulong i = 0;
        while(this->my_teams.size()<group_number)
        {
            std::string name= "group";
            name+=std::to_string(i);
            this->my_teams.push_back(Team(name,i/double(group_number)));
            i++;
        }
    }
    void Leauge::play()
    {
        if(this->played)
        {
            std::__throw_invalid_argument("alredy played");
        }
        std::random_device my_rnd;
        std::mt19937 do_rand(my_rnd());
        std::uniform_int_distribution<std::mt19937::result_type> out(outmin,max);
        std::uniform_int_distribution<std::mt19937::result_type> home(homemin,max);
        for(ulong day =0 ; day<this->my_Schedule.my_games.size(); ++day)
        {
            for(ulong game = 0 ; game<this->my_Schedule.my_games[0].size(); game++)
            {
                int homepoint = home(do_rand);
                int outpoint = out(do_rand);

                homepoint +=int(this->my_teams[this->my_Schedule.my_games[day][game].HomeTeam].level*teambounus);
                outpoint +=int(this->my_teams[this->my_Schedule.my_games[day][game].OutTeam].level*teambounus);
                this->my_Schedule.my_games[day][game].set_points(homepoint,outpoint);

                if(this->my_Schedule.my_games[day][game].win == 1)
                
                {
                    this->my_teams[this->my_Schedule.my_games[day][game].HomeTeam].totalWin++;
                    this->my_teams[this->my_Schedule.my_games[day][game].OutTeam].totalLose++;
                }
                else
                {
                    this->my_teams[this->my_Schedule.my_games[day][game].OutTeam].totalWin++;
                    this->my_teams[this->my_Schedule.my_games[day][game].HomeTeam].totalLose++;
                }
                this->my_teams[this->my_Schedule.my_games[day][game].OutTeam].totalLosePoint+=this->my_Schedule.my_games[day][game].HomePoint;
                this->my_teams[this->my_Schedule.my_games[day][game].OutTeam].totalWinPoint+=this->my_Schedule.my_games[day][game].OutPoint;
                this->my_teams[this->my_Schedule.my_games[day][game].HomeTeam].totalLosePoint+=this->my_Schedule.my_games[day][game].OutPoint;
                this->my_teams[this->my_Schedule.my_games[day][game].HomeTeam].totalWinPoint+=this->my_Schedule.my_games[day][game].HomePoint;
            }
        }
        this->played=true;
    }

    std::vector<Team> Leauge::results()
    {
        if(!this->played)
        {
            std::__throw_invalid_argument("not played yet");
        }
        std::vector<Team> groups;
        for(ulong i=0 ; i<this->my_teams.size(); i++)
        {
            ulong index_in_new = 0;
            while(index_in_new<groups.size())
            {
                if(this->my_teams[i].totalWin>groups[index_in_new].totalWin)
                {
                    break;
                }
                if(this->my_teams[i].totalWin==groups[index_in_new].totalWin)
                {
                    if((this->my_teams[i].totalWinPoint-this->my_teams[i].totalLosePoint)>(groups[index_in_new].totalWinPoint-groups[index_in_new].totalLosePoint))
                    {
                        break;
                    }
                }
                index_in_new++;
            }
            groups.insert((groups.begin()+long(index_in_new)),this->my_teams[i]);
        }
        for(ulong i=0 ; i<this->my_teams.size();i++)
        {
            std::cout<< i <<") name : "<< groups[i].TeamName<<" | wins: "<<groups[i].totalWin<<+" | difrens:" <<(groups[i].totalWinPoint-groups[i].totalLosePoint)<<std::endl;
        }
        return groups;
    }

        std::vector<Team> Leauge::top_lead(int number)
        {

            if(!this->played)
            {
                std::__throw_invalid_argument("not played yet");
            }
            if(number>group_number)
            {
                std::__throw_invalid_argument("to many teams");
            }
             std::vector<Team> new_groups;
            std::vector<Team> groups = this->results();
            for(ulong index =0 ; index<number; index++)
            {
                new_groups.push_back(groups[index]);
                std::cout<< index <<") name : "<< groups[index].TeamName<<" | wins: "<<groups[index].totalWin<<+" | difrens:" <<(groups[index].totalWinPoint-groups[index].totalLosePoint)<<std::endl;
            }
            return new_groups;
        }

        int Leauge::longest_win()
        {
            if(!this->played)
            {
                std::__throw_invalid_argument("not played yet");
            }   
            int longest =0;
            for(ulong index=0 ; index<this->my_teams.size() ; index++)
            {
                int new_long = this->team_longest_win(index);
                if(longest<new_long)
                {
                    longest=new_long;
                }
            }
            return longest;
        }

        int Leauge::longest_lose()
        {
            if(!this->played)
            {
                std::__throw_invalid_argument("not played yet");
            }
            int longest =0;
            for(ulong index=0 ; index<this->my_teams.size() ; index++)
            {
                int new_long = this->team_longest_lose(index);
                if(longest<new_long)
                {
                    longest=new_long;
                }
            }
            return longest;
        }

        int Leauge::numeber_more_score()
        {
            if(!this->played)
            {
                std::__throw_invalid_argument("not played yet");
            }
            int counter = 0;
            for(ulong index=0;index<this->my_teams.size();index++)
            {
                if((this->my_teams[index].totalWinPoint-this->my_teams[index].totalLosePoint)>0)
                {
                    ++counter;
                }
            }
            return counter;
        }

        int Leauge::team_longest_win(ulong teamNum)
        {
            if(!this->played)
            {
                std::__throw_invalid_argument("not played yet");
            }
            int longest = 0;
            int counter = 0;
            for(ulong day =0 ; day<this->my_Schedule.my_games.size(); ++day)
            {
                for(ulong game = 0 ; game<this->my_Schedule.my_games[0].size(); game++)
                {
                    if(this->my_Schedule.my_games[day][game].win == 1)
                    {
                        if(this->my_Schedule.my_games[day][game].OutTeam==teamNum)
                        {
                            counter=0;
                        }
                        if(this->my_Schedule.my_games[day][game].HomeTeam==teamNum)
                        {
                            ++counter;
                            if(counter>longest)
                            {
                                longest = counter;
                            }
                        }
                    }
                    if(this->my_Schedule.my_games[day][game].win == -1)
                    {
                        if(this->my_Schedule.my_games[day][game].HomeTeam==teamNum)
                        {
                            counter=0;
                        }
                        if(this->my_Schedule.my_games[day][game].OutTeam==teamNum)
                        {
                            ++counter;
                            if(counter>longest)
                            {
                                longest = counter;
                            }
                        }
                    }
                }
            }
            return longest;
        }

        int Leauge::team_longest_lose(ulong teamNum)
        {
            if(!this->played)
            {
                std::__throw_invalid_argument("not played yet");
            }
            int longest = 0;
            int counter = 0;
            for(ulong day =0 ; day<this->my_Schedule.my_games.size(); ++day)
            {
                for(ulong game = 0 ; game<this->my_Schedule.my_games[0].size(); game++)
                {
                    if(this->my_Schedule.my_games[day][game].win == -1)
                    {
                        if(this->my_Schedule.my_games[day][game].OutTeam==teamNum)
                        {
                            counter=0;
                        }
                        if(this->my_Schedule.my_games[day][game].HomeTeam==teamNum)
                        {
                            ++counter;
                            if(counter>longest)
                            {
                                longest = counter;
                            }
                        }
                    }
                    if(this->my_Schedule.my_games[day][game].win == 1)
                    {
                        if(this->my_Schedule.my_games[day][game].HomeTeam==teamNum)
                        {
                            counter=0;
                        }
                        if(this->my_Schedule.my_games[day][game].OutTeam==teamNum)
                        {
                            ++counter;
                            if(counter>longest)
                            {
                                longest = counter;
                            }
                        }
                    }
                }
            }
            return longest;
        }
}