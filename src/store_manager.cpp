#include "store_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void StoreManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add_crystals", "amount"), &StoreManager::add_crystals);
    ClassDB::bind_method(D_METHOD("spend_crystals", "amount"), &StoreManager::spend_crystals);
    ClassDB::bind_method(D_METHOD("get_crystals"), &StoreManager::get_crystals);
    ClassDB::bind_method(D_METHOD("watch_ad_for_crystals"), &StoreManager::watch_ad_for_crystals);
    ClassDB::bind_method(D_METHOD("is_vip_member"), &StoreManager::is_vip_member);
    
    ADD_SIGNAL(MethodInfo("crystals_changed", PropertyInfo(Variant::INT, "new_amount")));
}

void StoreManager::_ready() {
    UtilityFunctions::print("StoreManager hazır - Kristal: ", crystals);
}

void StoreManager::add_crystals(int amount) {
    crystals += amount;
    emit_signal("crystals_changed", crystals);
    UtilityFunctions::print("Kristal eklendi: +", amount, " Toplam: ", crystals);
}

bool StoreManager::spend_crystals(int amount) {
    if (crystals >= amount) {
        crystals -= amount;
        emit_signal("crystals_changed", crystals);
        return true;
    }
    return false;
}

int StoreManager::get_crystals() const {
    return crystals;
}

void StoreManager::watch_ad_for_crystals() {
    // Reklam göster ve 500 kristal ver
    // AdManager::show_rewarded_ad();
    add_crystals(500);
}

bool StoreManager::is_vip_member() const {
    return is_vip;
}
