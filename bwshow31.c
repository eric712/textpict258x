// bwshow31.txt is alpha test version of bwshow31.c
// top
// stuck at line
 extern int read(int rrfh,char* rrfa,int rrlen);
// rem extern int write(int wxh,char* wwfa,int wwlen);
 extern int ioctl(int,int,void*);
 #define ctcgets 0x5401
 #define ctcsets 0x5402
 #define icannonand 0xFFFFFFFD
 #define icannonor 0x00000002
 #define echoand 0xFFFFFFF7
 #define echoor 0x00000008
 #define istdin 0
// rem #define istdout 1
// ---------------------------
 #include <stdio.h>
// #include <locale.h>
 #include <stdlib.h>
 typedef FILE* HANDLE;
// typedef unsigned short WCHAR;
 typedef int WCHAR;
 typedef struct
 {
 short prem2;
 short constmb;
 int skip02;
 int skip06;
 int skip10;
 int skip14;
// 0018 bbiwidth     0022 bbiheight    26 bbiplanes    28 bbibitcount
 int bbiwidth;
 int bbiheight;
 short bbiplanes;
 short bbibitcount;
// 0030 needzeroc
 int needzeroc;
 int skip34;
 int skip38;
 int skip42;
 int bbiclrused;
 int skip50;
// -- 54 colortable size == 8 for bbibitcount == 1
 int hblackcolor;
 int hwhitecolor;
 } abumphdr;
 abumphdr rua;
 int ralinei[1024];
 int ralinej[1024];
 char revtab13[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x0E,0x0F,0x1C,0x00,0x00,0x1C,0x00,0x00,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,
                     0x39,0x82,0xA8,0x84,0x85,0x86,0x88,0x28,
                     0x8A,0x8B,0x89,0x8D,0x33,0x0C,0x34,0x35,
                     0x0B,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                     0x09,0x0A,0xA7,0x27,0xB3,0x0d,0xB4,0xB5,
                     0x83,0x9E,0xB0,0xAE,0xA0,0x92,0xA1,0xA2,
                     0xA3,0x97,0xA4,0xA5,0xA6,0xB2,0xB1,0x98,
                     0x99,0x90,0x93,0x9F,0x94,0x96,0xAF,0x91,
                     0xAD,0x95,0xAC,0x1A,0x2B,0x1B,0x87,0x8C,
                     0x29,0x1E,0x30,0x2E,0x20,0x12,0x21,0x22,
                     0x23,0x17,0x24,0x25,0x26,0x32,0x31,0x18,
                     0x19,0x10,0x13,0x1F,0x14,0x16,0x2F,0x11,
                     0x2D,0x15,0x2C,0x9A,0xAB,0x9B,0xA9,0x00 };
 char rfn[]="test.bmp\0";
 char oel[]={0x0d,0x0a};
 char* aline=" announcement 01234567890123456789 ";
// WCHAR wist[]={0x0020,0x259d,0x2598,0x2580,0x2597,0x2590,0x259a,0x259c,
//               0x2596,0x259e,0x258c,0x259b,0x2584,0x259f,0x2599,0x2588};
// WCHAR rejwist[]={0x0020,0x259d,0x2598,0x00df,0x2597,0x00de,0x259a,0x0014,
//               0x2596,0x259e,0x00dd,0x00e2,0x00dc,0x259f,0x2599,0x00db};
// WCHAR yist[]={0x0020,0x2580,0x2584,0x2588};
// WCHAR xist[]={0x0020,0x2590,0x258c,0x2588};
// WCHAR oeel[]={0x000d,0x000a};
 WCHAR bigwist[40];
 WCHAR wist[]={0x00000020,0x009d96e2,0x009896e2,0x008096e2,
               0x009796e2,0x009096e2,0x009a96e2,0x009c96e2,
               0x009696e2,0x009e96e2,0x008c96e2,0x009b96e2,
               0x008496e2,0x009f96e2,0x009996e2,0x008896e2};
