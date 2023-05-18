#include "card.h"
#include "uuid/uuid.h"
#include <iostream>
#include <cstring>

#define MAX_ID  128
#define MAX_LENGTH_NAME  6
const int max_type_of_cards = 100;
const char * card_name[max_type_of_cards] = 
        {"Carrot", "Grass", "Corn"};
const int current_type_of_cards = sizeof(card_name) 
    / sizeof(const char *);


Card::Card(const char * _name):
    name(_name)
{
    uuid_t uuid;
    char buf[MAX_ID];
    uuid_generate(uuid);
    uuid_unparse(uuid, buf);
    uid = std::string(buf);
    type = ClickableCard;
    printf("Construct card "); print_card();
}

Card::~Card(void){
    printf("Goodbye from card "); print_card();
}

void Card::print_card(void){
    std::string card_type;
    if (type == ClickableCard){
        card_type = "ClickableCard";
    }
    else if (type == SlotCard){
        card_type = "SlotCard";
    }
    else if (type == EliminatedCard){
        card_type = "EliminatedCard";
    }
    else assert(false);
    printf("uid: %s, name: %-*s, type is: %s\n", 
        uid.c_str(), MAX_LENGTH_NAME, name, card_type.c_str());
}
