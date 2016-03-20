#/bin/sh

printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

for file in $1/*.go;
do
	printf "On file $file\n\n"
	./run.sh go.l go.y $file
	printf "\n\nEnd file $file\n\n"
	printf "________________________________________________________________\n\n"
done