// ----------
 WCHAR oeel[]={0x0000000d,0x0000000a};
//    tblekey partially converts BIOS key to regular key.
//    subscript is BIOSKEY * 2
 char tblekey[] = { "*027010203040506070809000-0=*8*9"
                    "0q0w0e0r0t0y0u0i0o0p919313*00a0s"
                    "0d0f0g0h0j0k0l0;34*0*0920z0x0c0v"
                    "0b0n0m0,0.0/*0*0*032*0*0*0*0*0*0"
                    "*0*0*0*0*0*0*0AGAHAI*0AK*0AM*0AO"
                    "APAQARAS*0*0*0*0*0*0*0*0*0*0*0*0"
                    "*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0"
                    "*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0"
                    "*0270!0@0#0$0%0^0&0*0(0)0_0+*8*9"
                    "0Q0W0E0R0T0Y0U0I0O0P0{0}13*00A0S"
                    "0D0F0G0H0J0K0L0:34*0*00|0Z0X0C0V"
                    "0B0N0M0<0>0?*0*0*032*0*0*0*0*0*0"
                    "*0*0*0*0*0*0*0AGAHAI*0AK*0AM*0AO"
                    "APAQARAS*0*0*0*0*0*0*0*0*0*0*0*0"
                    "*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0"
                    "*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0" };
// --------------------- 512 bytes
 int getonebit(int onebsub, char* baline)
 {
 int glist[]={128,64,32,16,8,4,2,1};
 int twodsub,tworsub,twobres,twoterm;
 twobres=1;
 tworsub=onebsub & 7;
 twodsub=onebsub >> 3;
 twoterm=((int)(*(baline + twodsub)));
 if((glist[tworsub] & twoterm) == 0)
 {
 twobres=0;
 }
 return twobres;
 }
// -------------
 void numberprn(char* stnuwa,long startsu,
            long width,long basew,long nuhl)
   {
// use alselset(&crz0160[0],
// linenumber)
// for stnuwa when to a numbered line.
      long ctr,numer,nufrac,nurem,nuprod;
      int isneg;
      numer=(long)0;
      isneg=0;
      if(nuhl < 0)isneg=1;
      if(isneg == 1)numer=((long)(0-1))-nuhl;
      if(isneg == 0)numer=nuhl;
      ctr=width-1;
nuwlop:  if(ctr<0)goto nuwbot;
      nufrac=numer/basew;
      goto nuwtwo;
nuwshrink:  nufrac --;
nuwtwo:  nuprod=basew*nufrac;
      nurem=numer-nuprod;
      if(nurem<0)goto nuwshrink;
      numer = nufrac;
      if(isneg == 1)
      {
      nurem=(basew-((long)1))-nurem;
      }
      if(nurem > 9)
       {
       nurem = nurem + 7;
       }
  *(stnuwa+((startsu-1)+ctr))=nurem+'\60';
      ctr --;
      goto nuwlop;
nuwbot:  ctr=0;
      }
// -------------
 int aprten(char* rawol,int wprval)
 {
 char *prloc;
 int prctr,prlnow,prrmid;
 int prres,prlz;
 prlz=48;
 numberprn(rawol,1,10,10,wprval);
 prrmid=9;
 prctr=0;
 while(prctr < 9)
 {
 prlnow = (int)(*(rawol + prctr));
 if((prctr == 0)&&(prlnow == 57))prlz=57;
 if(prlnow != prlz)
 {
 prrmid=prctr;
 prctr=prctr + 11;
 }
 prctr=prctr+1;
 }
 prres=prrmid;
 if((wprval < 0)&&(prrmid >= 1))prres=prrmid-1;
 return prres;
 }
