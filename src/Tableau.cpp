#include "Tableau.h"

Tableau::Tableau(sf::Vector2f position,sf::Vector2f dposition):Depot(position,dposition){

}

void Tableau::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   _pile.back()->draw(target,states);
}