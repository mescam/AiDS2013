BEGIN {
  FS=";"
  n[1]=500; n[2]=1000; n[3]=2500; n[4]=5000; n[5]=10000; n[6]=20000; n[7]=50000; n[8]=75000; n[9]=100000; n[10]=150000;
  f[0]="Insertion Sort"; f[1] = "Shell Sort"; f[2]="Selection Sort"; f[3]="Heap Sort";
  d[1]="Random"; d[2]="Ascending"; d[3]="Descending"; d[4]="Constant"; d[5]="V-Shaped";
}

{ 
  #in file: n, set type, func, time
  #tab: [func, set type, n] = time
  tab[$3, $2, $1]=$4; 
}   


END {
  for(i=0;i<4;i++){ #for each func
    print f[i];
    print "-", d[1], d[2], d[3], d[4], d[5];
    for(j=1;j<=10;j++) { #for each n
      print n[j], tab[i, 1, n[j]], tab[i, 2, n[j]], tab[i, 3, n[j]], tab[i, 4, n[j]], tab[i, 5, n[j]]; #DRY, but later.
    }
    print ""; print ""; print "";
  }
}
# vim: set ts=2 sw=2 tw=0 et :
