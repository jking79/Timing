#!/bin/bash

source scripts/skimAndMerge/common_variables.sh

## input
label=${1}

## GMSB
for lambda in 100 150 200 250 300 350 400 500 600
do
    for ctau in 0p001 0p1 10 200 400 600 800 1000 1200 10000
    do
	if [[ "${ctau}" == "0p1" ]]
	then
	    if [[ "${lambda}" == "500" ]] || [[ "${lambda}" == "600" ]]
	    then
		sctau="${ctau}"
	    else
		sctau="0_1";
	    fi
	fi

	gridpoint="L-${lambda}TeV_Ctau-${sctau}cm"
	nohup ./scripts/skimAndMerge/skimAndMerge_SignalGridPoint.sh ${label} "GMSB" ${gridpoint} >& GMSB_${gridpoint}_Skim.log &
    done
done

## HVDS
for mdp in 20 40 60
do
    for mzp in 300 500 800 1000
    do
	for ctau in 1 100 500 1000 2500 10000
	do
	    gridpoint="MZp-${mzp}_MDP-${mdp}_Ctau-${ctau}mm"
	    nohup ./scripts/skimAndMerge/skimAndMerge_SignalGridPoint.sh ${label} "HVDS" ${gridpoint} >& HVDS_${gridpoint}_Skim.log &
	done
    done
done