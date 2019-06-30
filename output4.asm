_PrintNewLine:
section .data
.nl		 db		10
section .text
		push		ecx
		push		edx
		mov		ecx, .nl
		mov		edx, 1
		;print the string
		push		eax
		push		ebx
		mov		eax,4
		mov		ebx,1
		int		0x80
		pop		ebx
		pop		eax
		pop		edx
		pop		ecx
		ret
_UserInput:
section .bss
buffer	resb	120
intg	resd	1
isneg	resb	1	
section .text
		pushad		
		mov	esi, buffer
		mov	edi, 0	
.loop1:	
		mov	eax, 03	
		mov	ebx, 0	
		mov	ecx, esi
		mov	edx, 1	
		int	0x80	
		cmp	byte[esi], 0
		je	 .parse
		cmp	byte[esi], 10
		je	 .parse
		inc	esi
		inc	edi	
		jmp	.loop1
.parse:
		mov	esi, buffer	
		mov	ecx, edi	
		mov	dword[intg], 0
		mov	byte[isneg], 0
.negativ:	
 		cmp	byte[esi], '-'
		jne	.loop
		inc	esi
		inc	byte[isneg]
.loop:	  mov	ebx, 0
		mov	bl, byte[esi]	
 		cmp	bl, 10	
  		je	 .done	
		cmp	bl, '0'
		jb	 .done
		cmp	bl, '9'
		ja	 .done	
		mov	edx, 10
		mov	eax, dword[intg]
		mul	edx	
 		sub	bl, '0'
		add	eax, ebx
		mov	dword[intg], eax
		inc	esi
		loop    .loop
.done:
  		cmp	byte[isneg], 0
		je	 .return
		neg	eax
		mov	dword [intg], eax
.return:
		popad
		mov	eax, [intg]
		ret
_DecimalPrint:
section		.bss
.decstr		resb		10
.ct1		resd		1
section .text
		pushad
		mov		 dword[.ct1],0
		mov		 edi,.decstr
		add		 edi,9
		xor		 edx,edx	
.whileNotZero:
		mov		 ebx,10	
		div		 ebx	
		add		 edx,'0'
		mov		 byte[edi],dl
		dec		 edi
		inc		 dword[.ct1] 
		xor		 edx,edx
		cmp		 eax,0
		jne		 .whileNotZero
		inc		 edi
		mov		 ecx, edi	 
		mov		 edx, [.ct1]
		mov		 eax, 4
		mov		 ebx, 1
		int		 0x80
		popad
		ret
_NegPosPrint:
section .data
		minus db '-'
section .text
		pushad
		cmp eax, 0000h
		jge X1
		neg eax
		push eax
		mov eax,4
		mov ebx, 1
		mov ecx, minus
		mov edx, 1
		int 80h
		pop eax
		X1:
		call _DecimalPrint
		popad
		ret
global _start
_start:
section .bss
d4.maths resd 1
d4.physics resd 1
d4.chemistry resd 1
b5 resd 1
d5cb34567 resd 1
b3c2.maths resd 1
b3c2.physics resd 1
b3c2.chemistry resd 1
.bufferop1	resd	3
section .text
mov eax,1
push eax
pop eax
mov dword[b5],eax
call _UserInput
mov dword[d5cb34567], eax
mov eax,0
push eax
pop eax
mov dword[d4.maths],eax
mov eax,0
push eax
pop eax
mov dword[d4.physics],eax
mov eax,0
push eax
pop eax
mov dword[d4.chemistry],eax
.loop0:
push dword[b5]
push dword[d5cb34567]
pop ebx
pop eax
push 0ffffh
cmp eax,ebx
jle .rel0
pop eax
push 0000h
.rel0:
pop eax
cmp eax,0000h
je .endloop0
call _UserInput
mov dword[b3c2.maths], eax
call _UserInput
mov dword[b3c2.physics], eax
call _UserInput
mov dword[b3c2.chemistry], eax
push dword[b3c2.maths]
push dword[b3c2.physics]
push dword[b3c2.chemistry]
push dword[d4.maths]
push dword[d4.physics]
push dword[d4.chemistry]
pop dword[.bufferop1+8]
pop dword[.bufferop1+4]
pop dword[.bufferop1+0]
pop eax
add eax, dword[.bufferop1+8]
mov dword[.bufferop1+8], eax
pop eax
add eax, dword[.bufferop1+4]
mov dword[.bufferop1+4], eax
pop eax
add eax, dword[.bufferop1+0]
mov dword[.bufferop1+0], eax
push dword[.bufferop1+0]
push dword[.bufferop1+4]
push dword[.bufferop1+8]
pop eax
mov dword[d4.chemistry],eax
pop eax
mov dword[d4.physics],eax
pop eax
mov dword[d4.maths],eax
push dword[b5]
mov eax,1
push eax
pop ebx
pop eax
add eax,ebx
push eax
pop eax
mov dword[b5],eax
jmp .loop0
.endloop0:
mov eax,dword[d4.maths]
call _NegPosPrint
call _PrintNewLine
mov eax,dword[d4.physics]
call _NegPosPrint
call _PrintNewLine
mov eax,dword[d4.chemistry]
call _NegPosPrint
call _PrintNewLine
mov	ebx, 0
mov	eax, 1
int	0x80
