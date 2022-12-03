# Blackjack-Trainer
Allows you to train skills for black jack: Basic strategy and Hi-Lo counting

## Basic Strategy
<img src="./images/mini-blackjack-strategy-chart.webp" width="200"/>

<sub> *source: https://www.blackjackapprenticeship.com/blackjack-strategy-charts/*</sub>

<p>
Basic strategy presents the best moves(Hit, Stand, Double, etc.) for a given player's and dealer's hand. Memorizing this alone is not enough to beat the house's edge, but knowing this is essential when trying to beat the dealer.
<br>
This trainer helps players master basic strategy by practicing matching the corresponding plays, given the dealer and their hand. 
<br>

Notes: 
* you are not allowed to surrender
* if your card contains a pair that you don't split
</p>

<p>
Below are the corresponding commands for each play:

    Hit: h
    Stand: s
    Double/or hit: dh
    Double/or stand: ds
    Split: p
    Quit: q or quit

    
</p>

## Hi-Lo Counting
<p>
Hi-Lo counting is one way to count cards. Low cards (those with rank 2-6) are valued at +1, regular cards (those with rank 7-9) are values at 0, and high cards (10 through Ace) are valued at -1. 
<br>
An entire deck of cards has a sum total of 0. This means if you keep a proper count you can guess which type of card you will get. The running count is defined as the total count. The true count is the running count divded by the number of remaining decks. Note that this count can be estimated and doesn't have to be exact.
</p>

