#!/bin/bash

var=${1:-"phopt_0"}
commoncut=${2:-"phopt_0>20.0"}
text=${3:-"overplot"}
nbinsx=${4:-100}
xlow=${5:-0}
xhigh=${6:-100}
islogx=${7:-0}
islogy=${8:-0}
title=${9:-${var}}
xtitle=${10:-${var}}
ytitle=${11:-"Events"}

root -l -b -q runTreePlotter.C\(\"${var}\",\"${commoncut}\",\"${text}\",${nbinsx},${xlow},${xhigh},${islogx},${islogy},\"${title}\",\"${xtitle}\",\"${ytitle}\"\)
