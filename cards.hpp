#pragma once
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

char suite_map[5] = {'I', 'h', 'c', 'd', 's'};
enum Suite{
    INVALID_SUITE = 0,
    heart,
    club,
    diamond,
    spade
};
 
std::string rank_map[14] = {"I-", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10", "j ", "q ", "k ", "a "};
enum Rank{
    INVALID_RANK = 0,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    j,
    q,
    k,
    a
};

enum HILO_VAL{
    INVALID_HILO = -9999,
    hi = -1,
    reg,
    lo,
};

class Card{
private:
    Suite suite;
    Rank rank;
    HILO_VAL hilo;
public:
    Card(){
        suite = INVALID_SUITE;
        rank = INVALID_RANK;
        hilo = INVALID_HILO;
    }

    Card(Suite suite, Rank rank): suite(suite), rank(rank), hilo(hilo){
        this->suite = suite;
        this->rank = rank;
        if (rank == Rank::INVALID_RANK){
            hilo = HILO_VAL::INVALID_HILO;
        }else{
            if (rank <= Rank::r6){
                hilo = HILO_VAL::lo;
            }else if (rank >= Rank::r10 || rank == Rank::a){
                hilo = HILO_VAL::hi;
            }else{
                hilo = HILO_VAL::reg;
            }
        }
    }

    char getCSuite(){
        return suite_map[(int)suite];
    }

    Suite getSSuite(){
        return suite;
    }
    
    std::string getSRank(){
        return rank_map[(int)rank];
    }

    Rank getRRank(){
        return rank;
    }

    std::string displayCard(){
        return getSRank() + getCSuite();
    }

    int getHILO(){
        return (int)hilo;
    }

    bool isInvalid(){
        return suite == Suite::INVALID_SUITE || rank == Rank::INVALID_RANK || hilo == HILO_VAL::INVALID_HILO;
    }

    void invalidate(){
        suite = Suite::INVALID_SUITE;
        rank = Rank::INVALID_RANK;
        hilo = HILO_VAL::INVALID_HILO;
    }
};

class Deck{
private:
    // row 0: heart, row 1: club, row 2: diamond, row 3: spade
    Card deck[4][13];
    std::vector<Card> valids;
public:
    Deck(){
        for (int i=0; i < 13; ++i){
            Card c(Suite::heart, (Rank) (i+1));
            deck[0][i] = c;
            valids.push_back(deck[0][i]);
        }
        for (int i=0; i < 13; ++i){
            Card c(Suite::club, (Rank) (i+1));
            deck[1][i] = c;
            valids.push_back(deck[1][i]);
        }
        for (int i=0; i < 13; ++i){
            Card c(Suite::diamond, (Rank) (i+1));
            deck[2][i] = c;
            valids.push_back(deck[2][i]);
        }
        for (int i=0; i < 13; ++i){
            Card c(Suite::spade, (Rank) (i+1));
            deck[3][i] = c;
            valids.push_back(deck[3][i]);
        }
    }



    // Gets a random card and invalidates it from the deck
    Card getRandom(){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine e(seed);

        std::shuffle(std::begin(valids), std::end(valids), e);

        Card ret(Suite::INVALID_SUITE, Rank::INVALID_RANK);
        int idx = rand()%52;

        if (valids.size() > 0){
            ret = valids[0];
            valids.erase(valids.begin());
        }

        return ret;
    }
};