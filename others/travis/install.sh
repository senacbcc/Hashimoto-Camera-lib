echo "Instalação da Biblioteca Allegro 5"
arch=$(uname -m)
if [ "$arch" == "i686" -o "$arch" == "i386" -o "$arch" == "i486" -o "$arch" == "i586" ]; then
flag=1
else
flag=0
fi
echo "Atualizando Sistema... "
sudo apt-get update
echo "Instalando Dependencias... "
sudo apt-get -y install libgl1-mesa-dev
sudo apt-get -y install libglu1-mesa-dev
sudo apt-get -y install cmake
sudo apt-get -y build-essential
sudo apt-get -y make
sudo apt-get -y libxcursor-dev
sudo apt-get install -y cmake g++ freeglut3-dev libxcursor-dev libpng12-dev libjpeg-dev libfreetype6-dev libgtk2.0-dev libasound2-dev libpulse-dev libopenal-dev libflac-dev libdumb1-dev libvorbis-dev libphysfs-dev
sudo apt-get install -y libpng-dev libz-dev libcurl4-gnutls-dev libfreetype6-dev libasound-dev
echo "Baixando Allegro 5 ..."
git clone git://git.code.sf.net/p/alleg/allegro
echo "Instalando Allegro 5..."
cd allegro
git checkout 5.0
cmake -DCMAKE_INSTALL_PREFIX=/usr .
make
sudo make install
cd ..
echo "Allegro 5 Instalado"