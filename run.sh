make
echo "########## Ejecucion del compilador ########" > salida.txt
for f in  $( ls prueba ); do echo "Processing $f file..";
echo "" >> salida.txt
echo "############  ./lotes-primer-entrega/lote2/$f ##############" >> salida.txt
./ucc -c prueba/$f >> salida.txt
 done


