;Ustyukhin Andrey 192 \\\  Variant 5
;Print array "B" from elements "A", which are not equal to the scanned number X.
format PE console
entry start

include 'win32a.inc'

;--------------------------------------------------------------------------
section '.data' data readable writable

        strVecSize   db 'size of vector? ', 0
        strIncorSize db 'Incorrect size of vector = %d', 10, 0
        strVecElemI  db '[%d]? ', 0
        strScanInt   db '%d', 0
        strSumValue  db 'Summa = %d', 10, 0
        strVecElemOut db '[%d] = %d', 10, 0
        strNumber     db 'Special number? ', 0


        num          dd ?
        vec_size     dd 0
        vec_size_ne  dd 0
        sum          dd 0
        i            dd ?
        tmp          dd ?
        tmpStack     dd ?
        vec          rd 100
        vec_ne       rd 100

;--------------------------------------------------------------------------
section '.code' code readable executable
start:
; 1) num input
        call NumberInput
; 2) vector input
        call VectorInput
        returnInput:

; 3) test vector out
        call VectorOut
        returnVecOut:
finish:
        call [getch]

        push 0
        call [ExitProcess]

;--------------------------------------------------------------------------
NumberInput:
        push strNumber
        call [printf]
        add esp, 4

        push num
        push strScanInt
        call [scanf]
        add esp, 8
        ret
;--------------------------------------------------------------------------
VectorInput:
        push strVecSize
        call [printf]
        add esp, 4

        push vec_size
        push strScanInt
        call [scanf]
        add esp, 8

        mov eax, [vec_size]
        cmp eax, 0
        jg  getVector
; fail size
        push vec_size
        push strIncorSize
        call [printf]
        push 0
        call [ExitProcess]
; else continue...
;--------------------------------------------------------------------------
getVector:
        mov [vec_size_ne], 0
        xor ecx, ecx            ; ecx = 0
        mov ebx, vec            ; ebx = &vec


   getVecLoop:
        mov [tmp], ebx
        cmp ecx, [vec_size]
        jge endInputVector       ; to end of loop

        ; input element's number
        mov [i], ecx
        push ecx
        push strVecElemI
        call [printf]
        add esp, 8

        ; enter an element
        push ebx
        push strScanInt
        call [scanf]

        mov eax, [num]
        cmp dword [ebx], eax
        je getNewVector

        ; to new array
        mov edx, dword [ebx]
        mov eax, [vec_size_ne]
        mov [vec_ne + 4*eax], edx
        inc [vec_size_ne]


   getNewVector:
       ; add esp, 8

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp]
        add ebx, 4
        jmp getVecLoop
endInputVector:
        jmp returnInput
;--------------------------------------------------------------------------
VectorOut:
        xor ecx, ecx            ; ecx = 0
    putVecLoop:
        cmp ecx, [vec_size_ne]
        je endOutputVector      ; to end of loop
        mov [i], ecx

        ; output element
        push dword [vec_ne + 4*ecx]
        push ecx
        push strVecElemOut
        call [printf]

        mov ecx, [i]
        inc ecx
        jmp putVecLoop
endOutputVector:
        jmp returnVecOut
;-------------------------------third act - including HeapApi--------------------------
                                                 
section '.idata' import data readable
    library kernel, 'kernel32.dll',\
            msvcrt, 'msvcrt.dll',\
            user32,'USER32.DLL'

include 'api\user32.inc'
include 'api\kernel32.inc'
    import kernel,\
           ExitProcess, 'ExitProcess',\
           HeapCreate,'HeapCreate',\
           HeapAlloc,'HeapAlloc'
  include 'api\kernel32.inc'
    import msvcrt,\
           printf, 'printf',\
           scanf, 'scanf',\
           getch, '_getch'