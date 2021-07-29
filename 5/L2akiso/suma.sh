cat $1>temp
cat $2>>temp
sort temp > temp2
uniq temp2 >Suma
rm temp
rm temp2