// -----------
 int bprten(char* rawyl,int wyrval)
 {
 int rawbctr,rawbdisp,rawbres,rawbch,rawbhtr;
 char rawcw[10];
 rawbdisp=aprten(rawcw,wyrval);
 rawbres=10-rawbdisp;
 rawbctr=0;
 while(rawbctr < rawbres)
 {
 rawbhtr=rawbctr+rawbdisp;
 rawbch=(int)(*(rawcw + rawbhtr));
 *(rawyl + rawbctr)=(char)rawbch;
 rawbctr=rawbctr+1;
 }
 return rawbres;
 }
// ------------
 void writeline(WCHAR*,int,HANDLE);
 void wrten(char* wtnmode,int wtrval)
 {
 int bprwid,bprctr,bprterm,hprctr;
 char bigcw[14];
 char bigdw[56];
 bprwid=bprten(bigcw,wtrval);
 bprctr=0;
 while(bprctr < bprwid)
 {
 hprctr=bprctr+bprctr;
 hprctr=hprctr+hprctr;
// hprctr=hprctr+4;
 bigdw[hprctr+0]=bigcw[bprctr];
 bigdw[hprctr+1]=(char)0;
 bigdw[hprctr+2]=(char)0;
 bigdw[hprctr+3]=(char)0;
 bprctr=bprctr+1;
 }
 hprctr=hprctr+4;
 if(bprwid < 0)bprwid=0;
 bigdw[hprctr+0]=(char)13;
 bigdw[hprctr+1]=(char)0;
 bigdw[hprctr+2]=(char)0;
 bigdw[hprctr+3]=(char)0;
 bigdw[hprctr+4]=(char)10;
 bigdw[hprctr+5]=(char)0;
 bigdw[hprctr+6]=(char)0;
 bigdw[hprctr+7]=(char)0;
 if(((int)(*(wtnmode+0))) != 78)
 {
 bigdw[hprctr+0]=(char)32;
 bigdw[hprctr+4]=(char)32;
 }
 writeline((int*)bigdw,bprwid+2,stdout);
 }
// ----
 int readnumber(int rnumany,HANDLE rnuhan)
 {
 int readskip4[1];
 char rnnc[80];
 int rnuctr2,rnuprod,rnures,rnnt;
 rnures=0;
 rnuprod=1;
 rnuctr2=0;
 fread(rnnc,rnumany,1,rnuhan);
// rem ReadFile(rnuhan,rnnc,rnumany,readskip4,(char*)0);
 while(rnuctr2 < rnumany)
 {
 rnnt=(int)(*(rnnc + rnuctr2));
 if(rnnt < 0)
 {
 rnnt=rnnt+256;
 }
 rnures=rnures+(rnuprod * rnnt);
 rnuprod=rnuprod*256;
 rnuctr2=rnuctr2+1;
 }
 return rnures;
 }
// ------------
 void readoneline(int rolwid,int* ralinew,int rolbpp,HANDLE rahan)
 {
 char rolbuff[160];
 int rolctr,rolbigwid,roltinywid;
  if(rolbpp == 1)
  {
  rolbigwid=((rolwid + 31)/32)*32;
  roltinywid=rolbigwid >> 3;
  rolctr=0;
   while(rolctr < roltinywid)
   {
   rolbuff[rolctr]=readnumber(1,rahan);
   rolctr=rolctr+1;
   }
  rolctr=0;
   while(rolctr < rolbigwid)
   {
   *(ralinew + rolctr) = getonebit(rolctr,rolbuff);
   rolctr=rolctr+1;
   }
  }
// not return
 }
