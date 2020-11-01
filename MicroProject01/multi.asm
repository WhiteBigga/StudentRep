format PE console
entry start

include 'win32a.inc'
include 'mul_macro.inc'

;--------------------------------------------------------------------------
section '.data' data readable writable

        strVecSize   db 'size of vector? ', 0
        strIncorSize db 'Incorrect size of vector = %d', 10, 0
        strVecElemI  db 'Your integer number for [%d] index? ', 0
        strInputInfo db 'For each index enter an integer number: ', 0
        strScanInt   db '%d', 0
        strPosValue  db 'Multiplication of positive values = %d', 10, 0
        strNegValue  db 'Multiplication of negative values = %d', 10, 0
        strVecElemOut  db '[%d] = %d', 10, 0

        num          dd 0
        vec_size     dd 15
        multNeg      dd 1
        multPos      dd 1
        i            dd ?
        tmp          dd ?
        tmpStack     dd ?
        vec          rd 100

;--------------------------------------------------------------------------
section '.code' code readable executable
start:
; 1) vector input
        ;call VectorInput
        VInputMacro
; 2) get vector positive values multiplication
        VPosMacro
; 3) get vector negative values multiplication
        VNegMacro
; 4) output of the 1st multiplication
        push [multPos]
        push strPosValue
        call [printf]
; 5) output of the 2nd multiplication
        push [multNeg]
        push strNegValue
        call [printf]
; 6) test vector out
        ;call VectorOut
        VOutMacro
finish:
        call [getch]

        push 0
        call [ExitProcess]

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