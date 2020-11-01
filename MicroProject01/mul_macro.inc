;--------------------------------------------------------------------------
;Macros for input elements of array
macro VInputMacro {
VectorInput:
        xor ecx, ecx            ; ecx = 0
        mov ebx, vec            ; ebx = &vec
getVecLoop:   ; loop for reading each element
        mov [tmp], ebx
        cmp ecx, [vec_size]      ; check if it is the last element of array
        jge endInputVector       ; to end of loop

        ; input element text
        mov [i], ecx
        push ecx
        push strVecElemI
        call [printf]

        ; reading int number
        push ebx
        push strScanInt
        call [scanf]
        add esp, 8

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp]
        add ebx, 4
        jmp getVecLoop    ; back to loop
endInputVector:
        ;;ret
}

;--------------------------------------------------------------------------
;Macros for calculating multiplication of positive numbers
macro VPosMacro {
  VectorPosMul:
        xor ecx, ecx            ; ecx = 0
        mov ebx, vec            ; ebx = &vec
  posMulVecLoop:
        cmp ecx, [vec_size]    ; check if it is the last element of array
        je endPVector
        mov eax, [num]
        cmp dword [ebx], eax   ;skip the element if it is less or equals to 0
        jle nextPElem          ; to end of loop
        mov eax, [multPos]
        imul dword [ebx]       ;multiplicating
        mov [multPos], eax
  nextPElem:
        inc ecx
        add ebx, 4
        jmp posMulVecLoop      ;back to loop
  endPVector:
        ;;ret
}
;--------------------------------------------------------------------------
;Macros for calculating multiplication of negative numbers
macro VNegMacro {
  VectorNegMul:
        xor ecx, ecx            ; ecx = 0
        mov ebx, vec            ; ebx = &vec
  negMulVecLoop:
        cmp ecx, [vec_size]     ; check if it is the last element of array
        je endNVector
        mov eax, [num]
        cmp dword [ebx], eax    ;skip the element if it is greater than 0
        jge nextNElem            ; to end of loop
        mov eax, [multNeg]
        imul dword [ebx]        ;multiplicating
        mov [multNeg], eax
  nextNElem:
        inc ecx
        add ebx, 4
        jmp negMulVecLoop       ;back to loop
  endNVector:
        ;;ret
}

;--------------------------------------------------------------------------
;Output of array to know that nothing has changed
macro VOutMacro {
  VectorOut:
        xor ecx, ecx            ; ecx = 0
        mov ebx, vec            ; ebx = &vec
  putVecLoop:                   ; loop to display each element
        mov [tmp], ebx
        cmp ecx, [vec_size]     ; check if it is the last element of array
        je endOutputVector      ; to end of loop
        mov [i], ecx

        ;; output element
        push dword [ebx]
        push ecx
        push strVecElemOut
        call [printf]

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp]
        add ebx, 4
        jmp putVecLoop
endOutputVector:
        ;;ret
}