// ----
 void getwidth(abumphdr *rc,HANDLE hc)
 {
 (*(rc)).prem2 = 0;
 (*(rc)).constmb = readnumber(2,hc);
 (*(rc)).skip02 = readnumber(4,hc);
 (*(rc)).skip06 = readnumber(4,hc);
 (*(rc)).skip10 = readnumber(4,hc);
 (*(rc)).skip14 = readnumber(4,hc);
 (*(rc)).bbiwidth = readnumber(4,hc);
 (*(rc)).bbiheight = readnumber(4,hc);
 (*(rc)).bbiplanes = readnumber(2,hc);
 (*(rc)).bbibitcount = readnumber(2,hc);
 (*(rc)).needzeroc = readnumber(4,hc);
 (*(rc)).skip34 = readnumber(4,hc);
 (*(rc)).skip38 = readnumber(4,hc);
 (*(rc)).skip42 = readnumber(4,hc);
 (*(rc)).bbiclrused = readnumber(4,hc);
 (*(rc)).skip50 = readnumber(4,hc);
 (*(rc)).hblackcolor = readnumber(4,hc);
 (*(rc)).hwhitecolor = readnumber(4,hc);
// 62
// not return
 }
// ---- 117
 void writeline(WCHAR* linw,int wwd,HANDLE wh)
 {
// long iera;
// WCHAR werm;
// char werc[2];
// int ierm;
// char* aierm;
 int wtr;
// iera=(long)(&ierm);
// aierm=(char*)iera;
 int iyrm[1];
 wtr=0;
 while(wtr < wwd)
 {
// ierm=(int)(*(linw + wtr));
 iyrm[0]=(int)(*(linw + wtr));
// werm=(WCHAR)ierm;
// werc[0]= *(aierm+0);
// werc[1]= *(aierm+1);
// fputwc((int)werm,wh);
// fwrite(werc,2,1,wh);
 fwrite((char*)iyrm,4,1,wh);
 wtr=wtr+1;
 }
 }
 void wwrdisp(int* pixes,int* pjxes,int dwid)
 {
 int xdwid,xdctr,xdsel,ydsel,ydwid,ydctr;
 int wdselc=0-11;
 int wrjunk[1];
 HANDLE wdhandle;
 WCHAR obuff[200];
 WCHAR oeol[]={0x0000000d,0x0000000a};
 xdwid=dwid >> 1;
 ydwid=dwid;
// if(xdwid > 78)xdwid=78;
 xdctr=0;
 ydctr=0;
 while(xdctr < ydwid)
 {
 ydsel=0;
 ydsel=ydsel+(2*(*(pixes + (xdctr + 0))))+(1*(*(pixes + (xdctr + 1))));
 ydsel=ydsel+(8*(*(pjxes + (xdctr + 0))))+(4*(*(pjxes + (xdctr + 1))));
 *(obuff + ydctr)=wist[15-ydsel];
 ydctr=ydctr+1;
 xdctr=xdctr+2;
 }
 *(obuff + xdwid)=oeol[0];
 *(obuff + (xdwid+ 1))=oeol[1];
// wdhandle=GetStdHandle(wdselc);
 wdhandle=stdout;
// WriteConsoleW(wdhandle,obuff,xdwid+2,wrjunk,0);
// fwrite(obuff,(xdwid+2)*2,1,wdhandle);
 writeline(obuff,xdwid+2,wdhandle);
 }
// end of wwrdisp
 int getakey()
 {
 int buff680[50];
 char ckess[4];
 int getakess;
 int lookey904;
 lookey904=0;
 getakess=0;
 ioctl(istdin,ctcgets,buff680);
 getakess=buff680[3];
 getakess=getakess & icannonand;
 getakess=getakess & echoand;
 buff680[3]=getakess;
 ioctl(istdin,ctcsets,buff680);
// rem fread(ckess,1,1,stdin);
 read(istdin,ckess,1);
 lookey904=(int)ckess[0];
 ioctl(istdin,ctcgets,buff680);
 getakess=buff680[3];
 getakess=getakess | icannonor;
 getakess=getakess | echoor;
 buff680[3] = getakess;
 ioctl(istdin,ctcsets,buff680);
 getakess = lookey904 & 255;
 return getakess;
 }
