# The steps to install the game from scratch are the following

# Define color codes
GREEN='\033[0;32m'
BLUE='\033[94m'
NC='\033[0m'  # No color

#CLEAN INSTALLATION:
echo -e "${BLUE}Removing any previous installation of Left4Dead...${NC}"

sudo rm /usr/bin/Left4Dead ||
sudo rm /usr/bin/Left4DeadServer ||

sudo rm -r /etc/Left4dead ||
sudo rm -r /var/Left4dead ||

echo -e "${GREEN}OLD FILES REMOVED${NC}"


echo "Running the installer for the game Left4Dead."

# Check the user's choice
if [[ $choice == [Nn] ]]; then
    echo "Installer execution stopped."
    exit 0  # Exit the script with a success status
else
    echo -e "${GREEN}Continuing with the installer...${NC}"
fi

echo -e "${BLUE}Step 0 - Updating and downloading essentials...${NC}"

# 0.0 - First, we update our system's repositories
sudo apt update

# 0.1 - And install gcc and other esential tools
sudo apt install build-essential
sudo apt install git

echo -e "${GREEN}Step 0 - Completed${NC}"

# 1 - Download CMake - version 3.26 or above is needed
echo -e "${BLUE}Step 1 - Downloading CMake...${NC}"
# sudo apt install python3-pip
# pip install cmake --upgrade
sudo apt install cmake
echo -e "${GREEN}Step 1 - Completed${NC}"


# 2 - SDL2
echo -e "${BLUE}Step 2 - Downloading SDL...${NC}"

# 2.1 Install basic dependencies
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

git clone https://github.com/libsdl-org/SDL.git --branch release-2.26.5

cd SDL
mkdir build
cd build
cmake .. && make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 2 - Completed${NC}"



# 2.2 - Download and install SDL_Image
echo -e "${BLUE}Step 2.1 - Downloading SDL2_image...${NC}"

git clone --branch release-2.6.3 https://github.com/libsdl-org/SDL_image.git

cd SDL_image
git checkout SDL2
mkdir build
cd build
cmake .. && make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 2.1 - Completed${NC}"

# 2.3 - Download and install SDL_mixer
echo -e "${BLUE}Step 2.2 - Downloading SDL2_mixer...${NC}"

git clone --branch release-2.6.3 https://github.com/libsdl-org/SDL_mixer.git

cd SDL_mixer
git checkout SDL2
mkdir build
cd build
cmake .. && make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 2.2 - Completed${NC}"

# 2.4 - Download and install SDL_ttf
echo -e "${BLUE}Step 2.3 - Downloading SDL_ttf...${NC}"

git clone --branch release-2.20.2 https://github.com/libsdl-org/SDL_ttf.git

cd SDL_ttf
git checkout SDL2
mkdir build
cd build
cmake .. && make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 2.3 - Completed${NC}"


echo -e "${BLUE}Step 2.4 - Downloading sdl2pp...${NC}"
git clone https://github.com/libSDL2pp/libSDL2pp.git --branch 0.18.1

cd libSDL2pp
mkdir build
cd build
cmake .. && make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 2.4 - Completed${NC}"

# 3 - Catch2
echo "Step 3 - Downloading Catch2..."
git clone https://github.com/catchorg/Catch2.git --branch devel

cd Catch2
mkdir build
cd build
cmake .. && make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 3 - Completed${NC}"

# 4 - Qt
echo "Step 4 - Downloading Qt..."
sudo apt install qtbase5-dev qt5-qmake qtbase5-dev-tools
echo -e "${GREEN}Step 4 - Completed${NC}"

# 5
echo -e "${BLUE}Step 5 - Downloading yaml dependencies...${NC}"

git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build
cd build
cmake ..
make -j6
sudo make install

cd ../../
echo -e "${GREEN}Step 5 - Completed${NC}"

# 6 - Downloading the game itself
echo -e "${BLUE}Step 6 - Downloading the game...${NC}"
sudo rm /usr/lib/x86_64-linux-gnu/libSDL2*
git clone https://github.com/Merok23/TPG-Taller-Left4dead-Grupo1.git --branch main

cd TPG-Taller-Left4dead-Grupo1
mkdir build
cd build
cmake .. && make -j6

echo -e "${GREEN}Step 6 - Completed${NC}"

# 7 
echo -e "${BLUE}Step 7 - Moving files to correct folders...${NC}"


# executables to /usr/bin
cd target
sudo mv Left4Dead /usr/bin/
sudo mv Left4DeadServer /usr/bin/

cd ../../client
#config files to /etc/Left4Dead
sudo mkdir /etc/Left4Dead
sudo mv client_config.yaml /etc/Left4Dead/
cd ../config
sudo mv config.yaml /etc/Left4Dead/


cd .. # in TPG-Taller-Left4dead-Grupo1
#data files to /var/Left4Dead
sudo mkdir /var/Left4Dead
sudo mv client /var/Left4Dead/client
sudo mv server /var/Left4Dead/server
sudo mv assets /var/Left4Dead/assets

# New absolute path that the client_config will have
# /var/Left4Dead/assets/Zombie/
#
# New absolute path that the env variable will have
# LEFT4DEAD_CLIENT_CONFIG_FILE="/etc/Left4Dead/client_config.yaml"

echo -e "${GREEN}Step 7 - Completed${NC}"

echo -e "${BLUE}Step 8 - Creating Desktop Shorcuts in ~/Desktop${NC}"

sudo mv Left4Dead.sh ~/Desktop
sudo mv Left4DeadServer.sh ~/Desktop

echo -e "${GREEN}Installation Completed, enjoy your game!${NC}"

#-------------------------------------Removing source files for libs----------------------------------------------#
cd .. #in home
#estando en la carpeta base:
sudo rm -r yaml-cpp
sudo rm -r Catch2
sudo rm -r libSDL2pp
sudo rm -r SDL_ttf
sudo rm -r SDL_mixer
sudo rm -r SDL_image
sudo rm -r SDL
sudo rm -r TPG-Taller-Left4dead-Grupo1


#in /usr/bin the client has to run
#export LEFT4DEAD_CLIENT_CONFIG_FILE="/etc/Left4Dead/client_config.yaml"


echo -e "\n\n\n${GREEN}The game was successfully installed and can now be run.${NC}"

#in /usr/bin the client has to run
#cd /usr/bin
#export LEFT4DEAD_CLIENT_CONFIG_FILE="/etc/Left4Dead/client_config.yaml"