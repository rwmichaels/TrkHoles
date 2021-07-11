{
  // plot sieve slit holes from the "csv" files produced by Siyu
  // May 2021.

#include <string.h>
  
  FILE *fd;
  fd = fopen("holes.dat", "r");

  char strin[80];

  if (fd == NULL) {
    cout << "missing input file"<<endl;
    exit;
  }


  int row,col;
  float tgth,tgph;

  float minth,minph,maxth,maxph;
  minth = 9999;
  maxth = -9999;
  minph = 9999;
  maxph = -9999;

  TH2F *Pthph = new TH2F("Pthph","tg_th vs tg_ph",100,-0.030,0.030,100,-0.050,0.050);

  
   while (fgets(strin,80,fd)) {

    cout << "strin "<<strin<<endl;
    Int_t istrl = 0;
    if( strstr(strin,"x,y")!=NULL) istrl=1;
    
    sscanf(strin,"x,y =  %d %d %f %f ",&row,&col,&tgth,&tgph);

    cout << "row "<<row<<"  col "<<col<<"   tgth "<<tgth<<"   tgph "<<tgph<<endl;

    if(tgth < minth) minth = tgth;
    if(tgth > maxth) maxth = tgth;
    if(tgph < minph) minph = tgph;
    if(tgph > maxph) maxph = tgph;

    if(istrl) Pthph->Fill(tgph,tgth);

   }

   cout << "min,max "<<minth<<"  "<<maxth<<"  "<<minph<<"  "<<maxph<<endl;

   Pthph->Draw("SB");

}




