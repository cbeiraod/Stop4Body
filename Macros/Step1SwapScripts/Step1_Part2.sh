#!/bin/bash

alias cmsenv='eval `scramv1 runtime -sh`'

cd /exper-sw/cmst3/cmssw/users/cbeiraod/
. setup.sh

#cd /exper-sw/cmst3/cmssw/users/cbeiraod/CMSSW_8_0_14/src/
cd $CMSSW_BASE/src/
eval `scramv1 runtime -sh`

#cd /exper-sw/cmst3/cmssw/users/cbeiraod/CMSSW_8_0_14/src/UserCode/Stop4Body/Macros/
cd UserCode/Stop4Body/Macros/

. setupPaths.sh

#for DIR in "${NTUPLE_DIR}" "${TEST_DIR}" "${TRAIN_DIR}" ;do
  export DIR=${SWAP_DIR}
  echo "Processing directory: ${DIR}"

  hadd -f ${DIR}/T2DegStop_deltaM10.root ${DIR}/T2DegStop_250_240.root ${DIR}/T2DegStop_275_265.root ${DIR}/T2DegStop_300_290.root ${DIR}/T2DegStop_325_315.root ${DIR}/T2DegStop_350_340.root ${DIR}/T2DegStop_375_365.root ${DIR}/T2DegStop_400_390.root ${DIR}/T2DegStop_425_415.root ${DIR}/T2DegStop_450_440.root ${DIR}/T2DegStop_475_465.root ${DIR}/T2DegStop_500_490.root ${DIR}/T2DegStop_525_515.root ${DIR}/T2DegStop_550_540.root ${DIR}/T2DegStop_575_565.root ${DIR}/T2DegStop_600_590.root ${DIR}/T2DegStop_625_615.root ${DIR}/T2DegStop_650_640.root ${DIR}/T2DegStop_675_665.root ${DIR}/T2DegStop_700_690.root ${DIR}/T2DegStop_725_715.root ${DIR}/T2DegStop_750_740.root ${DIR}/T2DegStop_775_765.root ${DIR}/T2DegStop_800_790.root
  hadd -f ${DIR}/T2DegStop_deltaM20.root ${DIR}/T2DegStop_250_230.root ${DIR}/T2DegStop_275_255.root ${DIR}/T2DegStop_300_280.root ${DIR}/T2DegStop_325_305.root ${DIR}/T2DegStop_350_330.root ${DIR}/T2DegStop_375_355.root ${DIR}/T2DegStop_400_380.root ${DIR}/T2DegStop_425_405.root ${DIR}/T2DegStop_450_430.root ${DIR}/T2DegStop_475_455.root ${DIR}/T2DegStop_500_480.root ${DIR}/T2DegStop_525_505.root ${DIR}/T2DegStop_550_530.root ${DIR}/T2DegStop_575_555.root ${DIR}/T2DegStop_600_580.root ${DIR}/T2DegStop_625_605.root ${DIR}/T2DegStop_650_630.root ${DIR}/T2DegStop_675_655.root ${DIR}/T2DegStop_700_680.root ${DIR}/T2DegStop_725_705.root ${DIR}/T2DegStop_750_730.root ${DIR}/T2DegStop_775_755.root ${DIR}/T2DegStop_800_780.root
  hadd -f ${DIR}/T2DegStop_deltaM30.root ${DIR}/T2DegStop_250_220.root ${DIR}/T2DegStop_275_245.root ${DIR}/T2DegStop_300_270.root ${DIR}/T2DegStop_325_295.root ${DIR}/T2DegStop_350_320.root ${DIR}/T2DegStop_375_345.root ${DIR}/T2DegStop_400_370.root ${DIR}/T2DegStop_425_395.root ${DIR}/T2DegStop_450_420.root ${DIR}/T2DegStop_475_445.root ${DIR}/T2DegStop_500_470.root ${DIR}/T2DegStop_525_495.root ${DIR}/T2DegStop_550_520.root ${DIR}/T2DegStop_575_545.root ${DIR}/T2DegStop_600_570.root ${DIR}/T2DegStop_625_595.root ${DIR}/T2DegStop_650_620.root ${DIR}/T2DegStop_675_645.root ${DIR}/T2DegStop_700_670.root ${DIR}/T2DegStop_725_695.root ${DIR}/T2DegStop_750_720.root ${DIR}/T2DegStop_775_745.root ${DIR}/T2DegStop_800_770.root
  hadd -f ${DIR}/T2DegStop_deltaM40.root ${DIR}/T2DegStop_250_210.root ${DIR}/T2DegStop_275_235.root ${DIR}/T2DegStop_300_260.root ${DIR}/T2DegStop_325_285.root ${DIR}/T2DegStop_350_310.root ${DIR}/T2DegStop_375_335.root ${DIR}/T2DegStop_400_360.root ${DIR}/T2DegStop_425_385.root ${DIR}/T2DegStop_450_410.root ${DIR}/T2DegStop_475_435.root ${DIR}/T2DegStop_500_460.root ${DIR}/T2DegStop_525_485.root ${DIR}/T2DegStop_550_510.root ${DIR}/T2DegStop_575_535.root ${DIR}/T2DegStop_600_560.root ${DIR}/T2DegStop_625_585.root ${DIR}/T2DegStop_650_610.root ${DIR}/T2DegStop_675_635.root ${DIR}/T2DegStop_700_660.root ${DIR}/T2DegStop_725_685.root ${DIR}/T2DegStop_750_710.root ${DIR}/T2DegStop_775_735.root ${DIR}/T2DegStop_800_760.root
  hadd -f ${DIR}/T2DegStop_deltaM50.root ${DIR}/T2DegStop_250_200.root ${DIR}/T2DegStop_275_225.root ${DIR}/T2DegStop_300_250.root ${DIR}/T2DegStop_325_275.root ${DIR}/T2DegStop_350_300.root ${DIR}/T2DegStop_375_325.root ${DIR}/T2DegStop_400_350.root ${DIR}/T2DegStop_425_375.root ${DIR}/T2DegStop_450_400.root ${DIR}/T2DegStop_475_425.root ${DIR}/T2DegStop_500_450.root ${DIR}/T2DegStop_525_475.root ${DIR}/T2DegStop_550_500.root ${DIR}/T2DegStop_575_525.root ${DIR}/T2DegStop_600_550.root ${DIR}/T2DegStop_625_575.root ${DIR}/T2DegStop_650_600.root ${DIR}/T2DegStop_675_625.root ${DIR}/T2DegStop_700_650.root ${DIR}/T2DegStop_725_675.root ${DIR}/T2DegStop_750_700.root ${DIR}/T2DegStop_775_725.root ${DIR}/T2DegStop_800_750.root
  hadd -f ${DIR}/T2DegStop_deltaM60.root ${DIR}/T2DegStop_250_190.root ${DIR}/T2DegStop_275_215.root ${DIR}/T2DegStop_300_240.root ${DIR}/T2DegStop_325_265.root ${DIR}/T2DegStop_350_290.root ${DIR}/T2DegStop_375_315.root ${DIR}/T2DegStop_400_340.root ${DIR}/T2DegStop_425_365.root ${DIR}/T2DegStop_450_390.root ${DIR}/T2DegStop_475_415.root ${DIR}/T2DegStop_500_440.root ${DIR}/T2DegStop_525_465.root ${DIR}/T2DegStop_550_490.root ${DIR}/T2DegStop_575_515.root ${DIR}/T2DegStop_600_540.root ${DIR}/T2DegStop_625_565.root ${DIR}/T2DegStop_650_590.root ${DIR}/T2DegStop_675_615.root ${DIR}/T2DegStop_700_640.root ${DIR}/T2DegStop_725_665.root ${DIR}/T2DegStop_750_690.root ${DIR}/T2DegStop_775_715.root ${DIR}/T2DegStop_800_740.root
  hadd -f ${DIR}/T2DegStop_deltaM70.root ${DIR}/T2DegStop_250_180.root ${DIR}/T2DegStop_275_205.root ${DIR}/T2DegStop_300_230.root ${DIR}/T2DegStop_325_255.root ${DIR}/T2DegStop_350_280.root ${DIR}/T2DegStop_375_305.root ${DIR}/T2DegStop_400_330.root ${DIR}/T2DegStop_425_355.root ${DIR}/T2DegStop_450_380.root ${DIR}/T2DegStop_475_405.root ${DIR}/T2DegStop_500_430.root ${DIR}/T2DegStop_525_455.root ${DIR}/T2DegStop_550_480.root ${DIR}/T2DegStop_575_505.root ${DIR}/T2DegStop_600_530.root ${DIR}/T2DegStop_625_555.root ${DIR}/T2DegStop_650_580.root ${DIR}/T2DegStop_675_605.root ${DIR}/T2DegStop_700_630.root ${DIR}/T2DegStop_725_655.root ${DIR}/T2DegStop_750_680.root ${DIR}/T2DegStop_775_705.root ${DIR}/T2DegStop_800_730.root
  hadd -f ${DIR}/T2DegStop_deltaM80.root ${DIR}/T2DegStop_250_170.root ${DIR}/T2DegStop_275_195.root ${DIR}/T2DegStop_300_220.root ${DIR}/T2DegStop_325_245.root ${DIR}/T2DegStop_350_270.root ${DIR}/T2DegStop_375_295.root ${DIR}/T2DegStop_400_320.root ${DIR}/T2DegStop_425_345.root ${DIR}/T2DegStop_450_370.root ${DIR}/T2DegStop_475_395.root ${DIR}/T2DegStop_500_420.root ${DIR}/T2DegStop_525_445.root ${DIR}/T2DegStop_550_470.root ${DIR}/T2DegStop_575_495.root ${DIR}/T2DegStop_600_520.root ${DIR}/T2DegStop_625_545.root ${DIR}/T2DegStop_650_570.root ${DIR}/T2DegStop_675_595.root ${DIR}/T2DegStop_700_620.root ${DIR}/T2DegStop_725_645.root ${DIR}/T2DegStop_750_670.root ${DIR}/T2DegStop_775_695.root ${DIR}/T2DegStop_800_720.root

  hadd -f ${DIR}/Background_TTbar.root   ${DIR}/TTJets.root    ${DIR}/Wjets_100to200.root ${DIR}/Wjets_200to400.root ${DIR}/Wjets_400to600.root ${DIR}/Wjets_600to800.root ${DIR}/Wjets_800to1200.root ${DIR}/Wjets_1200to2500.root ${DIR}/Wjets_2500toInf.root
  hadd -f ${DIR}/Background_TTbarLO.root ${DIR}/TTJets_LO.root ${DIR}/Wjets_100to200.root ${DIR}/Wjets_200to400.root ${DIR}/Wjets_400to600.root ${DIR}/Wjets_600to800.root ${DIR}/Wjets_800to1200.root ${DIR}/Wjets_1200to2500.root ${DIR}/Wjets_2500toInf.root
  hadd -f ${DIR}/Background_TT_pow.root  ${DIR}/TT_pow.root    ${DIR}/Wjets_100to200.root ${DIR}/Wjets_200to400.root ${DIR}/Wjets_400to600.root ${DIR}/Wjets_600to800.root ${DIR}/Wjets_800to1200.root ${DIR}/Wjets_1200to2500.root ${DIR}/Wjets_2500toInf.root
  hadd -f ${DIR}/Background_TTLep.root   ${DIR}/TTJets_DiLepton.root ${DIR}/TTJets_SingleLeptonFromT.root ${DIR}/TTJets_SingleLeptonFromTbar.root    ${DIR}/Wjets_100to200.root ${DIR}/Wjets_200to400.root ${DIR}/Wjets_400to600.root ${DIR}/Wjets_600to800.root ${DIR}/Wjets_800to1200.root ${DIR}/Wjets_1200to2500.root ${DIR}/Wjets_2500toInf.root

  hadd -f ${DIR}/Background_TTbar_Zinv.root   ${DIR}/Background_TTbar.root   ${DIR}/ZJetsToNuNu_HT100to200.root ${DIR}/ZJetsToNuNu_HT200to400.root ${DIR}/ZJetsToNuNu_HT400to600.root ${DIR}/ZJetsToNuNu_HT600to800.root ${DIR}/ZJetsToNuNu_HT800to1200.root ${DIR}/ZJetsToNuNu_HT1200to2500.root ${DIR}/ZJetsToNuNu_HT2500toInf.root
  hadd -f ${DIR}/Background_TTbarLO_Zinv.root ${DIR}/Background_TTbarLO.root ${DIR}/ZJetsToNuNu_HT100to200.root ${DIR}/ZJetsToNuNu_HT200to400.root ${DIR}/ZJetsToNuNu_HT400to600.root ${DIR}/ZJetsToNuNu_HT600to800.root ${DIR}/ZJetsToNuNu_HT800to1200.root ${DIR}/ZJetsToNuNu_HT1200to2500.root ${DIR}/ZJetsToNuNu_HT2500toInf.root
  hadd -f ${DIR}/Background_TT_pow_Zinv.root  ${DIR}/Background_TT_pow.root  ${DIR}/ZJetsToNuNu_HT100to200.root ${DIR}/ZJetsToNuNu_HT200to400.root ${DIR}/ZJetsToNuNu_HT400to600.root ${DIR}/ZJetsToNuNu_HT600to800.root ${DIR}/ZJetsToNuNu_HT800to1200.root ${DIR}/ZJetsToNuNu_HT1200to2500.root ${DIR}/ZJetsToNuNu_HT2500toInf.root
  hadd -f ${DIR}/Background_TTLep_Zinv.root   ${DIR}/Background_TTLep.root   ${DIR}/ZJetsToNuNu_HT100to200.root ${DIR}/ZJetsToNuNu_HT200to400.root ${DIR}/ZJetsToNuNu_HT400to600.root ${DIR}/ZJetsToNuNu_HT600to800.root ${DIR}/ZJetsToNuNu_HT800to1200.root ${DIR}/ZJetsToNuNu_HT1200to2500.root ${DIR}/ZJetsToNuNu_HT2500toInf.root
#done