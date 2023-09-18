include console.inc

COMMENT *

   Заготовка программы

*

.data
Fstr DB 'Введите последовательность символов,с точкой в качестве признака конца текста.',0
Sstr DB 'Исходный текст:',0
FinC1 DB 'Текст после преобразовния по правилу 1:',0
FinC2 DB 'Текст после преобразовния по правилу 2:',0
Limstr DB 'Превышено допустимое количество символов.',0
Vodstr DB 'Пустая строка.',0
N=10
K=20
Orig_text DB N DUP (?)
Fin_text  DB K DUP (?)
SYM_NUM   DD 0

.CODE
ENTER_TEXT PROC									;ВВОД ТЕКСТА   procedure(var sym_num:dword; VAR адрес начала массива)
	PUSH EBP
	MOV	 EBP,ESP
	PUSH ESI
	PUSH EAX
	MOV EAX, [EBP+8]							;В EAX АДРЕС SYM_NUM
	MOV ESI, [EBP+12]							;В ESI АДРЕС НАЧАЛА МАССИВА
	MOV ECX,[EAX]
L:
	MOV ECX,[EAX]
	INCHAR BYTE PTR [ESI+ECX]					;ВВОД СИМВОЛА
	CMP	BYTE PTR [ESI+ECX],'.'					;CРАВНЕНИЕ СИМВОЛА С ТОЧКОЙ
	JE F
	INC DWORD PTR [EAX]							;УВЕЛИЧЕНИЕ СЧЕТЧИКА СИМВОЛОВ
	CMP DWORD PTR [EAX],N
	JA F
	JMP L
F:
	POP EAX
	POP ESI
	POP EBP
	RET [8]
ENTER_TEXT ENDP

CONDITION1 PROC                                 ;ВЫПОЛНЕНИЕ ПЕРВОГО УСЛОВИЯ procedure(sym_num:dword; VAR адрес начала массива)
	PUSH EBP
	MOV	 EBP,ESP
	PUSH ESI
	PUSH EAX
	PUSH ECX
	MOV EAX, [EBP+8]							;В EAX ЗНАЧЕНИЕ SYM_NUM
	MOV ESI, [EBP+12]							;В ESI АДРЕС НАЧАЛА МАССИВА
	MOV ECX,0
S:
	CMP BYTE PTR [ESI+ECX], 'A'
	JB M
	CMP BYTE PTR [ESI+ECX], 'Z'
	JA M
	CMP BYTE PTR [ESI+ECX], 'Z'
	JNE KA										;ЧАСТНЫЙ СЛУЧАЙ, ПРИ 'Z'
	MOV BYTE PTR [ESI+ECX], 'A'					;ЗАМЕНА 'Z' НА 'A'
	JMP M
KA:												
	ADD BYTE PTR [ESI+ECX],1					;ЗАМЕНА СИМВОЛА НА СЛЕДУЮЩИЙ, В ОБЩЕМ СЛУЧАЕ
M:												;ЕСЛИ ЭТО НЕ СТРОЧНАЯ БУКВА
	INC ECX
	CMP ECX,EAX
	JNE S                                       ;ЗАЦИКЛИВАНИЕ, ПОКА СЧЕТЧИК НЕ ДОСТИГНЕТ SYM_NUM
	
	POP ECX
	POP EAX
	POP ESI
	POP EBP
	RET [8]
CONDITION1 ENDP

CONDITION2 PROC									;ПРОЦЕДУРА ВТОРОГО УСЛОВИЯ procedure(sym_num:dword; адрес начала исходного массива; адрес начала конечного массива)
	PUSH EBP
	MOV EBP,ESP
	PUSH EAX
	PUSH ECX
	PUSH EDX
	PUSH ESI
	
	MOV ECX,[EBP+8]								;В ЕСХ ЗНАЧЕНИЕ SYM_NUM
	MOV EDX,[EBP+12]							;В ЕSР АДРЕС НАЧАЛА ИСХОДНОГО МАССИВА
	MOV ESI,[EBP+16]							;В ESI АДРЕС НАЧАЛА КОНЕЧНОГО МАССИВА
	
L1:
	MOV AL,  BYTE PTR [EDX+ECX-1]
	MOV BYTE PTR [ESI+2*ECX-1],AL
	MOV BYTE PTR [ESI+2*ECX-2],AL
	LOOP L1
	
	POP ESI
	POP EDX
	POP ECX
	POP EAX
	POP EBP
	RET [12]
CONDITION2 ENDP

Start:
	OUTSTR OFFSET Fstr
	NEWLINE
	PUSH OFFSET Orig_text
	PUSH OFFSET SYM_NUM
	CALL ENTER_TEXT
	
	CMP SYM_NUM,N	 							;ПРОВЕРКА,ПРЕВЫШЕНО ЛИ КОЛИЧЕСТВО СИМВОЛОВ							
	JA LIM
	
	CMP SYM_NUM,0								;ПРОВЕРКА НА ПУСТУЮ СТРОКУ
	JE VOD
	
	MOV ECX,SYM_NUM
	MOV Orig_text[ECX],0
	OUTSTR OFFSET Sstr
	NEWLINE
	OUTSTR OFFSET Orig_text
	NEWLINE
	
	;Проверка условия
	MOV AL,Orig_text[0]
	MOV BL,Orig_text[ECX-1]
	CMP AL,'0'
	JB  CON2
	CMP AL,'9'
	JA  CON2
	CMP BL,'0'
	JB  CON2
	CMP BL,'9'
	JA  CON2
	CMP AL,BL
	JE CON2
	;;;;;;;;;;;;;;;;;;;;;;;;
	
CON1:											;ПЕРВОЕ УСЛОВИЕ
	PUSH OFFSET Orig_text						;АДРЕС НАЧАЛА МАССИВА КЛАДЕТСЯ В СТЕК
	PUSH SYM_NUM								;ЗНАЧЕНИЕ СЧЕТЧИКА СИМВОЛОВ КЛАДЕТСЯ В СТЕК
	CALL CONDITION1
	MOV Orig_text[ECX],0						
	OUTSTR OFFSET FinC1					
	NEWLINE
	OUTSTR OFFSET Orig_text						;ВЫВОД ПРЕОБРАЗОВАННОГО МАССИВА
	NEWLINE
	JMP FIN
CON2:											;ВТОРОЕ УСЛОВИЕ
	PUSH OFFSET Fin_text
	PUSH OFFSET Orig_text
	PUSH SYM_NUM
	CALL CONDITION2
	MOV Fin_text[2*ECX],0
	OUTSTR OFFSET FinC2
	NEWLINE
	OUTSTR OFFSET Fin_text
	NEWLINE
	JMP FIN
LIM:
	OUTSTR OFFSET Limstr
	NEWLINE
	JMP FIN
VOD:
	OUTSTR OFFSET Vodstr
	NEWLINE
FIN:
	EXIT
END Start
