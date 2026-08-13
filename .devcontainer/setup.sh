#!/bin/bash
set -e

echo "🎮 Godot 4 Kurulumu Başlıyor..."

GODOT_VERSION="4.2.1"
GODOT_URL="https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_linux.x86_64.zip"
GODOT_TEMPLATES="https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-stable_export_templates.tpz"

# Godot indir ve kur
if [ ! -f /usr/local/bin/godot ]; then
    echo "📥 Godot indiriliyor..."
    wget -q --show-progress "$GODOT_URL" -O godot.zip
    unzip -q godot.zip
    mv Godot_v${GODOT_VERSION}-stable_linux.x86_64 godot
    chmod +x godot
    sudo mv godot /usr/local/bin/
    rm godot.zip
    echo "✅ Godot kuruldu!"
else
    echo "✅ Godot zaten kurulu"
fi

# Godot C++ bindings (godot-cpp)
if [ ! -d "godot-cpp" ]; then
    echo "📥 godot-cpp indiriliyor..."
    git clone https://github.com/godotengine/godot-cpp.git
    cd godot-cpp
    git checkout 4.2.1-stable
    git submodule update --init --recursive
    cd ..
    echo "✅ godot-cpp hazır!"
fi

# Build araçları
echo "🔧 Build araçları kuruluyor..."
sudo apt-get update -qq
sudo apt-get install -y -qq \
    scons \
    build-essential \
    pkg-config \
    libx11-dev \
    libxcursor-dev \
    libxinerama-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libasound2-dev \
    libpulse-dev \
    libudev-dev \
    libxi-dev \
    libxrandr-dev \
    yasm

# Android SDK (isteğe bağlı)
if [ ! -d "android-sdk" ]; then
    echo "📱 Android SDK indiriliyor..."
    mkdir -p android-sdk
    cd android-sdk
    wget -q https://dl.google.com/android/repository/commandlinetools-linux-9477386_latest.zip
    unzip -q commandlinetools-linux-9477386_latest.zip
    mkdir -p cmdline-tools/latest
    mv cmdline-tools/* cmdline-tools/latest/ 2>/dev/null || true
    rm commandlinetools-linux-9477386_latest.zip
    cd ..
    echo "✅ Android SDK hazır!"
fi

echo ""
echo "🎉 Kurulum tamamlandı!"
echo "Godot versiyonu: $(godot --version 2>/dev/null || echo 'Kontrol edilemedi')"
echo ""
echo "Kullanım:"
echo "  godot --editor project.godot    # Editörü aç"
echo "  scons platform=linux            # Linux için derle"
echo "  scons platform=android          # Android için derle"
