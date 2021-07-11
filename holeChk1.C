{
  // plot tg_th vs row for each column
  // May 2021.

#include <string.h>
#include <vector>
  
  FILE *fd;
  fd = fopen("holes.dat", "r");

  Int_t i;
  Int_t NCOL=15;
  vector<TH2F*> hcol;
  char cname[80],ctitle[80];
  
  char strin[80];

  if (fd == NULL) {
    cout << "missing input file"<<endl;
    exit;
  }

  for (i=0; i<NCOL; i++) {
    sprintf(cname,"hcol%d",i);
    sprintf(ctitle,"Column %d tg_th vs row",i);
    hcol.push_back(new TH2F(cname,ctitle,100,-1,12,100,-0.06,0.06));
  }
    

  int row,col;
  float tgth,tgph;

  float minth,minph,maxth,maxph;
  minth = 9999;
  maxth = -9999;
  minph = 9999;
  maxph = -9999;

  
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

    if(istrl) {
      if (col>=0 && col<NCOL) {
	 hcol[col]->Fill(row,tgth);
         hcol[col]->Fill(10,tgph);
      }
    }

   }

   cout << "min,max "<<minth<<"  "<<maxth<<"  "<<minph<<"  "<<maxph<<endl;


}




