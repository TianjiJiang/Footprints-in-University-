LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY filter_200us IS
PORT(
clk,in_bit:	IN	STD_LOGIC;
out_bit:	OUT	STD_LOGIC
);
END;

ARCHITECTURE one OF	filter_200us IS
SIGNAL cnt:STD_LOGIC_VECTOR(19 DOWNTO 0);
SIGNAL out_bit_r:STD_LOGIC;
BEGIN
out_bit<=out_bit_r;

PROCESS(clk)
BEGIN
	IF RISING_EDGE(clk) THEN
		IF	in_bit ='1'	THEN	--һ�����ָߵ�ƽ����λ������
			cnt	<=X"00000";		--��0������
			out_bit_r <='1';	--�����1
		ELSE
			IF cnt>=9600	THEN	--clk=48M ԼΪ200us
				out_bit_r<='0';	--�͵�ƽ��ȴ���200usʱ����͵�ƽ.
			ELSE				--�͵�ƽ���С��200usʱ����ߵ�ƽ.
				cnt<=cnt+1;		--�������ۼ�
				out_bit_r<='1';
			END IF;
		END IF;
	END IF;
END PROCESS;
END;