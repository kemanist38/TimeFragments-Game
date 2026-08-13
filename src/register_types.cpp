#include "register_types.h"

#include "time_controller.h"
#include "player_movement.h"
#include "level_manager.h"
#include "skill_system.h"
#include "store_manager.h"
#include "audio_manager.h"
#include "save_manager.h"
#include "multiplayer_manager.h"
#include "performance_manager.h"
#include "debug_manager.h"
#include "ad_manager.h"
#include "analytics_manager.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        ClassDB::register_class<TimeController>();
        ClassDB::register_class<PlayerMovement>();
        ClassDB::register_class<LevelManager>();
        ClassDB::register_class<SkillSystem>();
        ClassDB::register_class<StoreManager>();
        ClassDB::register_class<AudioManager>();
        ClassDB::register_class<SaveManager>();
        ClassDB::register_class<MultiplayerManager>();
        ClassDB::register_class<PerformanceManager>();
        ClassDB::register_class<DebugManager>();
        ClassDB::register_class<AdManager>();
        ClassDB::register_class<AnalyticsManager>();
    }
}

void uninitialize_module(ModuleInitializationLevel p_level) {
    // Cleanup if needed
}

extern "C" {
    GDExtensionBool GDE_EXPORT timefragments_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization
    ) {
        godot::GDExtensionBinding::InitObject init_obj(
            p_get_proc_address, p_library, r_initialization
        );
        
        init_obj.register_initializer(initialize_module);
        init_obj.register_terminator(uninitialize_module);
        init_obj.set_minimum_library_initialization_level(
            MODULE_INITIALIZATION_LEVEL_SCENE
        );
        
        return init_obj.init();
    }
}
