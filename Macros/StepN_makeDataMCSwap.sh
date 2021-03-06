#!/bin/bash

. setupJSONs.sh
. setupPaths.sh

INPUT=${SWAP_DIR}
OUTPUT=~cbeiraod/local-area/Stop4Body/DataMCSwap
OUTPUT_POW=~cbeiraod/local-area/Stop4Body/DataMCSwap_pow
OUTPUT_LEP=~cbeiraod/local-area/Stop4Body/DataMCSwap_lep


if [[ -d ${INPUT} ]] ; then
  if [[ ! -d ${OUTPUT} ]] ; then
    mkdir -p ${OUTPUT}
  fi
  if [[ ! -d ${OUTPUT_POW} ]] ; then
    mkdir -p ${OUTPUT_POW}
  fi
  if [[ ! -d ${OUTPUT_LEP} ]] ; then
    mkdir -p ${OUTPUT_LEP}
  fi

  makePlots --json ${JSON_PATH}/plot2016swap.json     --outDir ${OUTPUT}     --inDir ${INPUT} --variables variables.json --cuts variables.json
  makePlots --json ${JSON_PATH}/plot2016swap_pow.json --outDir ${OUTPUT_POW} --inDir ${INPUT} --variables variables.json --cuts variables.json
  makePlots --json ${JSON_PATH}/plot2016swap_lep.json --outDir ${OUTPUT_LEP} --inDir ${INPUT} --variables variables.json --cuts variables.json
fi
