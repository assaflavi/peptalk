#!/bin/bash

resultsDir=$1
for k in `seq 1 8`; do
    outfile="$resultsDir/roc.top$k.clusters.txt"
    cat /dev/null > $outfile
    echo -e "#PDB\tTPR\tSPECIFICITY" >> $outfile
    for f in $resultsDir/*quality.txt; do
	    filename=`basename $f`
	    pdbid=${filename%%.*}
	
	    tpr=`cat $f | egrep -v '^#' | head -$k | awk '{sum=sum+$8}END{print sum}'`
        fpr=`cat $f | egrep -v '^#' | head -$k | awk '{sum=sum+$9}END{print sum}'`
	    #recall=`calc $tp/$tpfn`
	    #specificity=`calc $tp/$tpfp`
	    #echo $coverage $size $tp $tpfp $tpfn
	    echo -e "$pdbid\t$tpr\t$fpr" >> $outfile
    done # | awk '{sum=sum+$1;}END{print sum/NR}'
done

