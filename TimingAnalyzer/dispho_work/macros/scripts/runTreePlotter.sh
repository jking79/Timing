#!/bin/bash

cutconfig=${1:-"cut_config/signal_blinded_hlt.txt"}
plotconfig=${2:-"plot_config/phopt_0.txt"}
scalearea=${3:-0}
outfiletext=${4:-"phopt_0"}
dir=${5:-"plots"}

## first make plot
root -l -b -q runTreePlotter.C\(\"${cutconfig}\",\"${plotconfig}\",${scalearea},\"${outfiletext}\"\)

## make out dirs
topdir=/afs/cern.ch/user/k/kmcdermo/www
fulldir=${topdir}/dispho/${dir}

## make them readable
mkdir -p ${fulldir}
pushd ${topdir}
./makereadable.sh ${fulldir}
popd

## copy everything
cp ${outfiletext}_log.png ${outfiletext}_lin.png ${outfiletext}.root ${outfiletext}_integrals.txt ${fulldir}
