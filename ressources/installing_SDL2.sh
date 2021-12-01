#! /bin/bash

# This script is used to install the dependencies for the project.

# Colors codes.
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[35m"
ORANGE="\033[43m"
DEFAULT="\033[0m"

# Variable used as a boolean to know if the script achieved its goal.
IS_ERROR=0

# This function will check if SDL2 is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function checkSDL2()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2" ]; then
		echo -e ${YELLOW}"SDL2 is not installed. Installing it now..."${DEFAULT}
		brew install sdl2
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2 installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2 has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2 is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_image is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function checkSDL2_image()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_image" ]; then
		echo -e ${YELLOW}"SDL2_image is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_image
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_image installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_image has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_image is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_ttf is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function checkSDL2_ttf()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_ttf" ]; then
		echo -e ${YELLOW}"SDL2_ttf is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_ttf
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_ttf installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_ttf has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_ttf is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_mixer is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function checkSDL2_mixer()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_mixer" ]; then
		echo -e ${YELLOW}"SDL2_mixer is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_mixer
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_mixer installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_mixer has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_mixer is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_net is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function checkSDL2_net()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_net" ]; then
		echo -e ${YELLOW}"SDL2_net is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_net
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_net installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_net has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_net is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_gfx is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function checkSDL2_gfx()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_gfx" ]; then
		echo -e ${YELLOW}"SDL2_gfx is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_gfx
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_gfx installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_gfx has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_gfx is already installed."${DEFAULT}
	fi
}

# This function will check if brew is installed.
# If it is not installed, it will install it with curl.
# If any error occurs, it will return 1.
function checkBrew()
{
	if [ ! -d "$HOME/.brew" ]; then
		echo -e ${YELLOW}"Brew is not installed. Installing it now..."${DEFAULT}
		/bin/zsh -c "rm -rf $HOME/.brew && git clone --progress --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update"
		if [ $? -ne 0 ]; then
			echo -e ${RED}"Brew installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"Brew has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"Brew is already installed."${DEFAULT}
	fi
}

# This function will download a picture to the ressource folder.
# Only if the installation is successful.
function downloadPicture()
{
	if [ ! -d "./ressources/great.png" ]; then
		curl -s -o ./ressources/great.png https://cdn.intra.42.fr/users/medium_chdespon.jpg
		if [ $? -ne 0 ]; then
			echo -e ${ORANGE}"Download of the picture failed."${DEFAULT}
			IS_ERROR=1
		fi
	fi
}


function main()
{
	echo -e ${PURPLE}"Installing requirements..."${DEFAULT}
	checkBrew
	if [ $IS_ERROR -eq 0 ]; then
		checkSDL2
		if [ $IS_ERROR -eq 0 ]; then
			checkSDL2_image
			checkSDL2_ttf
			checkSDL2_mixer
			checkSDL2_net
			checkSDL2_gfx
		fi
	fi
	if [ $IS_ERROR -eq 0 ]; then
		downloadPicture
	fi
	if [ $IS_ERROR -eq 0 ]; then
		echo -e ${GREEN}"Requirements have been installed."${DEFAULT}
	else
		echo -e ${RED}"An error occured during the installation."${DEFAULT}
		return 1
	fi
}

main