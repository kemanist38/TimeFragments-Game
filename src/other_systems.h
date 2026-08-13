// other_systems.h - Basit versiyonlar

#ifndef OTHER_SYSTEMS_H
#define OTHER_SYSTEMS_H

#include <godot_cpp/classes/node.hpp>
using namespace godot;

// SkillSystem
class SkillSystem : public Node {
    GDCLASS(SkillSystem, Node)
protected:
    static void _bind_methods() {}
public:
    void _ready() override { UtilityFunctions::print("SkillSystem hazır"); }
};

// MultiplayerManager
class MultiplayerManager : public Node {
    GDCLASS(MultiplayerManager, Node)
protected:
    static void _bind_methods() {}
public:
    void _ready() override { UtilityFunctions::print("MultiplayerManager hazır"); }
};

// PerformanceManager
class PerformanceManager : public Node {
    GDCLASS(PerformanceManager, Node)
protected:
    static void _bind_methods() {}
public:
    void _ready() override { UtilityFunctions::print("PerformanceManager hazır"); }
};

// DebugManager
class DebugManager : public Node {
    GDCLASS(DebugManager, Node)
protected:
    static void _bind_methods() {}
public:
    void _ready() override { UtilityFunctions::print("DebugManager hazır"); }
};

// AnalyticsManager
class AnalyticsManager : public Node {
    GDCLASS(AnalyticsManager, Node)
protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("log_event", "event_name"), &AnalyticsManager::log_event);
    }
public:
    void _ready() override { UtilityFunctions::print("AnalyticsManager hazır"); }
    void log_event(String event_name) {
        UtilityFunctions::print("Analytics: ", event_name);
    }
};

#endif
