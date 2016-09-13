#!/bin/bash

SIGNAL=~/local-area/Stop4Body/nTuples_v2016-08-31/T2DegStop_300_270.root
BACKGROUND=~/local-area/Stop4Body/nTuples_v2016-08-31/Background.root

if [[ -f ${SIGNAL} && -f ${BACKGROUND} ]] ; then
  trainMVA --method BDT --signalFile ${SIGNAL} --backgroundFile ${BACKGROUND}
#  root runTMVAGui.C
  #DIR=$(pwd)
  #echo "Changing to TMVAGui directory"
  #cd TMVAGui
  #echo "Running TMVAGui.C"
  #root TMVAGui.C\(\"${DIR}/TMVA.root\"\)
  #echo "Returning to starting directory"
  #cd $DIR
fi

