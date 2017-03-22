#!/bin/sh

apply=${1:-1}

# inclusive
for vid in none medium
do
    for HT in 40To100 100To200 200To400 400To600 600ToInf
    do
	root -l -b -q "runPhotonPlots_HT.C("\"${vid}\",\"GJets\",\"${HT}\",${apply},0,0,1,0")"
    done
done

# isEB
for vid in none medium
do
    for HT in 40To100 100To200 200To400 400To600 600ToInf
    do
	root -l -b -q "runPhotonPlots_HT.C("\"${vid}\",\"GJets\",\"${HT}\",${apply},1,0,1,0")"
    done
done

# isEE
for vid in none medium
do
    for HT in 40To100 100To200 200To400 400To600 600ToInf
    do
	root -l -b -q "runPhotonPlots_HT.C("\"${vid}\",\"GJets\",\"${HT}\",${apply},0,1,1,0")"
    done
done
