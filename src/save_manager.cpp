#include "save_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void SaveManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("save_game"), &SaveManager::save_game);
    ClassDB::bind_method(D_METHOD("load_game"), &SaveManager::load_game);
    ClassDB::bind_method(D_METHOD("delete_save"), &SaveManager::delete_save);
    ClassDB::bind_method(D_METHOD("has_save"), &SaveManager::has_save);
    ClassDB::bind_method(D_METHOD("get_save_data"), &SaveManager::get_save_data);
}

void SaveManager::_ready() {
    UtilityFunctions::print("SaveManager hazır");
    
    // Otomatik yükleme
    if (has_save()) {
        load_game();
    }
}

void SaveManager::save_game() {
    Dictionary data = get_save_data();
    String json_string = JSON::stringify(data);
    
    Ref<FileAccess> file = FileAccess::open(save_path, FileAccess::WRITE);
    if (file.is_valid()) {
        file->store_string(json_string);
        UtilityFunctions::print("Oyun kaydedildi!");
    } else {
        UtilityFunctions::print("Kaydetme HATASI!");
    }
}

bool SaveManager::load_game() {
    if (!FileAccess::file_exists(save_path)) {
        return false;
    }
    
    Ref<FileAccess> file = FileAccess::open(save_path, FileAccess::READ);
    if (!file.is_valid()) {
        return false;
    }
    
    String json_string = file->get_as_text();
    Dictionary data = JSON::parse_string(json_string);
    
    apply_save_data(data);
    UtilityFunctions::print("Oyun yüklendi!");
    return true;
}

void SaveManager::delete_save() {
    if (FileAccess::file_exists(save_path)) {
        // FileAccess::remove(save_path); // Godot 4'te farklı olabilir
    }
}

bool SaveManager::has_save() const {
    return FileAccess::file_exists(save_path);
}

Dictionary SaveManager::get_save_data() {
    Dictionary data;
    
    data["version"] = "1.0.0";
    data["timestamp"] = Time::get_singleton()->get_unix_time_from_system();
    
    // LevelManager verileri
    LevelManager* level = Object::cast_to<LevelManager>(get_node("/root/LevelManager"));
    if (level) {
        data["current_world"] = level->get("current_world");
        data["current_level"] = level->get_current_level();
        data["crystals_collected"] = level->get_crystals_collected();
    }
    
    // StoreManager verileri
    StoreManager* store = Object::cast_to<StoreManager>(get_node("/root/StoreManager"));
    if (store) {
        data["total_crystals"] = store->get_crystals();
    }
    
    // SkillSystem verileri
    SkillSystem* skills = Object::cast_to<SkillSystem>(get_node("/root/SkillSystem"));
    if (skills) {
        data["skills"] = skills->call("save_data");
    }
    
    // İstatistikler
    data["total_play_time"] = 0; // Hesaplanacak
    data["deaths"] = 0;
    data["levels_completed"] = 0;
    
    return data;
}

void SaveManager::apply_save_data(const Dictionary& data) {
    // LevelManager'a uygula
    LevelManager* level = Object::cast_to<LevelManager>(get_node("/root/LevelManager"));
    if (level && data.has("current_level")) {
        level->set_level(data.get("current_world", 1), data.get("current_level", 1));
    }
    
    // StoreManager'a uygula
    StoreManager* store = Object::cast_to<StoreManager>(get_node("/root/StoreManager"));
    if (store && data.has("total_crystals")) {
        store->call("add_crystals", data.get("total_crystals", 0));
    }
    
    UtilityFunctions::print("Kayıt verileri uygulandı");
}
