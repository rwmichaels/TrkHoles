{
  // plot tg_th vs col for each row
  // May 2021.

#include <string.h>
#include <vector>
  
  FILE *fd;
  fd = fopen("holes.dat", "r");

  Int_t i;
  Int_t NROW=15;
  vector<TH2F*> hrow;
  char cname[80],ctitle[80];
  
  char strin[80];

  if (fd == NULL) {
    cout << "missing input file"<<endl;
    exit;
  }

  for (i=0; i<NROW; i++) {
    sprintf(cname,"hrow%d",i);
    sprintf(ctitle,"Row %d tg_ph vs col",i);
    hrow.push_back(new TH2F(cname,ctitle,20,-3,12,40,-0.06,0.06));
  }
    

  int row,col;
  float tgth,tgph;

  float minth,minph,maxth,maxph;
  minth = 9999;
  maxth = -9999;
  minph = 9999;
  maxph = -9999;
  int mincol,minrow,maxcol,maxrow;
  mincol = 9999;
  maxcol = -9999;
  minrow = 9999;
  maxrow = -9999;
  
  
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
    if(col < mincol) mincol = col;
    if(col > maxcol) maxcol = col;
    if(row < minrow) minrow = row;
    if(row > maxrow) maxrow = row;

    
    
    if(istrl) {
      if (row>=0 && row<NROW) {
	hrow[row]->Fill(col,tgph);
        hrow[row]->Fill(-1,tgth);
      }
    }

   }

   cout << "angles "<<endl;
   cout << "min,max "<<minth<<"  "<<maxth<<"  "<<minph<<"  "<<maxph<<endl;
   cout << "columns, rows "<<endl;
   cout << "min,max "<<mincol<<"  "<<maxcol<<"  "<<minrow<<"  "<<maxrow<<endl;


}




