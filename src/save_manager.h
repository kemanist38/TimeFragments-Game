#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class SaveManager : public Node {
    GDCLASS(SaveManager, Node)
    
private:
    String save_path = "user://savegame.save";
    String config_path = "user://settings.cfg";
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    
    void save_game();
    bool load_game();
    void delete_save();
    bool has_save() const;
    
    void save_settings();
    void load_settings();
    
    // Cloud save
    void sync_to_cloud();
    void sync_from_cloud();
    
    // Data helpers
    Dictionary get_save_data();
    void apply_save_data(const Dictionary& data);
};

#endif
