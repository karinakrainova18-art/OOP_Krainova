#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "npc.h"
#include <map>
#include <functional>
#include <sstream>

class NPCFactory {
private:
    using FactoryMethod = std::function<std::shared_ptr<NPC>(const std::string&, int, int)>;
    std::map<std::string, FactoryMethod> factory_methods_;

public:
    NPCFactory();
    std::shared_ptr<NPC> create_npc(const std::string& type, const std::string& name, int x, int y);
    std::shared_ptr<NPC> create_npc_from_file_string(const std::string& file_string);
};

#endif


