#ifndef STORE_MANAGER_H
#define STORE_MANAGER_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class StoreManager : public Node {
    GDCLASS(StoreManager, Node)
    
private:
    int crystals = 0;
    bool is_vip = false;
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    
    void add_crystals(int amount);
    bool spend_crystals(int amount);
    int get_crystals() const;
    
    void purchase_product(String product_id);
    void watch_ad_for_crystals();
    
    bool is_vip_member() const;
};

#endif