// end of getakey
 int getbkey()
 {
 int loolimit896,loopkey852,ctr988,var984,var980;
 int bkess;
 loopkey852=0;
 var984=0;
 ctr988=0;
 loolimit896=1;
getbkoop: loopkey852 = loopkey852 * 256;
 bkess=getakey();
 loopkey852=loopkey852+bkess;
 ctr988=ctr988+1;
 if(ctr988 != 1)goto getbk02;
 if(bkess != 27)goto getbk02;
 loolimit896=3;
getbk02: if(ctr988 != 2)goto getbk03;
 if(bkess != 27)goto getbk03;
 loolimit896=2;
getbk03: if(ctr988 != 3)goto getbk04;
 if(bkess < 48)goto getbk04;
 if(bkess >= 59)goto getbk04;
 loolimit896=4;
getbk04: if(ctr988 >= loolimit896)goto skip1544;
 goto getbkoop;
skip1544: bkess=loopkey852;
 var980=127;
 var984=bkess;
 if(bkess != var980)goto skip1552;
 var984=8;
skip1552: if(bkess != 0x1B1B)goto skip1555;
 var984=27;
skip1555: if(bkess != 0x1B5B44)goto skip1559;
 var984=0x44B;
skip1559: if(bkess != 0x1B5B41)goto skip1563;
 var984=0x448;
skip1563: if(bkess != 0x1B5B42)goto skip1567;
 var984=0x450;
skip1567: if(bkess != 0x1B5B43)goto skip1571;
 var984=0x44D;
skip1571: if(bkess != 0x1B5B337E)goto skip1575;
 var984=0x453;
skip1575: if(bkess != 0x1B5B327E)goto skip1579;
 var984=0x452;
skip1579: if(bkess != 0x1B5B48)goto skip1583;
 var984=0x447;
skip1583: if(bkess != 0x1B5B46)goto skip1587;
 var984=0x44F;
skip1587: if(bkess != 0x1B5B357E)goto skip1591;
 var984=0x449;
skip1591: if(bkess != 0x1B5B367E)goto skip1595;
 var984=0x451;
skip1595: if(bkess != 0x1B5B317E)goto skip1599;
 var984=0x447;
skip1599: if(bkess != 0x1B5B347E)goto skip1603;
 var984=0x44F;
skip1603: if(bkess != 0x1B4F48)goto skip1607;
 var984=0x447;
skip1607: if(bkess != 0x1B4F46)goto skip1611;
 var984=0x44F;
skip1611: bkess = var984;
 return bkess;
 }
// bottom of getbkey
 int getckey()
 {
 int asciikey936,var992;
 int kessc,kessd;
 kessc=0;
 asciikey936=getbkey();
 var992 = asciikey936 & 127;
 kessd=(int)revtab13[var992];
 kessc = kessd & 255;
 if(asciikey936 < 511)goto getckot;
 kessc = asciikey936 & 511;
getckot: var992=0;
 return kessc;
 }
// bottom of getckey()
 int tikey()
 {
 int traw,tsub;
 char tktemp[4];
 traw=getckey();
 tsub=(traw & 255) * 2;
 tktemp[0]=tblekey[tsub+0];
 tktemp[1]=tblekey[tsub+1];
 traw=((int)(tktemp[0])) & 255;
 tsub=((int)(tktemp[1])) & 255;
 traw=traw+(256 * tsub);
 return traw;
 }
// bottom of tikey
 void tckeypar1(char* tcrez)
 {
 int tcshr;
 int tcterm;
 tcshr=tikey();
 tcterm=tcshr & 255;
 *(tcrez + 0)=(char)tcterm;
 tcshr = tcshr >> 8;
 tcterm=tcshr & 255;
 *(tcrez + 1)=(char)tcterm;
 }
 int tchkey()
 {
 int tcktype,tckraw,tckchar;
 char tkbuff[8];
 tckeypar1(tkbuff);
 tcktype=(int)tkbuff[0];
 tckraw=(int)tkbuff[1];
 tckchar=0;
 if(tcktype == 48)tckchar=tckraw;
 if((tcktype >= 49)&&(tcktype <= 57))
 {
 tckchar=((tcktype - 48)*10)+(tckraw-48);
 }
 if(tcktype == 42)tckchar=tckraw-48;
 if(tcktype == 65)tckchar=tckraw+128;
 return tckchar;
 }
