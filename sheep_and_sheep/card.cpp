#include "card.h"
#include "uuid/uuid.h"
#include <iostream>

#define MAX_ID  128

Card::Card(void)
{
    uuid_t uuid;
    char buf[MAX_ID];
    uuid_generate(uuid);
    uuid_unparse(uuid, buf);
    uid = std::string(buf);
    std::cout << uid << std::endl;
}
