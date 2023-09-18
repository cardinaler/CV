include console.inc

COMMENT *

   ��������� ���������

*

.data
Fstr DB '������� ������������������ ��������,� ������ � �������� �������� ����� ������.',0
Sstr DB '�������� �����:',0
FinC1 DB '����� ����� ������������� �� ������� 1:',0
FinC2 DB '����� ����� ������������� �� ������� 2:',0
Limstr DB '��������� ���������� ���������� ��������.',0
Vodstr DB '������ ������.',0
N=10
K=20
Orig_text DB N DUP (?)
Fin_text  DB K DUP (?)
SYM_NUM   DD 0

.CODE
ENTER_TEXT PROC									;���� ������   procedure(var sym_num:dword; VAR ����� ������ �������)
	PUSH EBP
	MOV	 EBP,ESP
	PUSH ESI
	PUSH EAX
	MOV EAX, [EBP+8]							;� EAX ����� SYM_NUM
	MOV ESI, [EBP+12]							;� ESI ����� ������ �������
	MOV ECX,[EAX]
L:
	MOV ECX,[EAX]
	INCHAR BYTE PTR [ESI+ECX]					;���� �������
	CMP	BYTE PTR [ESI+ECX],'.'					;C�������� ������� � ������
	JE F
	INC DWORD PTR [EAX]							;���������� �������� ��������
	CMP DWORD PTR [EAX],N
	JA F
	JMP L
F:
	POP EAX
	POP ESI
	POP EBP
	RET [8]
ENTER_TEXT ENDP

CONDITION1 PROC                                 ;���������� ������� ������� procedure(sym_num:dword; VAR ����� ������ �������)
	PUSH EBP
	MOV	 EBP,ESP
	PUSH ESI
	PUSH EAX
	PUSH ECX
	MOV EAX, [EBP+8]							;� EAX �������� SYM_NUM
	MOV ESI, [EBP+12]							;� ESI ����� ������ �������
	MOV ECX,0
S:
	CMP BYTE PTR [ESI+ECX], 'A'
	JB M
	CMP BYTE PTR [ESI+ECX], 'Z'
	JA M
	CMP BYTE PTR [ESI+ECX], 'Z'
	JNE KA										;������� ������, ��� 'Z'
	MOV BYTE PTR [ESI+ECX], 'A'					;������ 'Z' �� 'A'
	JMP M
KA:												
	ADD BYTE PTR [ESI+ECX],1					;������ ������� �� ���������, � ����� ������
M:												;���� ��� �� �������� �����
	INC ECX
	CMP ECX,EAX
	JNE S                                       ;������������, ���� ������� �� ��������� SYM_NUM
	
	POP ECX
	POP EAX
	POP ESI
	POP EBP
	RET [8]
CONDITION1 ENDP

CONDITION2 PROC									;��������� ������� ������� procedure(sym_num:dword; ����� ������ ��������� �������; ����� ������ ��������� �������)
	PUSH EBP
	MOV EBP,ESP
	PUSH EAX
	PUSH ECX
	PUSH EDX
	PUSH ESI
	
	MOV ECX,[EBP+8]								;� ��� �������� SYM_NUM
	MOV EDX,[EBP+12]							;� �S� ����� ������ ��������� �������
	MOV ESI,[EBP+16]							;� ESI ����� ������ ��������� �������
	
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
	
	CMP SYM_NUM,N	 							;��������,��������� �� ���������� ��������							
	JA LIM
	
	CMP SYM_NUM,0								;�������� �� ������ ������
	JE VOD
	
	MOV ECX,SYM_NUM
	MOV Orig_text[ECX],0
	OUTSTR OFFSET Sstr
	NEWLINE
	OUTSTR OFFSET Orig_text
	NEWLINE
	
	;�������� �������
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
	
CON1:											;������ �������
	PUSH OFFSET Orig_text						;����� ������ ������� �������� � ����
	PUSH SYM_NUM								;�������� �������� �������� �������� � ����
	CALL CONDITION1
	MOV Orig_text[ECX],0						
	OUTSTR OFFSET FinC1					
	NEWLINE
	OUTSTR OFFSET Orig_text						;����� ���������������� �������
	NEWLINE
	JMP FIN
CON2:											;������ �������
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
