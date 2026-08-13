#include "level_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>

void LevelManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("collect_crystal"), &LevelManager::collect_crystal);
    ClassDB::bind_method(D_METHOD("complete_level"), &LevelManager::complete_level);
    ClassDB::bind_method(D_METHOD("restart_level"), &LevelManager::restart_level);
    ClassDB::bind_method(D_METHOD("next_level"), &LevelManager::next_level);
    ClassDB::bind_method(D_METHOD("pause_game"), &LevelManager::pause_game);
    ClassDB::bind_method(D_METHOD("resume_game"), &LevelManager::resume_game);
    ClassDB::bind_method(D_METHOD("get_crystals_collected"), &LevelManager::get_crystals_collected);
    ClassDB::bind_method(D_METHOD("get_level_time"), &LevelManager::get_level_time);
    ClassDB::bind_method(D_METHOD("set_level", "world", "level"), &LevelManager::set_level);
    
    ADD_SIGNAL(MethodInfo("crystal_collected", PropertyInfo(Variant::INT, "total")));
    ADD_SIGNAL(MethodInfo("level_completed", PropertyInfo(Variant::FLOAT, "time")));
    ADD_SIGNAL(MethodInfo("level_failed", PropertyInfo(Variant::STRING, "reason")));
    ADD_SIGNAL(MethodInfo("game_paused"));
    ADD_SIGNAL(MethodInfo("game_resumed"));
}

void LevelManager::_ready() {
    UtilityFunctions::print("LevelManager hazır - Seviye ", current_world, "-", current_level);
    
    // Seviyedeki toplam kristal sayısını hesapla
    // get_tree()->get_nodes_in_group("crystals").size()
}

void LevelManager::_process(double delta) {
    if (!is_level_complete && !is_paused && !Engine::get_singleton()->is_editor_hint()) {
        level_time += delta;
    }
}

void LevelManager::collect_crystal() {
    crystals_collected++;
    emit_signal("crystal_collected", crystals_collected);
    
    // Ses efekti
    // Partikül efekti
    // UI güncelleme
    
    UtilityFunctions::print("Kristal toplandı: ", crystals_collected, "/", total_crystals_in_level);
}

void LevelManager::complete_level() {
    if (is_level_complete) return;
    
    is_level_complete = true;
    
    // Skor hesaplama
    float time_bonus = Math::max(0.0f, 300.0f - level_time); // 5 dakika hedef
    int score = crystals_collected * 100 + (int)time_bonus;
    
    emit_signal("level_completed", level_time);
    
    // Reklam göster (her 3 seviyede bir)
    if (current_level % 3 == 0) {
        // AdManager::show_interstitial_ad();
    }
    
    UtilityFunctions::print("Seviye tamamlandı! Süre: ", level_time, " Skor: ", score);
}

void LevelManager::fail_level(String reason) {
    player_deaths++;
    emit_signal("level_failed", reason);
    
    // 3 saniye sonra restart
    // get_tree()->create_timer(3.0).connect("timeout", callable_mp(this, &LevelManager::restart_level));
}

void LevelManager::restart_level() {
    get_tree()->reload_current_scene();
}

void LevelManager::next_level() {
    current_level++;
    if (current_level > 10) {
        current_level = 1;
        current_world++;
    }
    
    String next_scene = "res://scenes/levels/world" + String::num_int64(current_world) + 
                       "_level" + String::num_int64(current_level) + ".tscn";
    
    // get_tree()->change_scene_to_file(next_scene);
}

void LevelManager::pause_game() {
    is_paused = true;
    get_tree()->set_pause(true);
    emit_signal("game_paused");
}

void LevelManager::resume_game() {
    is_paused = false;
    get_tree()->set_pause(false);
    emit_signal("game_resumed");
}

void LevelManager::set_level(int world, int level) {
    current_world = world;
    current_level = level;
    crystals_collected = 0;
    level_time = 0.0f;
    is_level_complete = false;
}