// bottom of int tchkey
 void tckeypar3(char* tckey2)
 {
 int tchraw,tchfilt,tchupper;
 tchupper=0;
 tchraw=tchkey();
 tchfilt = tchraw & 127;
 if((tchraw <= 127)&&(tchraw >= 32))
 {
 tchupper=49;
 *(tckey2 + 0)=(char)tchupper;
 *(tckey2 + 1)=(char)tchfilt;
 *(tckey2 + 2)=(char)32;
 }
 if(tchraw > 127)
 {
 tchupper=50;
 *(tckey2 + 0)=(char)tchupper;
 *(tckey2 + 1)=(char)65;
 *(tckey2 + 2)=(char)tchfilt;
 }
 if((tchraw >= 0)&&(tchraw < 32))
 {
 tchupper=53;
 *(tckey2 + 0)=(char)tchupper;
 *(tckey2 + 1)=(char)(tchfilt + 48);
 *(tckey2 + 2)=(char)32;
 }
 }
// bottom of tckeypar3
 int keyline2(char* keysto)
 {
 char kl2in[16];
 char kl2end[2];
 int keybulen;
 int kl2type,kl2step,kl2char,kl2allow;
 kl2end[0]=(char)13;
 kl2end[1]=(char)10;
 fwrite(kl2end,2,1,stdout);
// rem write(istdout,kl2end,2);
 keybulen=0;
 kl2allow=1;
 while(kl2allow == 1)
 {
 tckeypar3(kl2in);
 kl2type=(int)kl2in[0];
 kl2step=kl2type & 3;
 kl2char=(int)kl2in[kl2step];
 if(kl2type == 53)kl2char=kl2char-48;
 if(kl2char == 13)kl2allow=0;
 if((kl2char == 8)&&(keybulen >= 1))kl2step=0-1;
 if((kl2char == 8)&&(keybulen >= 1))keybulen=keybulen-1;
 if((kl2allow == 1)&&(kl2step > 0)&&(kl2char >= 32))
 {
 *(keysto+(keybulen+(kl2step-1)))=(char)kl2char;
 if(kl2step == 2)
 {
 *(keysto+keybulen)=(char)60;
 }
 keybulen=keybulen+kl2step;
 if(keybulen > 50)kl2allow=0;
 if(keybulen >= 1)
 {
 fwrite(kl2end,2,1,stdout);
 fwrite(keysto,keybulen,1,stdout);
 fwrite(kl2end,2,1,stdout);
// rem write(istdout,kl2end,2);
// rem write(istdout,keysto,keybulen);
// rem write(istdout,kl2end,2);
 }
// --------------------------
 }
// keybulen=keybulen+kl2step;
 }
 *(keysto + keybulen)=(char)0;
 return keybulen;
 }
