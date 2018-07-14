#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#define rotr(x,y) ((((x)>>(y))|(x)<<(32-(y)))&0xffffffff)
#define ds0(x) (rotr((x),7))^(rotr((x),18))^((x)>>3)
#define ds1(x) (rotr((x),17))^(rotr((x),19))^((x)>>10)
#define dss0(x) (rotr((x),2))^(rotr((x),13))^(rotr((x),22))
#define dss1(x) (rotr((x),6))^(rotr((x),11))^(rotr((x),25))
#define MAJ(x,y,z) ((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z));
#define CH(x, y, z) ((x) & (y)) ^ ((~(x)) & (z));
 
int main(void){
    struct timeval start_time, now;

    unsigned int k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
          0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
          0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
          0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
          0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
          0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
          0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
          0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
          0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
          0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
          0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
          0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
          0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
          0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
          0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
          0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    unsigned int oa = 0x6a09e667;
    unsigned int ob = 0xbb67ae85;
    unsigned int oc = 0x3c6ef372;
    unsigned int od = 0xa54ff53a;
    unsigned int oe = 0x510e527f;
    unsigned int of = 0x9b05688c;
    unsigned int og = 0x1f83d9ab;
    unsigned int oh = 0x5be0cd19;

    int i, j, n = 0;
    unsigned int a, b, c, d, e, f, g, h;
    unsigned int s0 = 0;
    unsigned int maj = 0;
    unsigned int t2 = 0;
    unsigned int s1 = 0;
    unsigned int ch = 0;
    unsigned int t1 = 0;
    unsigned int w[64] = {0};
    
    char str[8][9];
    unsigned int result[10][8] = {0};

    //時間計測開始
    gettimeofday(&start_time, NULL);
    
    //とりあえず50音、行毎に10ループ
    for(n = 0; n < 10; n++){
        a = oa;
        b = ob;
        c = oc;
        d = od;
        e = oe;
        f = of;
        g = og;
        h = oh;

        w[4] = 0x00000000;
        w[5] = 0x00000000;
        w[6] = 0x00000000;
        w[7] = 0x00000000;
        w[8] = 0x00000000;
        w[9] = 0x00000000;
        w[10] = 0x00000000;
        w[11] = 0x00000000;
        w[12] = 0x00000000;
        w[13] = 0x00000000;
        w[14] = 0x00000000;

        switch(n){
            //あいうえお
            case 0:
                w[0] = 0xe38182e3;
                w[1] = 0x8184e381;
                w[2] = 0x86e38188;
                w[3] = 0xe3818a80;
                w[15] = 0x00000078;
                break;
            //かきくけこ
            //e3818be3818de3818fe38191e38193
            case 1:
                w[0] = 0xe3818be3;
                w[1] = 0x818de381;
                w[2] = 0x8fe38191;
                w[3] = 0xe3819380;
                w[15] = 0x00000078;
                break;
            //さしすせそ
            //e38195e38197e38199e3819be3819d
            case 2:
                w[0] = 0xe38195e3;
                w[1] = 0x8197e381;
                w[2] = 0x99e3819b;
                w[3] = 0xe3819d80;
                w[15] = 0x00000078;
                break;
            //たちつてと
            //e3819fe381a1e381a4e381a6e381a8
            case 3:
                w[0] = 0xe3819fe3;
                w[1] = 0x81a1e381;
                w[2] = 0xa4e381a6;
                w[3] = 0xe381a880;
                w[15] = 0x00000078;
                break;
            //なにぬねの
            //e381aae381abe381ace381ade381ae
            case 4:
                w[0] = 0xe381aae3;
                w[1] = 0x81abe381;
                w[2] = 0xace381ad;
                w[3] = 0xe381ae80;
                w[15] = 0x00000078;
                break;
            //はひふへほ
            //e381afe381b2e381b5e381b8e381bb
            case 5:
                w[0] = 0xe381afe3;
                w[1] = 0x81b2e381;
                w[2] = 0xb5e381b8;
                w[3] = 0xe381bb80;
                w[15] = 0x00000078;
                break;

            //まみむめも
            //e381bee381bfe38280e38281e38282
            case 6:
                w[0] = 0xe381bee3;
                w[1] = 0x81bfe382;
                w[2] = 0x80e38281;
                w[3] = 0xe3828280;
                w[15] = 0x00000078;
                break;
            //やゆよ
            //e38284e38286e38288
            case 7:
                w[0] = 0xe38284e3;
                w[1] = 0x8286e382;
                w[2] = 0x88800000;
                w[3] = 0x00000000;
                w[15] = 0x00000048;
                break;
            //らりるれろ
            //e38289e3828ae3828be3828ce3828d
            case 8:
                w[0] = 0xe38289e3;
                w[1] = 0x828ae382;
                w[2] = 0x8be3828c;
                w[3] = 0xe3828e80;
                w[15] = 0x00000078;
                break;
            //わをん
            //e3828fe38292e38293
            case 9:
                w[0] = 0xe3828fe3;
                w[1] = 0x8292e382;
                w[2] = 0x93800000;
                w[3] = 0x00000000;
                w[15] = 0x00000048;
                break;
            default:
                break;
        }
    

        for(i = 16; i < 64; i++){
            s0 = ds0(w[i-15]);
            s1 = ds1(w[i-2]);
            w[i] = (w[i-16] + s0 + w[i-7] + s1) & 0xffffffff;
        }

        for (i=0; i < 64; i++){
            s0 = dss0(a);
            maj = MAJ(a, b, c)
            t2 = s0 + maj;
            s1 = dss1(e);
            ch = CH(e, f, g)
            t1 = h + s1 + ch + k[i] + w[i];

            h = g;
            g = f;
            f = e;
            e = (d + t1) & 0xffffffff;
            d = c;
            c = b;
            b = a;
            a = (t1 + t2) & 0xffffffff;

            // char buff[12];
            // snprintf(buff, 12, "%#x", h);
            // puts(buff);

        }

        result[n][0] = (a + oa) & 0xffffffff;
        result[n][1] = (b + ob) & 0xffffffff;
        result[n][2] = (c + oc) & 0xffffffff;
        result[n][3] = (d + od) & 0xffffffff;
        result[n][4] = (e + oe) & 0xffffffff;
        result[n][5] = (f + of) & 0xffffffff;
        result[n][6] = (g + og) & 0xffffffff;
        result[n][7] = (h + oh) & 0xffffffff;
    };
    /*ここまで処理
    あとは時間計測*/
    gettimeofday(&now, NULL);

    double sec = (double)(now.tv_sec - start_time.tv_sec);
    double micro = (double)(now.tv_usec - start_time.tv_usec);
    double passed = sec + micro / 1000.0 / 1000.0;

    for(i=0; i < 10; i++){

        char buff[8][20];
        for (j = 0; j < 8; j++){
            snprintf(buff[j], 20, "%#x", result[i][j]);
            if(strlen(buff[j]) < 10){
                strcat(buff[j], "0");
            }
            strncpy(str[j], buff[j]+2, 8);
            str[j][8] = '\0';
        }
        for (j = 1; j < 8; j++){
            strcat(str[0], str[j]);
        }
        printf("%s\n", str[0]);
    }


    printf("%lf\n", passed); 
    return 0;
}