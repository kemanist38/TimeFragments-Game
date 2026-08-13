#include "time_controller.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void TimeController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("start_rewind"), &TimeController::start_rewind);
    ClassDB::bind_method(D_METHOD("stop_rewind"), &TimeController::stop_rewind);
    ClassDB::bind_method(D_METHOD("toggle_time_direction"), &TimeController::toggle_time_direction);
    ClassDB::bind_method(D_METHOD("can_rewind"), &TimeController::can_rewind);
    ClassDB::bind_method(D_METHOD("get_time_energy"), &TimeController::get_time_energy);
    ClassDB::bind_method(D_METHOD("get_time_scale"), &TimeController::get_time_scale);
    ClassDB::bind_method(D_METHOD("set_time_energy", "energy"), &TimeController::set_time_energy);
    ClassDB::bind_method(D_METHOD("add_time_energy", "amount"), &TimeController::add_time_energy);
    
    ADD_SIGNAL(MethodInfo("time_rewind_started"));
    ADD_SIGNAL(MethodInfo("time_rewind_ended"));
    ADD_SIGNAL(MethodInfo("time_energy_changed", PropertyInfo(Variant::FLOAT, "new_energy")));
}

void TimeController::_ready() {
    position_history.reserve(max_history_size);
    rotation_history.reserve(max_history_size);
    UtilityFunctions::print("TimeController hazır!");
}

void TimeController::_process(double delta) {
    // Enerji yenilenmesi (geri sarma yapılmıyorsa)
    if (!is_rewinding && time_energy < max_time_energy) {
        time_energy += energy_regen_rate * delta;
        if (time_energy > max_time_energy) {
            time_energy = max_time_energy;
        }
        emit_signal("time_energy_changed", time_energy);
    }
    
    // Zaman ölçeğini yumuşat
    float target_scale = is_rewinding ? reverse_time_scale : 1.0f;
    time_scale = Math::lerp(time_scale, target_scale, delta * 5.0f);
    
    // Zamanı yavaşlatma efekti (isteğe bağlı)
    if (!is_rewinding && time_scale < 0.9f) {
        time_scale = Math::lerp(time_scale, 1.0f, delta * 2.0f);
    }
}

void TimeController::start_rewind() {
    if (time_energy <= 0 || position_history.empty()) return;
    
    is_rewinding = true;
    emit_signal("time_rewind_started");
    UtilityFunctions::print("Zaman geri sarma BAŞLADI");
}

void TimeController::stop_rewind() {
    if (!is_rewinding) return;
    
    is_rewinding = false;
    emit_signal("time_rewind_ended");
    UtilityFunctions::print("Zaman geri sarma BİTTİ");
}

void TimeController::toggle_time_direction() {
    if (is_rewinding) {
        stop_rewind();
    } else {
        start_rewind();
    }
}

void TimeController::record_state(Vector3 pos, Quaternion rot) {
    if (is_rewinding) return; // Geri sarma sırasında kaydetme
    
    position_history.push_back(pos);
    rotation_history.push_back(rot);
    
    if (position_history.size() > max_history_size) {
        position_history.erase(position_history.begin());
        rotation_history.erase(rotation_history.begin());
    }
}

void TimeController::restore_state(Vector3 &pos, Quaternion &rot) {
    if (position_history.empty() || time_energy <= 0) {
        stop_rewind();
        return;
    }
    
    // Enerji harca
    time_energy -= energy_drain_rate * 0.016f; // ~60fps
    emit_signal("time_energy_changed", time_energy);
    
    if (time_energy <= 0) {
        stop_rewind();
        return;
    }
    
    // Son durumu geri yükle
    pos = position_history.back();
    rot = rotation_history.back();
    
    position_history.pop_back();
    rotation_history.pop_back();
}

bool TimeController::can_rewind() const {
    return time_energy > 10.0f && !position_history.empty();
}

float TimeController::get_time_energy() const {
    return time_energy;
}

float TimeController::get_time_scale() const {
    return time_scale;
}

void TimeController::set_time_energy(float energy) {
    time_energy = Math::clamp(energy, 0.0f, max_time_energy);
    emit_signal("time_energy_changed", time_energy);
}

void TimeController::add_time_energy(float amount) {
    set_time_energy(time_energy + amount);
}
