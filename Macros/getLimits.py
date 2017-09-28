import os,subprocess,ROOT
import pickle
import re
import time
import shutil

def getNJobs():
  cmd = "qstat | wc -l"
  p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  out, err = p.communicate()

  return int(out)

def assure_path_exists(path):
  dir = os.path.dirname(path)
  if not os.path.exists(dir):
    os.makedirs(dir)

if __name__ == "__main__":
  import argparse

  parser = argparse.ArgumentParser(description='Process the command line options')
  parser.add_argument('-i', '--inputDirectory', required=True, help='Name of the input directory')
  parser.add_argument('-o', '--outputDirectory', required=True, help='Base name of the output directory for each DM')
  parser.add_argument('-d', '--dryRun', action='store_true', help='Do a dry run (i.e. do not actually run the potentially dangerous commands but print them to the screen)')
  parser.add_argument('-u', '--unblind', action='store_true', help='Whether the results have been unblinded or not')

  args = parser.parse_args()

  inputDirectory = args.inputDirectory
  if not (os.path.exists(inputDirectory) and os.path.isdir(inputDirectory)):
    parser.error('The given input directory does not exist or is not a directory')

  if not args.dryRun:
    print "You did not enable dry run. You are on your own!"

  baseDirectory = os.path.realpath(os.getcwd())
  inputDirectory = os.path.realpath(inputDirectory)
  outputDirectory = args.outputDirectory
  assure_path_exists(outputDirectory)

  for deltaM in (10, 20, 30, 40, 50, 60, 70, 80):
    for stopM in (250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775, 800):
      neutM = stopM - deltaM
      datacardName = str(stopM) + "_" + str(neutM) + ".txt"

      assure_path_exists(outputDirectory + "/" + str(stopM) + "_" + str(neutM) + "/")

      cmd = "cp " + inputDirectory + "/" + datacardName + " " + outputDirectory + "/" + str(stopM) + "_" + str(neutM) + "/"
      print cmd
      p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
      out, err = p.communicate()

      job = outputDirectory + "/" + str(stopM) + "_" + str(neutM) + "/job_" + str(stopM) + "_" + str(neutM) + ".sh"
      with open(job, 'w') as thisScript:
        thisScript.write("#!/bin/bash\n\n")

        thisScript.write("alias cmsenv='eval `scramv1 runtime -sh`'\n\n")

        thisScript.write("cd /exper-sw/cmst3/cmssw/users/cbeiraod/\n")
        thisScript.write(". setup.sh\n\n")

        thisScript.write("cd $CMSSW_BASE/src/\n")
        thisScript.write("eval `scramv1 runtime -sh`\n\n")

        thisScript.write("cd " + outputDirectory + "/" + str(stopM) + "_" + str(neutM) + "\n\n")

        # First get the limits without fitting to data, the a-priori limits
        # Should be used before unblinding
        thisScript.write("combine -M AsymptoticLimits --noFitAsimov -n APriori")
        thisScript.write(" " + datacardName)
        thisScript.write(" > aPriori.txt\n")

        thisScript.write("\n")

        # Then generate a background only asimov toy and perform a maximum likelihood fit
        # The objective is to take a look at the pulls of the nuisance parameters and identify possible problems
        thisScript.write("combine -M FitDiagnostics --forceRecreateNLL -t -1")
        thisScript.write(" -n BOnly")
        thisScript.write(" --expectSignal 0 " + datacardName)
        thisScript.write(" > Bonly.txt\n")

        # Get the pulls of the nuisance parameters
        thisScript.write("python $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py")
        thisScript.write(" -a fitDiagnosticsBOnly.root")
        thisScript.write(" -g plots_Bonly.root")
        thisScript.write(" > Bonly_pulls.txt\n")

        thisScript.write("\n")

        # Repeat for B+S
        thisScript.write("combine -M FitDiagnostics --forceRecreateNLL -t -1")
        thisScript.write(" -n BpS")
        thisScript.write(" --expectSignal 1 " + datacardName)
        thisScript.write(" > BpS.txt\n")

        thisScript.write("python $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py")
        thisScript.write(" -a fitDiagnosticsBpS.root")
        thisScript.write(" -g plots_BpS.root")
        thisScript.write(" > BpS_pulls.txt\n")

        thisScript.write("\n")

        # Run the full CLs method
        # We need to run independently for each quantile
        thisScript.write("combine -M HybridNew --LHCmode LHC-limits -t -1")
        thisScript.write(" --expectedFromGrid 0.5")
        thisScript.write(" -n APriori")
        thisScript.write(" " + datacardName)
        thisScript.write(" > aPrioriFullCLs0500.txt\n")

        thisScript.write("combine -M HybridNew --LHCmode LHC-limits -t -1")
        thisScript.write(" --expectedFromGrid 0.16")
        thisScript.write(" -n APriori")
        thisScript.write(" " + datacardName)
        thisScript.write(" > aPrioriFullCLs0160.txt\n")

        thisScript.write("combine -M HybridNew --LHCmode LHC-limits -t -1")
        thisScript.write(" --expectedFromGrid 0.84")
        thisScript.write(" -n APriori")
        thisScript.write(" " + datacardName)
        thisScript.write(" > aPrioriFullCLs0840.txt\n")

        thisScript.write("combine -M HybridNew --LHCmode LHC-limits -t -1")
        thisScript.write(" --expectedFromGrid 0.975")
        thisScript.write(" -n APriori")
        thisScript.write(" " + datacardName)
        thisScript.write(" > aPrioriFullCLs0975.txt\n")

        thisScript.write("combine -M HybridNew --LHCmode LHC-limits -t -1")
        thisScript.write(" --expectedFromGrid 0.025")
        thisScript.write(" -n APriori")
        thisScript.write(" " + datacardName)
        thisScript.write(" > aPrioriFullCLs0025.txt\n")

        thisScript.write("hadd higgsCombineAPriori.HybridNew.root higgsCombineAPriori.HybridNew.mH120*.root\n")

        thisScript.write("\n")

        # Then get the a-posteriori limits, can only be retrieved after unblinding
        if args.unblind:
          thisScript.write("\n")
          thisScript.write("\n")
          thisScript.write("combine -M AsymptoticLimits -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosteriori.txt\n")

          thisScript.write("combine -M HybridNew --LHCmode LHC-limits")
          thisScript.write(" --expectedFromGrid 0.5")
          thisScript.write(" -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosterioriFullCLs0500.txt\n")

          thisScript.write("combine -M HybridNew --LHCmode LHC-limits")
          thisScript.write(" --expectedFromGrid 0.84")
          thisScript.write(" -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosterioriFullCLs0840.txt\n")

          thisScript.write("combine -M HybridNew --LHCmode LHC-limits")
          thisScript.write(" --expectedFromGrid 0.16")
          thisScript.write(" -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosterioriFullCLs0160.txt\n")

          thisScript.write("combine -M HybridNew --LHCmode LHC-limits")
          thisScript.write(" --expectedFromGrid 0.975")
          thisScript.write(" -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosterioriFullCLs0975.txt\n")

          thisScript.write("combine -M HybridNew --LHCmode LHC-limits")
          thisScript.write(" --expectedFromGrid 0.025")
          thisScript.write(" -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosterioriFullCLs0025.txt\n")

          thisScript.write("combine -M HybridNew --LHCmode LHC-limits")
          thisScript.write(" -n APosteriori")
          thisScript.write(" " + datacardName)
          thisScript.write(" > aPosterioriFullCLs.txt\n")

          thisScript.write("hadd higgsCombineAPosteriori.HybridNew.root higgsCombineAPosteriori.HybridNew.mH120*.root\n")

        mode = os.fstat(thisScript.fileno()).st_mode
        mode |= 0o111
        os.fchmod(thisScript.fileno(), mode & 0o7777)

      cmd = "qsub " + job + " -e " + job + ".e$JOB_ID -o " + job + ".o$JOB_ID"
      print cmd
      if not args.dryRun:
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()

















