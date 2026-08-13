# Android Build

## Gerekli Adımlar:

1. Android SDK yüklü olmalı
2. JAVA_HOME ayarlanmış olmalı
3. Debug/Release keystore oluşturulmalı

## Keystore Oluşturma:
```bash
keytool -genkey -v -keystore debug.keystore -alias androiddebugkey -storepass android -keypass android -keyalg RSA -validity 10000
