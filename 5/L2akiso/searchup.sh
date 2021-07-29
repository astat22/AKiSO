for f in "$(find $1/*)"; do
   a="$(md5sum $f | awk '{print $1}')"
   b="$(md5sum $f)" 
done

echo "$a">temp1
echo "$b">temp5
sort temp1>temp2
rm temp1
uniq -d temp2>temp3
rm temp2

n=$(cat temp5 | wc -l)
m=$(cat temp3 | wc -l)

for i in `seq 1 $n`; do
  for l in `seq 1 $m`; do
    suma="$(sed "$i q;d" ./temp5 | awk -v N=1 '{print $N}')"
    powt=$(sed "$l q;d" ./temp3 ) 
    if [ $suma == $powt ]; then
      echo "$(sed "$i q;d" ./temp5 | awk -v N=2 '{print $N}')" >> temp8
#      echo $powt" "$suma
    fi
  done
done
rm temp3
rm temp5

h=$(cat temp8 | wc -l)
for i in `seq 1 $h`; do
  du $(sed "$i q;d" ./temp8 )>>temp6 
done
rm temp8

sort -n temp6 
rm temp6
