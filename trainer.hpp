#pragma once
#include "basic_strategy.hpp"
#include "cards.hpp"
#include <ctime>


class Trainer{
private:
    std::vector<Deck> decks;
    int num_decks;
public:
    Trainer(){}
    Trainer(unsigned num_decks, bool shuffle = true){
        this->num_decks = num_decks;
        for (int i=0; i < num_decks; ++i){
            Deck dd(shuffle);
            decks.push_back(dd);
        }
    }

    void trainBasicStrat(){

    }

    void trainHILO(){
        using namespace std;
        cout << "HILO trainer\n";
        cout << "===========================================================\n";
        cout << "Instructions:\n";
        cout << "\tRanks [2,6] have a count of 1, [7,9] have a count of 0, and [10 - Ace] = -1\n";
        cout << "\tYou will be prompted with cards, your job is to keep track of the running count and the estimated true count\n";
        cout << "\tWhen prompted for the count, enter an integer (0, 5, -1, etc)\n";
        cout << "\tYou response will be timed. This session will go on until all decks are empty or you type quit\n";
        cout << "===========================================================\n";

        string resp = "";
        int num_cards = 52;
        int deck_idx = num_decks - 1;

        int currRunningCount = 0;
        int currTrueCount = 0;
        vector<int> runningCounts;
        vector<int> userRunningCounts;
        vector<clock_t> runningCountTimes;

        string askWhen= "";
        while (askWhen != "1" && askWhen != "0"){
            cout << "Do you want to be asked for count after every card (press 0) or after a random amount of cards (press 1)\n";
            cin >> askWhen;
        }
        int askInt = stoi(askWhen);
        srand(time(NULL));
        // Setting interval to ask user from a certain number of cards placed
        int askUser = askInt == 0? 1 : rand()%4 + 8;
        cout << "Beginning HILO training\n";
        cout << "===========================================================\n";

        while(num_cards > 0){
            Card drawn = decks[deck_idx].getRandom();
            currRunningCount += drawn.getHILO();
            drawn.displayCard();
            cout << "\t";
            num_cards--;
            askUser--;

            if (num_cards == 0){
                deck_idx--;
                if (deck_idx > 0){
                    num_cards = 52;
                }
            }

            if (askUser == 0 || num_cards == 0){
                cout << "\n";
                cout << num_cards << " Enter the running count: \n" << flush;
                clock_t time = clock();
                cin >> resp;
                time = clock() - time;


                if (resp == "quit"){
                    break;
                }

                runningCounts.push_back(currRunningCount);
                userRunningCounts.push_back(stoi(resp));
                runningCountTimes.push_back(time);

                if (num_cards == 0){
                    break;
                }
                askUser = askInt == 0? 1 : rand()%4 + 8;
            }
        }

        printHILOLog(runningCounts, userRunningCounts, runningCountTimes);
    }


    void printHILOLog(const std::vector<int>& actual, const std::vector<int>& user, std::vector<clock_t>& times){
        using namespace std;
        int nl = 0;
        cout << "Format: (actual count, user count)\n";
        cout << "Log:";
        cout << "\n===========================================================\n";
        cout << "|  ";
        for (int i=0; i < actual.size(); ++i){
            nl++;
            cout << "(" << actual[i] << ", " << user[i] << ") | ";
            if (nl == 6){
                cout << "\n";
            }
        }

        nl = 0;
        cout << "\n===========================================================\n";
        cout << "Time Log (seconds):\n";
        cout << "===========================================================\n";
        cout << "|  ";
        for (int i=0; i < times.size(); ++i){
            nl++;
            cout << (double) times[i]/1000 << "  | ";
            if (nl == 6){
                cout << "\n";
            }
        }
        cout << "\n===========================================================\n";

    }





    void hiloGetResp(std::string& resp){
       
        std::cout << "Enter the running count: \n" << std::flush;
        std::cin >> resp;
        // while()

    }
};

