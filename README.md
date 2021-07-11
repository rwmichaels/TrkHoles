Macros and files to find track residuals.  These are then
input to HrsTrkCorr.

R. Michaels, July 2021

TrkHoles.C
    main macro to find residuals
inputs:
   holes.dat is the location of sieve slit holes; it's a link
   holes.dat -> ./holefiles/holes2240.dat
   Afile.root is a root file from a sieve slit run
   AfileL.root -> ./rootfiles/prexLHRS_2240_siyu.root
These root files are on ifarm
ifarm:/w/halla-scifs17exp/parity/disk1/bob/trkcorr_rootfiles

To run the TrkHoles.C script, see the appendix

holeChk*.C
   various checks of the holes files

rcHoles.C
   generate tracks randomly, find holes (practice)

plot_holes.C
   plot the holes in holes.dat


Appendix:

How to run the script TrkHoles.C script

  * control Which_Spectrometer variable.
  * make the link for AfileL.root or AfileR.root, example
  ln -s  ./rootfiles/prexLHRS_2239_siyu.root AfileL.root
  * make the linke for holes.dat, example.
  ln -s ./holefiles/holes2239.dat holes.dat
  
root .x TrkHoles.C

// Some global checking histograms are available.
root [3] hrad->Draw()   
root [4] hthdiff->Draw()
root [5] hphdiff->Draw()
root [6] hf1->Draw("box")
root [7] hf0->Draw("box")

// Look at all the residual histograms by hand
root [18] thres11_4->Draw()
root [19] phres11_4->Draw()
root [20] thres10_1->Draw()
root [21] phres10_1->Draw()
root [22] thres10_2->Draw()
root [23] phres10_2->Draw()
root [24] thres10_3->Draw()
root [25] phres10_3->Draw()
root [26] thres10_4->Draw()
root [27] phres10_4->Draw()
root [28] thres9_1->Draw()
root [29] phres9_1->Draw()
root [30] thres9_2->Draw()
root [31] phres9_2->Draw()

The results of the residuals go into these files for use
by HrsTrkCorr
   ~/trkcorr/holefiles/resid*
example:
   resid_LeftHRS_0.dat

Sieve Slit Runs
  Runs taken with X = 0 and X at off-beam locations

  Runs ..... HRS ....... X ...... Y

  2239 ..... Left ...... 3.8 ... -0.5

  2240 ..... Left ..... -0.2 ... -0.5

  2241 ..... Left ..... -3.2 ... -0.5

  21363 .... Right .... 3.8 .... -0.5

  21364 .... Right .... -0.2 ... -0.5

  21365 .... Right .... -3.2 ... -0.5

