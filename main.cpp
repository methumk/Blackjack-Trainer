#include <iostream>
#include "trainer.hpp"


int main(){
    // BasicStrategy bs;
    // bs.checkArrs(0);
    // bs.checkArrs(1);
    // bs.checkArrs(2);

    // Deck d(true);

    // for (int i=0; i < 55; ++i){
    //     Card c = d.getRandom();
    //     std::cout << c.displayCard() << std::endl;
    // }
    Trainer t(1, true);
    t.trainHILO();


}