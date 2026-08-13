#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include <godot_cpp/classes/character_body3d.hpp>

using namespace godot;

class TimeController;

class PlayerMovement : public CharacterBody3D {
    GDCLASS(PlayerMovement, CharacterBody3D)
    
private:
    float speed = 6.0f;
    float sprint_speed = 10.0f;
    float jump_velocity = 12.0f;
    float gravity = 30.0f;
    float mouse_sensitivity = 0.005f;
    
    TimeController* time_controller;
    Node3D* camera;
    Node3D* mesh;
    
    bool has_double_jump = false;
    bool can_double_jump = false;
    int jump_count = 0;
    
    float health = 100.0f;
    float max_health = 100.0f;
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    void _physics_process(double delta) override;
    void _input(const Ref<InputEvent> &event) override;
    
    void handle_movement(float delta);
    void handle_jump();
    void handle_time_rewind();
    
    void take_damage(float damage);
    void heal(float amount);
    void die();
    
    // Getters
    float get_health() const { return health; }
    float get_max_health() const { return max_health; }
    bool is_dead() const { return health <= 0; }
    
    // Setters
    void set_has_double_jump(bool enabled) { has_double_jump = enabled; }
};

#endif
