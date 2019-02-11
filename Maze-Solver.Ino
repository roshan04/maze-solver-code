solving maze -shortest path #include<EEPROM.h> #define lp 8 #define ln 12 #define el 6 #define rp 4 #define rn 7 #define er 5 #define ers A0 #define rs A1 #define cs A2 #define ls A3 #define els A4 #define switch1 2 //#define switch2 1 #define switch0 10 #define led 13 //int flag = 0; //int count=1,s=0; //char h; int m=0,guide,signals,a[100],i=0; void shortestpath(int); void setup() { pinMode(lp,OUTPUT); pinMode(ln,OUTPUT); pinMode(el,OUTPUT); pinMode(rp,OUTPUT); pinMode(rn,OUTPUT); pinMode(er,OUTPUT); pinMode(ers,INPUT); pinMode(rs,INPUT); pinMode(cs,INPUT); pinMode(els,INPUT); pinMode(ls,INPUT); digitalWrite(er,HIGH); digitalWrite(el,HIGH); pinMode(led,OUTPUT); digitalWrite(led,LOW); // pinMode(switch0,INPUT); pinMode(switch1,INPUT); digitalWrite(switch1,LOW); //pinMode(switch2,INPUT); } void motor(int r,int l) {

switch(r) { case 0: digitalWrite(rp,LOW); digitalWrite(rn,LOW); break; case 1: digitalWrite(rp,HIGH);

      digitalWrite(rn,LOW);
      break;
case 2: digitalWrite(rp,LOW); digitalWrite(rn,HIGH); break; } switch(l) {

case 0: digitalWrite(lp,LOW); digitalWrite(ln,LOW); break; case 1: digitalWrite(lp,HIGH); digitalWrite(ln,LOW); break; case 2: digitalWrite(lp,LOW); digitalWrite(ln,HIGH); break; } } void loop() { signals=digitalRead(switch1); if(signals==1) { if(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1) { motor(1,1); } else if(digitalRead(els)==0&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==0) { motor(0,0);//stop; shortestpath(i); digitalWrite(er,LOW); digitalWrite(el,LOW); digitalWrite(led,HIGH); delay(2000); digitalWrite(led,LOW); delay(2000); while(1) { motor(0,0); } } else if(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==0) { a[i]=2;i++;//straight; while(!((digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)||(digitalRead(els)==1&&digitalRead(ls)==1&&digitalRead(cs)==1&&digitalRead(rs)==1&&digitalRead(ers)==1))) { motor(1,1); } i--; a[i]=3;i++;//right; if(digitalRead(els)==0&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==0) { while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { motor(0,1); }
} } else if(digitalRead(els)==0&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1) { a[i]=1;i++;//left; while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { if(digitalRead(els)==0&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==0) { break; } else { motor(1,0); } } } else if(digitalRead(els)==1&&digitalRead(ls)==1&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1) { motor(0,1); } else if(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==1&&digitalRead(ers)==1) { motor(1,0); } else if(digitalRead(els)==1&&digitalRead(ls)==1&&digitalRead(cs)==1&&digitalRead(rs)==1&&digitalRead(ers)==1) { a[i]=4;i++;//backward; while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) {
motor(2,1); } } } else if(signals==0) { while(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1) {
motor(1,1); } guide=EEPROM.read(m);m++; while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { if(guide==1) { while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { motor(1,0);
} } else if(guide==2) { while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { motor(1,1); } } else if(guide==3) { while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { motor(0,1); } } else if(guide==4) { while(!(digitalRead(els)==1&&digitalRead(ls)==0&&digitalRead(cs)==0&&digitalRead(rs)==0&&digitalRead(ers)==1)) { motor(2,1); } } else if(guide==0) { while(1) { motor(0,0); } } } } } void shortestpath(int k) { int m,n,o; for(int j=0;j<k;j++) { if(a[j]==4) { m=a[j-1]; n=a[j]; o=a[j+1]; if(m==1&&n==4&&o==3) { a[j-1]=4; } if(m==1&&n==4&&o==2) { a[j-1]=3; }

     if(m==3&&n==4&&o==1)
     {
      a[j-1]=4;
     }
     if(m==2&&n==4&&o==1)
     {
      a[j-1]=3;
     } 
     if(m==2&&n==4&&o==2)
     {
      a[j-1]=4;
     }
     if(m=1&&n==4&&o==1)
     {
      a[j-1]=2;
     } 
  for(int l=j;l<k;l++)
  {
    a[l]=a[l+2]; 
  }
      k=k-1;
      }
 }
 for(int q=0;q<k;q++)
 {
  EEPROM.write(q,a[q]); 
 }
  }
