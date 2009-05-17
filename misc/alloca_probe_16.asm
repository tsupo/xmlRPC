; via http://groups.google.com/group/microsoft.public.vc.mfc/browse_thread/thread/3f8a215607dfc5cc/71f145cf9ddd9a08?pli=1
;
;   for OpenSSL 0.9.8i or later

        .386
_TEXT   segment use32 para public 'CODE'
        public  __alloca_probe_16

        extrn __chkstk:abs  ; Absolute external constant 

__alloca_probe_16   proc near
arg_0   = dword ptr  8
            push    ecx
            lea     ecx, [esp+arg_0]
            sub     ecx, eax
            and     ecx, 0Fh
            add     eax, ecx
            sbb     ecx, ecx
            or      eax, ecx
            pop     ecx
            jmp     near ptr __chkstk
__alloca_probe_16   endp

public __alloca_probe_8
__alloca_probe_8    proc near
arg_0   = dword ptr  8
            push    ecx
            lea     ecx, [esp+arg_0]
            sub     ecx, eax
            and     ecx, 7
            add     eax, ecx
            sbb     ecx, ecx
            or      eax, ecx
            pop     ecx
            jmp     near ptr __chkstk
__alloca_probe_8    endp

_TEXT               ends
                    end
