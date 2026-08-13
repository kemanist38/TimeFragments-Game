#include "ad_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void AdManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize_ads"), &AdManager::initialize_ads);
    ClassDB::bind_method(D_METHOD("show_interstitial_ad"), &AdManager::show_interstitial_ad);
    ClassDB::bind_method(D_METHOD("show_rewarded_ad"), &AdManager::show_rewarded_ad);
    ClassDB::bind_method(D_METHOD("is_rewarded_ad_ready"), &AdManager::is_rewarded_ad_ready);
    
    ADD_SIGNAL(MethodInfo("interstitial_closed"));
    ADD_SIGNAL(MethodInfo("reward_earned", PropertyInfo(Variant::INT, "amount")));
}

void AdManager::_ready() {
    UtilityFunctions::print("AdManager hazır");
}

void AdManager::initialize_ads() {
    UtilityFunctions::print("AdMob başlatılıyor...");
    // Google Mobile Ads SDK başlatma
}

void AdManager::show_interstitial_ad() {
    UtilityFunctions::print("Geçiş reklamı gösteriliyor");
    emit_signal("interstitial_closed");
}

void AdManager::show_rewarded_ad() {
    UtilityFunctions::print("Ödüllü reklam gösteriliyor");
    emit_signal("reward_earned", 500);
}

bool AdManager::is_rewarded_ad_ready() {
    return true; // Test için her zaman hazır
}
