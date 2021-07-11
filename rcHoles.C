{
  // find rows and columns
  // May 2021.

#include <string.h>
#include <vector>
#include "TRandom.h"
  
  FILE *fd;
  fd = fopen("holes.dat", "r");

  Int_t NEVENTS = 2000;
  Int_t icol,jrow,idx,idxm;
  Int_t NCOL=15;  // max number; actually 10 (sometimes 9)
  Int_t NROW=10;  // rows
  Float_t *tgth_hole, *tgph_hole;
  Float_t thdiff,phdiff,thmin,phmin;
  Int_t *colfind,*holefind;
  colfind = new Int_t[NCOL];
  holefind = new Int_t[NCOL*NROW];
  tgth_hole = new Float_t[NCOL*NROW];  
  tgph_hole = new Float_t[NCOL*NROW];

  TH2F *hf0 = new TH2F("hf0","NOT found holes ",100,-0.052,0.052,100,-0.052,0.052);
  TH2F *hf1 = new TH2F("hf1","Found holes ",100,-0.052,0.052,100,-0.052,0.052);
  

  for (icol=0; icol<NCOL; icol++) {
    colfind[icol]=0;  // 0 not found, +1 found
    for (jrow=0; jrow<NROW; jrow++) {
      holefind[jrow]=0;
      idx = icol*NROW + jrow;
      tgth_hole[idx] = 1000+1000*idx; // initial value (= not found)
      tgph_hole[idx] = 1000+1000*idx;
    }
  }
  
  char strin[80];

  if (fd == NULL) {
    cout << "missing input file"<<endl;
    exit;
  }

  int row,col;
  float tgth,tgph;

  
   while (fgets(strin,80,fd)) {

    cout << "strin "<<strin<<endl;
    Int_t istrl = 0;
    if( strstr(strin,"x,y")!=NULL) istrl=1;
    
    sscanf(strin,"x,y =  %d %d %f %f ",&row,&col,&tgth,&tgph);

    cout << "row "<<row<<"  col "<<col<<"   tgth "<<tgth<<"   tgph "<<tgph<<endl;
    if(istrl) {
      if (col>=0 && col<NCOL) {
	colfind[col] = 1;
	if (row>=0 && row<NROW) {
	  idx = col*NROW + row;
          holefind[idx] = 1;
	  tgth_hole[idx] = tgth;
          tgph_hole[idx] = tgph;
	}
      }
    }

   }

   Int_t nholes=0;

   for (icol=0; icol<NCOL; icol++) {
     if (colfind[icol]==1) {
       cout << "\nFOUND COLUUMN "<<icol<<endl;
       for (jrow=0; jrow<NROW; jrow++) {
           idx = icol*NROW + jrow;
	   tgth = tgth_hole[idx];
           tgph = tgph_hole[idx];	  
           if(holefind[idx]==1) {
	     cout << "  row "<<jrow<<"   tgth = "<<tgth<<"    tgph "<<tgph<<endl;
	     nholes++;
	   }
       }
     }
   }

   cout << "Number of holes found "<<nholes<<endl;


// test the holes
   TRandom *rnd = new TRandom();
   
   for (Int_t ievt=0; ievt<NEVENTS; ievt++) {
// fake events
     Double_t rnd_th = rnd->Uniform(-0.05,0.05);
     Double_t rnd_ph = rnd->Uniform(-0.05,0.05);
     cout << "event "<<ievt<<"  val "<<rnd_th<<"  "<<rnd_ph<<endl;
     // find column

    thmin=9999;
    phmin=9999;
    idxm=-1;
    for (icol=0; icol<NCOL; icol++) {
      if (colfind[icol]==1) {
        for (jrow=0; jrow<NROW; jrow++) {
           idx = icol*NROW + jrow;
           if (holefind[idx]) {
	     thdiff = rnd_th - tgth_hole[idx];
	     phdiff = rnd_ph - tgph_hole[idx];
	     if (thdiff >= 0&&phdiff >= 0&&thdiff<thmin&&phdiff<phmin) {
	       thmin = thdiff;
	       phmin = phdiff;
               idxm = idx;
	     }
	   }
	}
      }
    }

    cout << "matched hole "<<idxm<<"  "<<tgth_hole[idxm]<<"   "<<tgph_hole[idxm]<<"   "<<rnd_th<<"  "<<rnd_ph<<endl;

    if (idxm > 0) {
       hf1->Fill(rnd_ph,rnd_th);
    } else {
       hf0->Fill(rnd_ph,rnd_th);
    }
    
   }  // event loop
   
} // end of macro






