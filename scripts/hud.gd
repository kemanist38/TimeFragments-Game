extends Control

@onready var health_bar = $MarginContainer/VBoxContainer/TopBar/HealthContainer/HealthBar
@onready var time_bar = $MarginContainer/VBoxContainer/TopBar/TimeContainer/TimeBar
@onready var crystal_count = $MarginContainer/VBoxContainer/TopBar/CrystalContainer/CrystalCount
@onready var fps_label = $MarginContainer/VBoxContainer/FPSLabel
@onready var time_button = $MarginContainer/VBoxContainer/CenterContainer/TimeButton
@onready var level_label = $MarginContainer/VBoxContainer/LevelLabel

var player = null
var time_controller = null

func _ready():
	await get_tree().process_frame
	player = get_tree().get_first_node_in_group("player")
	time_controller = get_node_or_null("/root/LevelTest/TimeController")
	
	if time_controller and time_controller.has_signal("time_energy_changed"):
		time_controller.connect("time_energy_changed", _on_time_energy_changed)
	
	print("HUD hazır")

func _process(delta):
	# FPS güncelle
	fps_label.text = "FPS: " + str(Engine.get_frames_per_second())
	
	# Zaman butonu görünürlüğü
	if time_controller and time_controller.has_method("can_rewind"):
		time_button.visible = time_controller.can_rewind()

func _on_time_energy_changed(new_energy):
	time_bar.value = new_energy

func update_crystals(amount):
	crystal_count.text = str(amount)

func update_health(health):
	health_bar.value = health

func _on_pause_pressed():
	print("Oyun duraklatıldı")
	get_tree().paused = true
	# Pause menüsü göster

func show_message(text: String, duration: float = 2.0):
	var label = Label.new()
	label.text = text
	label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	label.add_theme_font_size_override("font_size", 48)
	add_child(label)
	
	await get_tree().create_timer(duration).timeout
	label.queue_free()