// end of keyline2
// ----
// int getzakey()
// {
// int getzkres;
// char onezkey[4];
// fread(onezkey,1,1,stdin);
// getzkres=(int)onezkey[0];
// getzkres=getzkres & 255;
// return getzkres;
// }
// void getzkloop(char* zkres)
// {
// int zkterm,zktr,zkallow;
// zktr=0;
// zkallow=1;
// while(zkallow == 1)
// {
// zkterm=getzakey();
// if(zkterm == 13)zkallow=0;
// if(zkterm == 10)zkallow=0;
// if(zkallow == 1)
// {
// *(zkres + zktr)=(char)zkterm;
// zktr=zktr+1;
// if(zktr > 72)zkallow=0;
// }
// }
// }
// -----------------------------
 int main(char** skipstrs,int skipmany)
 {
 HANDLE fh;
 int fatneg,maiwid,maihgt,maibits,maictr,majctr;
 int bigwid,bigpos,majhgt,maihdr;
 int wqrjunk[1];
 fatneg=0-1073741824;
 fatneg=fatneg+fatneg;
 char rfn2[76];
 char maitest[20];
// char* localeres;
 maictr=0;
 while(maictr < 76)
 {
 rfn2[maictr]=(char)42;
 maictr=maictr+1;
 }
// --------------
// maictr=keyline2(rfn2);
// wrten("N",maictr);
// exit(0);
// --------------
 majctr=0;
 while(majctr < 76)
 {
 rfn2[majctr]=(char)0;
 majctr=majctr+1;
 }
 majctr=0;
 while(majctr < 16)
 {
 bigwist[majctr+majctr]=wist[majctr];
 bigwist[majctr+majctr+1]=wist[0];
 majctr=majctr+1;
 }
// rem localeres=setlocale(6,"en_US.UTF-8");
// writeline(localeres,16,stdout);
// wrten("N",(int)(localeres));
// -----------------------------------
// writeline(bigwist,32,stdout);
// writeline(oeel,2,stdout);
 writeline(wist,16,stdout);
 writeline(oeel,2,stdout);
// fh=CreateFile(rfn,fatneg,1,0,3,0,0);
 fwrite(aline,1,20,stdout);
 fwrite(oel,2,1,stdout);
// delay until replacement keyline **** getzkloop(rfn2);
 maictr=keyline2(rfn2);
 wrten("N",maictr);
// keyline2 succesfully written for Linux only.
 if(maictr < 5)
 {
 exit(4);
 }
 fh=fopen(rfn2,"rb");
 if((long)fh == 0L)
 {
 exit(8);
 }
// wrten(" ",(int)fh);
 maihdr=0;
 bigwid=1;
 getwidth(&rua,fh);
 maiwid=rua.bbiwidth;
 maihgt=rua.bbiheight;
 maibits=(int)(rua.bbibitcount);
 if(maibits == 1)
 {
 bigwid=(((maiwid+31)/32)*4);
 maihdr=62;
 }
 wrten(" ",maiwid);
// writeline(yist,4,stdout);
// writeline(oeel,2,stdout);
 wrten(" ",maihgt);
// writeline(xist,4,stdout);
// writeline(oeel,2,stdout);
 wrten("N",maibits);
 maictr=0;
 majhgt=maihgt+0;
 while(maictr < majhgt)
 {
 bigpos=(maihgt-1)-maictr;
 bigpos=bigpos*bigwid;
 bigpos=bigpos+maihdr;
// SetFilePointer(fh,bigpos,0,0);
 fseek(fh,bigpos,0);
 readoneline(maiwid,ralinei,maibits,fh);
// wrdisp(ralinei,maiwid);
 maictr=maictr+1;
 bigpos=(maihgt-1)-maictr;
 bigpos=bigpos*bigwid;
 bigpos=bigpos+maihdr;
 if(bigpos >= (1+maihdr))
 {
// SetFilePointer(fh,bigpos,0,0);
 fseek(fh,bigpos,0);
 readoneline(maiwid,ralinej,maibits,fh);
 }
 if(bigpos < (1+maihdr))
 {
 majctr=0;
 while(majctr < maiwid)
 {
 if((majctr & 3)!=0)
 {
 ralinej[majctr]=1;
 }
 if((majctr & 3)==0)
 {
 ralinej[majctr]=0;
 }
 majctr=majctr+1;
 }
 }
// ---------
 wwrdisp(ralinei,ralinej,maiwid);
// ------------------------
 maictr=maictr+1;
 }
 writeline(wist,16,stdout);
 writeline(oeel,2,stdout);
 wrten("N",(1000000/7));
 wrten("N",32767);
 fclose(fh);
 exit(0);
 return 0;
 }
// -------

// bottom of bwshow31
