#!/bin/bash

alias cmsenv='eval `scramv1 runtime -sh`'

cd /exper-sw/cmst3/cmssw/users/cbeiraod/
. setup.sh

cd /exper-sw/cmst3/cmssw/users/cbeiraod/Stop4Body/CMSSW_8_0_14/src/
#cd $CMSSW_BASE/src/
eval `scramv1 runtime -sh`

#cd /exper-sw/cmst3/cmssw/users/cbeiraod/CMSSW_8_0_14/src/UserCode/Stop4Body/Macros/
cd UserCode/Stop4Body/Macros/

. setupJSONs.sh
. setupPaths.sh

INPUT=~/local-area/Stop4Body/nTuples_v2017-10-19
INPUT_TEST=~/local-area/Stop4Body/nTuples_v2017-10-19_test
INPUT_SWAP=~/local-area/Stop4Body/nTuples_v2017-08-13_swap
OUTPUT=~/local-area/Stop4Body/ANPlots/

deltaM=70

if [[ -d ${INPUT} ]] ; then
  VARIABLE_JSON=variablesAN_BDT_AR.json

  JSONFILE=variablesAN_BDT_VR3.json
  makePlots --json ${JSON_PATH}/plot2016_DM${deltaM}RP.json --outDir ${OUTPUT}/BDT/DeltaM${deltaM}/VR3 --inDir ${INPUT}_bdt${deltaM}/ --variables ${VARIABLE_JSON} --cuts ${JSONFILE} --suffix bdt --unblind --final
fi