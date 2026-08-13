#include "player_movement.h"
#include "time_controller.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>

void PlayerMovement::_bind_methods() {
    ClassDB::bind_method(D_METHOD("take_damage", "damage"), &PlayerMovement::take_damage);
    ClassDB::bind_method(D_METHOD("heal", "amount"), &PlayerMovement::heal);
    ClassDB::bind_method(D_METHOD("get_health"), &PlayerMovement::get_health);
    ClassDB::bind_method(D_METHOD("get_max_health"), &PlayerMovement::get_max_health);
    ClassDB::bind_method(D_METHOD("set_has_double_jump", "enabled"), &PlayerMovement::set_has_double_jump);
    
    ADD_SIGNAL(MethodInfo("health_changed", PropertyInfo(Variant::FLOAT, "new_health")));
    ADD_SIGNAL(MethodInfo("player_died"));
    ADD_SIGNAL(MethodInfo("player_respawned"));
}

void PlayerMovement::_ready() {
    time_controller = Object::cast_to<TimeController>(get_node("../TimeController"));
    camera = get_node<Node3D>("Camera3D");
    mesh = get_node<Node3D>("MeshInstance3D");
    
    UtilityFunctions::print("Player hazır!");
}

void PlayerMovement::_physics_process(double delta) {
    if (is_dead()) return;
    
    handle_movement(delta);
    handle_jump();
    handle_time_rewind();
    
    // Yerçekimi
    if (!is_on_floor()) {
        velocity.y -= gravity * delta;
    } else {
        jump_count = 0;
        can_double_jump = true;
    }
    
    // Zaman ölçeğini uygula
    if (time_controller) {
        float time_scale = Math::abs(time_controller->get_time_scale());
        // Hızı zaman ölçeğine göre ayarla
    }
    
    move_and_slide();
    
    // Durumu kaydet (zaman makinesi için)
    if (time_controller && is_on_floor()) {
        time_controller->record_state(get_global_position(), get_global_rotation());
    }
}

void PlayerMovement::handle_movement(float delta) {
    Input* input = Input::get_singleton();
    Vector3 direction = Vector3();
    
    // Yön vektörü
    Basis basis = get_global_transform().basis;
    
    if (input->is_action_pressed("move_forward")) {
        direction -= basis.z;
    }
    if (input->is_action_pressed("move_back")) {
        direction += basis.z;
    }
    if (input->is_action_pressed("move_left")) {
        direction -= basis.x;
    }
    if (input->is_action_pressed("move_right")) {
        direction += basis.x;
    }
    
    direction = direction.normalized();
    
    // Hız hesaplama
    float current_speed = input->is_action_pressed("sprint") ? sprint_speed : speed;
    
    // Hızlı yavaşlama
    if (direction == Vector3()) {
        velocity.x = Math::lerp(velocity.x, 0.0f, delta * 10.0f);
        velocity.z = Math::lerp(velocity.z, 0.0f, delta * 10.0f);
    } else {
        velocity.x = direction.x * current_speed;
        velocity.z = direction.z * current_speed;
    }
}

void PlayerMovement::handle_jump() {
    if (Input::get_singleton()->is_action_just_pressed("jump")) {
        if (is_on_floor()) {
            velocity.y = jump_velocity;
            jump_count = 1;
        } else if (has_double_jump && can_double_jump && jump_count < 2) {
            velocity.y = jump_velocity;
            jump_count++;
            can_double_jump = false;
            // Çift zıplama partikül efekti
        }
    }
}

void PlayerMovement::handle_time_rewind() {
    if (!time_controller) return;
    
    if (time_controller->is_rewinding()) {
        Vector3 new_pos = get_global_position();
        Quaternion new_rot = get_global_rotation();
        
        time_controller->restore_state(new_pos, new_rot);
        
        set_global_position(new_pos);
        set_global_rotation(new_rot);
        velocity = Vector3(); // Hızı sıfırla
    }
}

void PlayerMovement::take_damage(float damage) {
    if (is_dead()) return;
    
    health -= damage;
    emit_signal("health_changed", health);
    
    // Hasar efekti
    // Ekran kızılması
    // Ses efekti
    
    if (health <= 0) {
        die();
    }
}

void PlayerMovement::heal(float amount) {
    health = Math::min(health + amount, max_health);
    emit_signal("health_changed", health);
}

void PlayerMovement::die() {
    health = 0;
    emit_signal("player_died");
    UtilityFunctions::print("Oyuncu öldü!");
    
    // Respawn timer
    // set_physics_process(false);
}
