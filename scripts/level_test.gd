extends Node3D

var crystals_collected = 0
var level_time = 0.0
var is_level_complete = false

@onready var player = $Player
@onready var hud = $CanvasLayer/HUD

func _ready():
	print("Test seviyesi yüklendi!")
	
	# Player'ı gruba ekle
	player.add_to_group("player")
	
	# Müzik çal
	if AudioManager.has_method("play_music"):
		AudioManager.play_music("level_theme")
	
	# Zaman kontrolcüsü bağla
	var time_ctrl = $TimeController
	if time_ctrl and time_ctrl.has_signal("time_rewind_started"):
		time_ctrl.connect("time_rewind_started", _on_time_rewind_started)

func _process(delta):
	if not is_level_complete:
		level_time += delta

func _on_crystal_collected(body):
	if body.is_in_group("player"):
		crystals_collected += 1
		hud.update_crystals(crystals_collected)
		
		# Ses efekti
		if AudioManager.has_method("play_sfx"):
			AudioManager.play_sfx("crystal_collect")
		
		# Kristali sil
		var crystal = get_node_or_null("Crystals/Crystal1")
		if crystal:
			crystal.queue_free()
		
		print("Kristal toplandı! Toplam: ", crystals_collected)

func _on_goal_reached(body):
	if body.is_in_group("player") and not is_level_complete:
		is_level_complete = true
		complete_level()

func complete_level():
	print("Seviye tamamlandı! Süre: ", level_time)
	hud.show_message("SEVİYE TAMAMLANDI!", 3.0)
	
	# Ses efekti
	if AudioManager.has_method("play_sfx"):
		AudioManager.play_sfx("level_complete")
	
	# Seviye istatistiklerini kaydet
	if SaveManager.has_method("save_game"):
		SaveManager.save_game()
	
	# Ana menüye dön
	await get_tree().create_timer(3.0).timeout
	get_tree().change_scene_to_file("res://scenes/main_menu.tscn")

func _on_time_rewind_started():
	print("Zaman geri sarma başladı!")
