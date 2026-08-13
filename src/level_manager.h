#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class LevelManager : public Node3D {
    GDCLASS(LevelManager, Node3D)
    
private:
    int current_level = 1;
    int current_world = 1;
    int crystals_collected = 0;
    int total_crystals_in_level = 0;
    float level_time = 0.0f;
    bool is_level_complete = false;
    bool is_paused = false;
    
    int player_deaths = 0;
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    void _process(double delta) override;
    
    void collect_crystal();
    void complete_level();
    void fail_level(String reason);
    void restart_level();
    void next_level();
    
    void pause_game();
    void resume_game();
    
    // Getters
    int get_current_level() const { return current_level; }
    int get_crystals_collected() const { return crystals_collected; }
    int get_total_crystals() const { return total_crystals_in_level; }
    float get_level_time() const { return level_time; }
    bool is_level_finished() const { return is_level_complete; }
    
    // Setters
    void set_level(int world, int level);
};

#endif
