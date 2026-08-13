extends Control

@onready var crystal_count = $CrystalPanel/CrystalCount

func _ready():
	# Kristal sayısını yükle
	var saved_data = SaveManager.get_save_data() if SaveManager.has_method("get_save_data") else {}
	var crystals = saved_data.get("total_crystals", 0)
	crystal_count.text = str(crystals)
	
	# Müzik çal
	if AudioManager.has_method("play_music"):
		AudioManager.play_music("menu_theme")
	
	print("Ana menü yüklendi")

func _on_play_pressed():
	print("Oyna butonuna basıldı")
	get_tree().change_scene_to_file("res://scenes/level_test.tscn")

func _on_shop_pressed():
	print("Mağaza açılıyor...")
	# get_tree().change_scene_to_file("res://scenes/shop.tscn")

func _on_settings_pressed():
	print("Ayarlar açılıyor...")

func _on_exit_pressed():
	print("Oyundan çıkılıyor...")
	get_tree().quit()
