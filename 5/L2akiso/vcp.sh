startCp="$(date +%s)"
rozmiar="$(du $1 | awk '{print $1}')"
rozmiar=$(($rozmiar/1000))
cp $1 $2 &
skopiowano=0
while [ $skopiowano -lt $rozmiar ]; do
  skopiowano="$(du $2 | awk '{print $1}')"
  skopiowano=$(($skopiowano/1000))
  procent=$((1+100*$skopiowano/$rozmiar))
  aktualnie="$(date +%s)"
  uplynelo=$(($aktualnie-$startCp))
  szybkosc=$(($uplynelo/$procent))
  szacowany=$(( (100-$procent)*$szybkosc))
  echo -e -n "\rSkopiowano $procent\%, szacowany czas: $szacowany sek "
  #echo $skopiowano" "$procent" "$uplynelo" "$szybkosc" "$szacowany
  sleep 1
done

