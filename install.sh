#! /bin/bash

clear
cat misc/worms.txt
if [ -z "$host" ]
then
    host=`uname -n`
    echo "Bonjour $host"
fi
/usr/bin/sudo pacman -S lsb-release -y
/usr/bin/sudo /usr/bin/aptitude install lsb
/usr/bin/sudo zypper install lsb -y

OS=$(lsb_release -si)

#set du dossier de destination
destination="./"

#set du nombre de threads
threads=$(/bin/cat /proc/cpuinfo | /bin/grep processor | /usr/bin/wc -l)
threads=$(($threads * 2))

if [ "$OS" = "Ubuntu" ]; then
    cat misc/ubuntu.txt
    /usr/bin/sudo apt-get install emacs build-essential subversion xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libsdl1.2-dev libsdl2-dev libsfml-dev cmake
elif [ "$OS" = "Debian" ]; then
    cat misc/debian.txt
    /usr/bin/sudo apt-get install emacs build-essential subversion xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libsdl1.2-dev libsdl2-dev libsfml-dev cmake
elif [ "$OS" = "Arch" ]; then
    cat misc/arch.txt
    /usr/bin/sudo pacman -S emacs base-devel subversion xorg-server-devel libxxf86vm  mesa sdl sfml cmake -y
elif [ "$OS" = "openSUSE Leap" ]; then
    /usr/bin/sudo zypper addrepo http://download.opensuse.org/repositories/games/openSUSE_Leap_42.2/games.repo
    /usr/bin/sudo zypper refresh
    /usr/bin/sudo zypper install SDL
    /usr/bin/sudo zypper addrepo http://download.opensuse.org/repositories/games/openSUSE_Leap_42.3/games.repo
    /usr/bin/sudo zypper refresh
    /usr/bin/sudo zypper install SDL
    wget http://software.opensuse.org/ymp/home:ykoba/openSUSE_Leap_42.2/sfml.ymp
    packages=(./sfml.ymp); 
    /usr/bin/sudo zypper in "${packages[@]}"
    /usr/bin/sudo zypper install -t pattern devel_C_C++
    /usr/bin/sudo zypper install emacs subversion xorg-x11-server Mesa libXext-devel Mesa-libGL1 libXext-devel libSDL-1_2-0 cmake #libXxf86vm
else
    echo -e "OS inconnu"
fi

#compilation
rm irrlicht-1.8.4.zip
wget http://downloads.sourceforge.net/irrlicht/irrlicht-1.8.4.zip
unzip irrlicht-1.8.4.zip
rm irrlicht-1.8.4.zip
cd  $destination/irrlicht-1.8.4/source/Irrlicht
make -j $threads

#installation
cd ../..
/usr/bin/sudo cp -r include/* /usr/local/include
/usr/bin/sudo cp lib/Linux/libIrrlicht.a /usr/local/lib

#message de fin d'installation

echo "installation de la lib terminée."
echo "Voulez vous compiler le jeu? [O/n]"
read rep
if [ "$rep" == "o" ] || [ ${#rep} -eq 0 ] || [ "$rep" == "O" ]
then
    echo "compilation"
    cd ..
    rm CMakeCache.txt
    cmake .
    make
else
    echo "saut de l'etape de compilation" 
fi
echo "Voulez vous lancer le jeu? [O/n]"
read rep
if [ "$rep" == "o" ] || [ ${#rep} -eq 0 ] || [ "$rep" == "O" ]
then
    cat misc/end.txt
    echo "Lancement du jeu" &&  sleep 1 &&./indie_studio
else
    echo "saut de l'etape de Lancement du jeu" 
fi
