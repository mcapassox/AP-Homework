n=50
for d in 10 50 100 200 500 700 1000
do
	./mm_test ${n} ${d} >> const_n.csv
done

d=600
for n in 1 2 4 8 16 32 50
do
	./mm_test ${n} ${d} >> const_d.csv
done
