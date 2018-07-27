#!/usr/bin/env bash

# Modified from N. Smith, U. Wisconsin
# https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2#Efficiencies_and_scale_factors
wget http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/RECO/passingRECO/egammaEffi.txt_EGM2D.root -O ../data/moriond17ElectronRecoSF.root
wget http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/EleID/passingMedium80X/egammaEffi.txt_EGM2D.root -O ../data/moriond17ElectronMediumSF.root
wget http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/EleID/passingTight80X/egammaEffi.txt_EGM2D.root -O ../data/moriond17ElectronTightSF.root
wget http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/EleID/passingMVA80Xwp80/egammaEffi.txt_EGM2D.root -O ../data/moriond17ElectronMVA80SF.root
wget http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/EleID/passingMVA80Xwp90/egammaEffi.txt_EGM2D.root -O ../data/moriond17ElectronMVA90SF.root

# Getting things from twiki is hard but possible
# See http://linux.web.cern.ch/linux/docs/cernssocookie.shtml
if which cern-get-sso-cookie &>/dev/null; then
  # https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults
  env -i KRB5CCNAME="$KRB5CCNAME" cern-get-sso-cookie --krb -r -u https://gaperrin.web.cern.ch/gaperrin/tnp -o ~/private/ssocookie.txt
  wget --load-cookies ~/private/ssocookie.txt https://gaperrin.web.cern.ch/gaperrin/tnp/TnP2016/2016Data_Moriond2017_6_12_16/JSON/RunBCDEF/EfficienciesAndSF_BCDEF.root -O ../data/moriond17MuonID_BCDEF.root
  wget --load-cookies ~/private/ssocookie.txt https://gaperrin.web.cern.ch/gaperrin/tnp/TnP2016/2016Data_Moriond2017_6_12_16/JSON/RunGH/EfficienciesAndSF_GH.root -O ../data/moriond17MuonID_GH.root
  env -i KRB5CCNAME="$KRB5CCNAME" cern-get-sso-cookie --krb -r -u https://calderon.web.cern.ch/calderon/MuonPOG/2016dataReRecoEfficiencies/isolation/ -o ~/private/ssocookie.txt
  wget --load-cookies ~/private/ssocookie.txt https://calderon.web.cern.ch/calderon/MuonPOG/2016dataReRecoEfficiencies/isolation/EfficienciesAndSF_BCDEF.root -O ../data/moriond17MuonIso_BCDEF.root
  wget --load-cookies ~/private/ssocookie.txt https://calderon.web.cern.ch/calderon/MuonPOG/2016dataReRecoEfficiencies/isolation/EfficienciesAndSF_GH.root -O ../data/moriond17MuonIso_GH.root

  # https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco#Supported_Algorithms_and_Operati
  env -i KRB5CCNAME="$KRB5CCNAME" cern-get-sso-cookie --krb -r -u https://twiki.cern.ch/twiki/bin/view/CMS/WebHome -o ~/private/ssocookie.txt
  wget --load-cookies ~/private/ssocookie.txt https://twiki.cern.ch/twiki/pub/CMS/BtagRecommendation80XReReco/CSVv2_Moriond17_B_H.csv -O ../data/CSVv2_Moriond17_B_H.cs
else
  echo -e "\033[33mWARNING: You will have to download some files yourself, sorry\033[0m"
fi

# Pileup from https://gitlab.cern.ch/ncsmith/PileupWeights
#git clone https://:@gitlab.cern.ch:8443/ncsmith/PileupWeights.git
#pushd PileupWeights
## This needs pileupCalc.py and takes a while
#cmsenv
#. getDataDistribution.sh
#./calculatePileupCorrections.py
#popd
