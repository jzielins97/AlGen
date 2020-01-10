#!/bin/bash

N=5000
iCh=1

rm test.log
touch test.log
for i in {1..100}
do
  ./AlGen $N $iCh | grep f= >> test.log
done

cat test.log | grep 19. | wc -l
