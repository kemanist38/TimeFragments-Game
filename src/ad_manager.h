#ifndef AD_MANAGER_H
#define AD_MANAGER_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class AdManager : public Node {
    GDCLASS(AdManager, Node)
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    
    void initialize_ads();
    void show_interstitial_ad();
    void show_rewarded_ad();
    void show_banner_ad();
    void hide_banner_ad();
    
    bool is_rewarded_ad_ready();
};
#endif
