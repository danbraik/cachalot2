#!/bin/bash

# INSTALL CACHALOT 2

# get installation directory
echo "Enter directory path to install Cachalot binaries and data."
echo "(press enter to use default value /usr/local/lib/cachalot2/)"
echo " > "
read path

if [ "$path" == "" ] ; then
	path="/usr/local/lib/cachalot2"
fi

echo "Installation into : '$path'"

# create installation dir
if [ ! -d "$path/data" ] ; then
	mkdir -p "$path/data" || exit
fi

# copy program
cp cachalot2 $path/cachalot2 || exit

# create intermediate script
run="$path/cachalot2_run.sh"
touch $run || exit

echo '#!/bin/bash' > $run # erase content
echo "INSTALL_DIR=\"$path\"" >> $run
echo 'HISTORY_FILE=~/.cachalot2' >> $run
# get absolute path of the music file
echo 'FILE="$(pwd)/$1"' >> $run
# if $1 was absolute, reset FILE
echo '[ "$(echo "$1" | cut -b 1)" == "/" ] && FILE="$1"' >> $run
# if $1 was empty, reset FILE
echo '[ "$1" == "" ] && FILE=""' >> $run
echo 'cd $INSTALL_DIR' >> $run
echo './cachalot2 "$HISTORY_FILE" "$FILE"' >> $run

# set exection permission
chmod a+rx $path/cachalot2
chmod a+rx $path/cachalot2_run.sh

# copy data
echo "Copy of program data"
cp  "data/jennaSue.ttf"	"$path/data/jennaSue.ttf" || exit
cp  "data/widget.png" 	"$path/data/widget.png"

# create callable file (link to intermediate script)
bin="/usr/local/bin/cachalot2"

if [ -f $bin ] ; then
	rm $bin
fi

echo "Creation of the program link : '$bin'"
ln -s $path/cachalot2_run.sh $bin || exit
#chmod a+rx $bin || exit

echo "Installation successful !"
