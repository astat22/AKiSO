#differentia="$(diff Plik1 Plik2)"
#
#if [ -n "$differentia" ]; then
#   echo "$differentia"
#fi
#
#cat ./temp5 | awk '{print $2}' >temp6
#sed "4q;d" ./temp5
#
#sed "2q;d" ./temp5 | awk -v N=2 '{print $N}'

#ala="ala"
#kot="kot"
#if [  $ala == $kot ] 
#then
#   echo $ala" "$kot
#fi

#du ./neural.pdf | awk '{print $1}'
a=$(date +%s)
b="$(du $1 | awk '{print $1}')"
echo $a" "$b
