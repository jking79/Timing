#!/bin/bash

cutconfig=${1:-"cut_config/signal_blinded_hlt.txt"}
plotconfig=${2:-"plot_config/phopt_0.txt"}
outfiletext=${3:-"phopt_0"}
dir=${4:-"plots"}

root -l -b -q runTreePlotter.C\(\"${cutconfig}\",\"${plotconfig}\",\"${outfiletext}\"\)

## copy out
topdir=/afs/cern.ch/user/k/kmcdermo/www
fulldir=${topdir}/dispho/${dir}

mkdir -p ${fulldir}
pushd ${topdir}
./makereadable.sh ${fulldir}
popd

cp ${outfiletext}_log.png ${outfiletext}_lin.png ${outfiletext}.root ${fulldir}
