LIBRARY IEEE ;                     
USE IEEE.STD_LOGIC_1164.ALL ; --��3���������㷢Ӧ���󲿷ֵ�VHDL��������
USE IEEE.STD_LOGIC_Arith.ALL ;
USE IEEE.STD_LOGIC_Unsigned.ALL ;

ENTITY int_div IS              
GENERIC(N:Integer:=4800);--�˴�������һ��Ĭ��ֵN��3������·Ϊ3��Ƶ��·;
Port
(Clockin:IN STD_LOGIC;
ClockOut:OUT STD_LOGIC           
);
END;


ARCHITECTURE Devider OF int_div IS
SIGNAL Counter:Integer RANGE 0 TO N-1;     
SIGNAL Temp1,Temp2:STD_LOGIC;		   --�źŵ������ڽṹ���ڣ������ⲿ
BEGIN
	PROCESS(Clockin)
BEGIN 
IF RISING_EDGE(Clockin) THEN 
	IF Counter=N-1 THEN
		counter<=0;
		Temp1<=Not Temp1;
	ELSE
		Counter<=Counter+1;
	END IF;
END IF;

IF falling_edge(clockin)	THEN
	IF Counter=N/2 THEN
		Temp2<=NOT Temp2;
	END IF;
END IF;
END PROCESS;
ClockOut<=Temp1 XOR Temp2;
END;