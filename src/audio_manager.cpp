#include "audio_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void AudioManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play_music", "track_name"), &AudioManager::play_music);
    ClassDB::bind_method(D_METHOD("play_sfx", "sound_name"), &AudioManager::play_sfx);
    ClassDB::bind_method(D_METHOD("stop_music"), &AudioManager::stop_music);
}

void AudioManager::_ready() {
    UtilityFunctions::print("AudioManager hazır");
}

void AudioManager::play_music(String track_name) {
    UtilityFunctions::print("Müzik çalınıyor: ", track_name);
    // AudioStreamPlayer ile müzik çal
}

void AudioManager::play_sfx(String sound_name) {
    UtilityFunctions::print("SFX: ", sound_name);
    // Ses efekti çal
}

void AudioManager::stop_music() {
    UtilityFunctions::print("Müzik durduruldu");
}
