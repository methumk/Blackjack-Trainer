#pragma once
#include <vector>

#define NUM_DEALER_UPCARD 10
#define NUM_HARD 10
#define NUM_SOFT 8
#define NUM_PAIR 10

enum ActionTypes{
    hit,
    stand,
    double_hit,
    double_stand,
    split,
    invalid
};

std::string action_names[6] = {
    "Hit",
    "Stand",
    "Dbl/H",
    "Dbl/S",
    "Split",
    "INVALID"
};

std::string hard_tot_rows[NUM_HARD] = {
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17+"
};

std::string soft_tot_rows[NUM_SOFT] = {
    "A-2",
    "A-3",
    "A-4",
    "A-5",
    "A-6",
    "A-7",
    "A-8",
    "A-9"
};

std::string pair_tot_rows[NUM_PAIR] = {
    "2-2",
    "3-3",
    "4-4",
    "5-5",
    "6-6",
    "7-7",
    "8-8",
    "9-9",
    "10-10",
    "A-A"
};



class BasicStrategy{
private:
    // used as temp variable to init total arrays
    std::vector<ActionTypes> acts;

    void invalidateActs(){
        acts.clear();
        acts.reserve(NUM_DEALER_UPCARD);
        for (int i=0; i < NUM_DEALER_UPCARD; ++i)
            acts.push_back(ActionTypes::invalid);
    }

    void initHardTotals(){
        // invalidate
        invalidateActs();
        hard_totals.reserve(NUM_HARD);

        for (int i=0; i < NUM_HARD; ++i){
            switch(i){
                case 0:
                    // hand = 8
                    fill(acts.begin(), acts.end(), ActionTypes::hit);
                    break;
                case 1:
                    // hand = 9
                    acts[0] = ActionTypes::hit;
                    fill(acts.begin()+1, acts.begin()+5, ActionTypes::double_hit);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 2:
                    // hand = 10
                    fill(acts.begin(), acts.begin()+8, ActionTypes::double_hit);
                    fill(acts.begin()+8, acts.end(), ActionTypes::hit);
                    break;
                case 3:
                    // hand = 11
                    fill(acts.begin(), acts.end(), ActionTypes::double_hit);
                    break;
                case 4:
                    // hand = 12
                    fill(acts.begin(), acts.begin()+2, ActionTypes::hit);
                    fill(acts.begin()+2, acts.begin()+5, ActionTypes::stand);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                    // hand = 13 to 16
                    fill(acts.begin(), acts.begin()+5, ActionTypes::stand);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 9:
                    // hand = 17+
                    fill(acts.begin(), acts.end(), ActionTypes::stand);
                    break;
            }
            hard_totals.push_back(acts);
        }
    }

    void initSoftTotals(){
        // invalidate
        invalidateActs();
        soft_totals.reserve(NUM_SOFT);

        for (int i=0; i < NUM_SOFT; ++i){
            switch(i){
                case 0:
                case 1:
                    // hand = A-2, A-3
                    fill(acts.begin(), acts.begin()+3, ActionTypes::hit);
                    fill(acts.begin()+3, acts.begin()+5, ActionTypes::double_hit);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 2:
                case 3:
                    // hand = A-4, A-5
                    fill(acts.begin(), acts.begin()+2, ActionTypes::hit);
                    fill(acts.begin()+2, acts.begin()+5, ActionTypes::double_hit);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 4:
                    // hand = A-6
                    acts[0] = ActionTypes::hit;
                    fill(acts.begin()+1, acts.begin()+5, ActionTypes::double_hit);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 5:
                    // hand = A-7
                    fill(acts.begin(), acts.begin()+5, ActionTypes::double_stand);
                    fill(acts.begin()+5, acts.begin()+7, ActionTypes::stand);
                    fill(acts.begin()+7, acts.end(), ActionTypes::hit);
                    break;
                case 6:
                    fill(acts.begin(), acts.end(), ActionTypes::stand);
                    acts[4] = ActionTypes::double_stand;
                    break;
                case 7:
                    fill(acts.begin(), acts.end(), ActionTypes::stand);
                    break;
            }
            soft_totals.push_back(acts);
        }
    }

