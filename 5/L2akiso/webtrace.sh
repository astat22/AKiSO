links -dump "$1" > temp1
while [ -z "$differentia" ]; do
   sleep $2
   links -dump "$1" > temp2
   differentia="$(diff temp1 temp2)"
   rm temp2
done
rm temp1
xmessage "$differentia"
