#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class AudioManager : public Node {
    GDCLASS(AudioManager, Node)
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    
    void play_music(String track_name);
    void play_sfx(String sound_name);
    void stop_music();
    
    void set_master_volume(float volume);
    void set_music_volume(float volume);
    void set_sfx_volume(float volume);
};
#endif
