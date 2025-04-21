#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include "Depot.h"
#include "Card.h"

class Level{
private:
    static Level* instance;
    Level();
    std::string m_levelpath;
    // Hand hand;
    /// @brief vector of cards in game
    /// used in drawing and scaling
    std::vector<Card*> m_cards;
    std::vector<std::shared_ptr<Depot>> m_depots; 
    std::vector<std::shared_ptr<Depot>> m_tableau; 
    std::vector<std::shared_ptr<Depot>> m_foundation; 
    std::shared_ptr<Depot> m_stock; 

    struct flags{
        /// @brief which depot can be moved
        int m_difficulty;
        /// @brief which type of card can be placed one on another
        int m_placingtype;
        bool s_autocollect=false;
        void autocollect(Level& level);
        bool s_stockdeal=false;
        bool tableauplaceany = false;
    };
    static flags s_flags;
public:
    static Level& getInstance(){
        if(!instance)
            instance = new Level();
        return *instance;
    }
    ~Level();
    /// @brief load level
    /// @param levelpath name of level file 
    void loadLevel(std::string &&levelpath);
    /// @brief reset level
    void resetLevel();
    /// @brief clean level
    void cleanLevel();
    /// @brief draw level
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;
    /// @brief shuffle cards
    void shuffle();
    /// @brief deal cards
    void dealCards();
    /// @brief scale level
    void scale(float x,float y);
    /// @brief handle level events
    void levelEvent(sf::Vector2i mousePos);
    void setFlags(flags flag){s_flags=flag;};
    static flags& getFlags(){return s_flags;}
    std::vector<Card*> &getCards(){return m_cards;}
    friend class Stock;
    friend class Tableau;
};
#endif

