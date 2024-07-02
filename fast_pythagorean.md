
-O3 -mavx2 and -ffast-math
```
BM_pythagorean_hypot_float(int, int):
        vxorps  xmm1, xmm1, xmm1
        sub     rsp, 8
        vcvtsi2ss       xmm0, xmm1, edi
        vcvtsi2ss       xmm1, xmm1, esi
        call    hypotf
        add     rsp, 8
        vcvttss2si      eax, xmm0
        ret
```


```
BM_pythagorean_hypot_float(int, int):
        vxorps  xmm1, xmm1, xmm1
        sub     rsp, 8
        vcvtsi2ss       xmm0, xmm1, edi
        vcvtsi2ss       xmm1, xmm1, esi
        call    hypotf
        add     rsp, 8
        vcvttss2si      eax, xmm0
        ret
```