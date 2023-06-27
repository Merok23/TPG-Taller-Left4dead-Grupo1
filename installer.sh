# The steps to install the game from scratch are the following

# Define color codes
GREEN='\033[0;32m'
NC='\033[0m'  # No color


echo "Hello! You are about to run the installer for our game, Left4Dead. It's a somewhat long installation, since
there are many libraries required. There will be messages like this one guiding you trough the installation, though, so don't worry"

echo "First things first, where should you run this installer? For now, we only support you running this installer in your
home directory, so that the libraries can be accesed from everywhere in your computer.

If you are not running this installer from the home terminal, please stop this installer, and run it again there."
read -p "Are you running the installer in your home directory? (y/n): " choice

# Check the user's choice
if [[ $choice == [Nn] ]]; then
    echo "Installer execution stopped."
    exit 0  # Exit the script with a success status
else
    echo -e "${GREEN}Continuing with the installer...${NC}"
fi

echo "Step 0 - Updating and downloading essentials..."

# 0.0 - First, we update our system's repositories
sudo apt update

# 0.1 - And install gcc and other esential tools
sudo apt install build-essential

echo -e "${GREEN}Step 0 - Completed${NC}"

# 1 - Download CMake - version 3.26 or above is needed
echo "Step 1 - Downloading CMake..."
sudo apt install cmake
echo -e "${GREEN}Step 1 - Completed${NC}"


# 2 - SDL2
echo "Step 2 - Downloading SDL..."

# 2.1 Install basic dependencies
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

# 2.2 - Download and install SDL_Image
echo "Step 2.1 - Downloading SDL_Image..."
# 2.2.1 - Define the GitHub repository and release tag
repo="libsdl-org/SDL_image"
tag="release-2.6.3"

# 2.2.2 - Retrieve the download URL of the release asset using GitHub API
url=$(curl -s "https://api.github.com/repos/$repo/releases/tags/$tag" | jq -r '.assets[0].browser_download_url')

# 2.2.3 - Download the zip file from the retrieved URL
wget -O SDL_Image.zip "$url"

# 2.2.4 - Unzip the downloaded file
unzip SDL_Image.zip

# 2.2.5 - Optional: Remove the zip file after extraction
#rm SDL_Image.zip

# 2.2.6 - Enter the folder and install the library
cd SDL_Image
git checkout SDL2
mkdir build
cd build
cmake ..
make -j4 # or as many cores as you have
sudo make install

# 2.2.7 - Back to the original folder
cd ../../
echo -e "${GREEN}Step 2.1 - Completed${NC}"

# 2.3 - Downloading and install SDL_Mixer
echo "Step 2.2 - Downloading SDL_Mixer..."
repo="libsdl-org/SDL_mixer"
tag="release-2.6.3"

url=$(curl -s "https://api.github.com/repos/$repo/releases/tags/$tag" | jq -r '.assets[0].browser_download_url')

wget -O SDL_Mixer.zip "$url"
unzip SDL_Mixer.zip
#rm SDL_Mixer.zip

cd SDL_Mixer
git checkout SDL2
mkdir build
cd build
cmake ..
make -j4 # or as many cores as you have
sudo make install

cd ../../
echo -e "${GREEN}Step 2.2 - Completed${NC}"

# 2.4 - Download and install SDL_TTF
echo "Step 2.3 - Downloading SDL_TTF..."
repo="libsdl-org/SDL_ttf"
tag="release-2.20.2"

url=$(curl -s "https://api.github.com/repos/$repo/releases/tags/$tag" | jq -r '.assets[0].browser_download_url')
wget -O SDL_TTF.zip "$url"
unzip SDL_TTF.zip

# 2.4.5 - Optional: Remove the zip file after extraction
#rm SDL_TTF.zip

cd SDL_TTF
git checkout SDL2
mkdir build
cd build
cmake ..
make -j4 # or as many cores as you have
sudo make install

cd ../../
echo -e "${GREEN}Step 2.3 - Completed${NC}"

# 2.5 - Download sdl2pp
echo "Step 3 - Downloading sdl2pp..."

repo="libSDL2pp/libSDL2pp"
tag="0.18.1"

# 2.3.2 - Retrieve the download URL of the release asset using GitHub API
url=$(curl -s "https://api.github.com/repos/$repo/releases/tags/$tag" | jq -r '.assets[0].browser_download_url')

# 2.3.3 - Download the zip file from the retrieved URL
wget -O SDL2pp.zip "$url"

# 2.3.4 - Unzip the downloaded file
unzip SDL2pp.zip

# 2.3.5 - Optional: Remove the zip file after extraction
#rm SDL2pp.zip

cd SDL2pp
git checkout SDL2
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../../
echo -e "${GREEN}Step 3 - Completed${NC}"

# 3 - Catch2
echo "Step 4 - Downloading Catch2..."

repo="catchorg/Catch2"
tag="v3.3.2"

# 2.3.2 - Retrieve the download URL of the release asset using GitHub API
url=$(curl -s "https://api.github.com/repos/$repo/releases/tags/$tag" | jq -r '.assets[0].browser_download_url')

# 2.3.3 - Download the zip file from the retrieved URL
wget -O Catch2.zip "$url"

# 2.3.4 - Unzip the downloaded file
unzip Catch2.zip

# 2.3.5 - Optional: Remove the zip file after extraction
#rm Catch2.zip

cd Catch2
mkdir build
cd build
Ejecuta los siguientes comandos para compilar e instalar Catch2:
cmake ..
make -j4
sudo make install

# cd ../../
echo -e "${GREEN}Step 4 - Completed${NC}"

# 4 - Qt
echo "Step 5 - Downloading Qt..."
sudo apt install qtbase5-dev qt5-qmake qtbase5-dev-tools
echo -e "${GREEN}Step 5 - Completed${NC}"

# 5 - Downloading the game itself
echo "Step 6 - Downloading the game..."
repo="Merok23/TPG-Taller-Left4dead-Grupo1"
tag="1.0"

# 2.3.2 - Retrieve the download URL of the release asset using GitHub API
url=$(curl -s "https://api.github.com/repos/$repo/releases/tags/$tag" | jq -r '.assets[0].browser_download_url')

# 2.3.3 - Download the zip file from the retrieved URL
wget -O Left4Dead.zip "$url"

# 2.3.4 - Unzip the downloaded file
unzip Left4Dead.zip

# 2.3.5 - Optional: Remove the zip file after extraction
#rm SDL2pp.zip

cd Left4Dead
mkdir build
cd build
cmake ..
make -j4


echo -e "${GREEN}Step 6 - Completed${NC}"

echo -e "\n\n\n${GREEN}The game was successfully installed and can now be run. \nTo execute, refer to the user manual${NC}"
