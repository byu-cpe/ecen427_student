sudo dmesg --clear
echo "----------Attempt 1----------" | sudo tee /dev/kmsg
sudo insmod audio_codec.ko
ls -la /dev/audio_codec /dev/ecen427/audio_codec
sudo rmmod audio_codec
echo "----------Attempt 2----------" | sudo tee /dev/kmsg
sudo insmod audio_codec.ko
ls -la /dev/audio_codec /dev/ecen427/audio_codec
sudo rmmod audio_codec
dmesg 