    void initPairTotals(){
        // invalidate
        invalidateActs();
        soft_totals.reserve(NUM_PAIR);

        for (int i=0; i < NUM_PAIR; ++i){
            switch(i){
                case 0:
                case 1:
                    // hand = 2-2, 3-3
                    fill(acts.begin(), acts.begin()+2, ActionTypes::hit);
                    fill(acts.begin()+2, acts.begin()+6, ActionTypes::split);
                    fill(acts.begin()+6, acts.end(), ActionTypes::hit);
                    break;
                case 2:
                    // hand = 4-4
                    fill(acts.begin(), acts.begin()+3, ActionTypes::hit);
                    fill(acts.begin()+3, acts.begin()+5, ActionTypes::split);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 3:
                    // hand = 5-5,
                    fill(acts.begin(), acts.begin()+8, ActionTypes::double_hit);
                    fill(acts.begin()+8, acts.end(), ActionTypes::hit);
                    break;
                case 4:
                    // hand = 6-6
                    acts[0] = ActionTypes::hit;
                    fill(acts.begin()+1, acts.begin()+5, ActionTypes::split);
                    fill(acts.begin()+5, acts.end(), ActionTypes::hit);
                    break;
                case 5:
                    // hand = 7-7
                    fill(acts.begin(), acts.begin()+6, ActionTypes::split);
                    fill(acts.begin()+6, acts.end(), ActionTypes::hit);
                    break;
                case 6:
                    // hand = 8-8
                    fill(acts.begin(), acts.end(), ActionTypes::split);
                    break;
                case 7:
                    // hand = 9-9
                    fill(acts.begin(), acts.end(), ActionTypes::split);
                    acts[5] = ActionTypes::stand;
                    acts[8] = ActionTypes::stand;
                    acts[9] = ActionTypes::stand;
                    break;
                case 8:
                    // hand = 10-10
                    fill(acts.begin(), acts.end(), ActionTypes::stand);
                    break;
                case 9:
                    // hand = A-A
                    fill(acts.begin(), acts.end(), ActionTypes::split);
                    break;
            }
            pair_totals.push_back(acts);
        }
    }
public:
    // For all total arrays cols correspond to dealer upcard
    // 0:2, 1:3, 2:4, 3:5, 4:6, 5:7, 6:8, 7:9, 8:10, 9:A

    // Rows correspond to hard totals
    // 0:8, 1:9, 2:10, 3:11, 4:12, 5:13, 6:14, 7:15, 8:16, 9:17+
    std::vector<std::vector<ActionTypes>> hard_totals;

    // Rows correspond to soft totals
    // 0:A-2, 1:A-3, 2:A-4, 3:A-5, 4:A-6, 5:A-7, 6:A-8, 7:A-9
    std::vector<std::vector<ActionTypes>> soft_totals;

    // Rows correspond to pair totals
    // 0:2-2, 1:3-3, 2:4-4, 3:5-5, 4:6-6, 5:7-7, 6:8-8, 7:9-9, 8:10-10, 9:A-A
    std::vector<std::vector<ActionTypes>> pair_totals;



    BasicStrategy(){
        initHardTotals();
        initSoftTotals();
        initPairTotals();
    }

    // type corresponds to 0: hardTotals, 1: softTotals, 2: pairTotals
    void checkArrs(int type = 0){
        int arr_len;
        std::vector<std::vector<ActionTypes>> arr;
        if (type == 1){
            arr_len = NUM_SOFT;
            arr = soft_totals;
            std::cout << "Printing SOFT TOTALS\n";
        }else if (type == 2){
            arr_len = NUM_PAIR;
            arr = pair_totals;
            std::cout << "Printing PAIR TOTALS\n";
        }else{
            type =0;
            arr_len = NUM_HARD;
            arr = hard_totals;
            std::cout << "Printing HARD TOTALS\n";
        }


        std::cout << "\t";
        for (int i=0; i < 10; ++i){
            if (i == 9){
                std::cout << "A\t";
            }else{
                std::cout << i+2 << "\t";
            }
        }
        std::cout << std::endl;

        for (int i=arr_len-1; i >= 0; --i){
            if (type == 1){
                std::cout << soft_tot_rows[i];
            }else if (type == 2){
                std::cout << pair_tot_rows[i];
            }else{
                std::cout << hard_tot_rows[i];
            }
            std::cout << ":\t";
            for (int j=0 ; j < NUM_DEALER_UPCARD; ++j){
                std::cout << action_names[(arr[i][j])] << "\t";
            }
            std::cout << std::endl << std::endl;
        }
    }
};