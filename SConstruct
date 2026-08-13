#!/usr/bin/env python
import os
import sys

# Godot-cpp yolunu kontrol et
godot_cpp_path = "godot-cpp"
if not os.path.exists(godot_cpp_path):
    print("HATA: godot-cpp bulunamadı!")
    print("Lütfen şunu çalıştırın: git clone https://github.com/godotengine/godot-cpp.git")
    sys.exit(1)

# Godot-cpp SConstruct'ını yükle
env = SConscript(os.path.join(godot_cpp_path, "SConstruct"))

# Derleme bayrakları
env.Append(CPPPATH=["src/"])
env.Append(CPPDEFINES=["DEBUG_ENABLED"])

# Kaynak dosyalar
sources = Glob("src/*.cpp")

# Çıktı kütüphanesi
library_name = "libtimefragments"
if env["platform"] == "windows":
    library_name += ".dll"
elif env["platform"] == "macos":
    library_name += ".dylib"
else:
    library_name += ".so"

library_path = "demo/bin/{}.{}{}".format(
    library_name,
    env["platform"],
    env["suffix"]
)

# Kütüphaneyi oluştur
library = env.SharedLibrary(
    target=library_path,
    source=sources
)

# Varsayılan hedef
Default(library)

# Bilgi mesajı
print("Platform: {}".format(env["platform"]))
print("Hedef: {}".format(library_path))
print("Kaynaklar: {}".format([str(s) for s in sources]))
