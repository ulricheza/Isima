#!/bin/bash

echo "Copie du tarball de povray" >> output.txt
lcg-cp lfn:/grid/biomed/mip/jopasserat/escourbi/povray.tgz ./povray.tgz >> output.txt
echo "Decompression du tarball"
tar -xvzf ./povray.tgz >> output.txt
echo "Execution de povray"
cd ./povray
./povray +A +W640 +H480 +Lshare/povray-3.6/include/ +SF1 +EF20 ./glsbng.ini >> output.txt
echo "Exportation des resultats"
echo "Listing des resultats"
ls ./glsbng*.png >> output.txt
LISTE=`ls ./glsbng*.png` >> output.txt

echo "copie sur le lfn" >> output.txt
export LFC_HOST="lfc-biomed.in2p3.fr" >> output.txt
for i in $LISTE
do
   echo $i >> output.txt
   lcg-cr -d cirigridse01.univ-bpclermont.fr -l lfn:/grid/biomed/mip/jopasserat/escourbi/$i $i >> output.txt
done


