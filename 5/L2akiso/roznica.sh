cat $1>temp
cat $2>>temp
sort temp > temp2
uniq temp2 >temp3
rm temp
rm temp2
cat Plik2>>temp3
sort temp3>temp4
uniq -u temp4 > Roznica
rm temp3
rm temp4

