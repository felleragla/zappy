#ifndef __IState_IA_HPP__
#define __IState_IA_HPP__
#include <map>
#include "../../src/ia/include/InventoryManager.hpp"

union State {
    int Level;
    int food;
    int food_per_unit_time;
    Inventorymanager& _inventory;
}
class IState_IA
{
    private:
    State Ia;

    public :
    IState_IA();
    ~IState_IA();
    int get_inventory(); const
    Inventorymanager get_inventory(); const
    int get_level(); const
    int get_food(); const
    int get_food_per_unit_time() const;
    void set_inventory(Inventorymanager& _inventory);
    int set_level(int level);
    int set_food(int food);
    int set_food_per_unit_time(int food_per_unit_time );

};

#endif