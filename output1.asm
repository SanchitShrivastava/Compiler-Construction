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
b3 resd 1
b2 resd 1
c2 resd 1
d2 resd 1
.bufferop1	resd	0
section .text
call _UserInput
mov dword[b2], eax
mov eax,20
push eax
pop eax
mov dword[c2],eax
call _UserInput
mov dword[d2], eax
push dword[b2]
push dword[c2]
pop ebx
pop eax
add eax,ebx
push eax
push dword[d2]
pop ebx
pop eax
add eax,ebx
push eax
pop eax
mov dword[b3],eax
mov eax, dword[b3]
call _NegPosPrint
call _PrintNewLine
mov	ebx, 0
mov	eax, 1
int	0x80
