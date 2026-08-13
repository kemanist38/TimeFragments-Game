#ifndef TIME_CONTROLLER_H
#define TIME_CONTROLLER_H

#include <godot_cpp/classes/node3d.hpp>
#include <vector>

using namespace godot;

class TimeController : public Node3D {
    GDCLASS(TimeController, Node3D)
    
private:
    float time_scale = 1.0f;
    float reverse_time_scale = -1.0f;
    bool is_time_reversed = false;
    bool is_rewinding = false;
    std::vector<Vector3> position_history;
    std::vector<Quaternion> rotation_history;
    int max_history_size = 180; // 3 saniye @ 60fps
    float time_energy = 100.0f;
    float max_time_energy = 100.0f;
    float energy_drain_rate = 30.0f; // Saniyede harcanan enerji
    float energy_regen_rate = 10.0f; // Saniyede yenilen enerji
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    void _process(double delta) override;
    
    void start_rewind();
    void stop_rewind();
    void toggle_time_direction();
    void record_state(Vector3 pos, Quaternion rot);
    void restore_state(Vector3 &pos, Quaternion &rot);
    
    bool can_rewind() const;
    float get_time_energy() const;
    float get_time_scale() const;
    
    void set_time_energy(float energy);
    void add_time_energy(float amount);
};

#endif
