#!/bin/bash

N=200
iCh=1

rm output.log
touch output.log
i=$(cat output.log | wc -l)
while [ $i -lt 200 ]
do
    echo $i
    ./AlGen $N $iCh 740 46 1080 50 34 >> output.log
    i=$(cat output.log | grep f= | wc -l)
done

value=$(cat output.log | grep "f=20.19" | wc -l)
all=$(cat output.log | grep "f=" | wc -l)

echo "$value / $all"
