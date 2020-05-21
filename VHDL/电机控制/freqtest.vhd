LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY	freqtest IS
PORT(
clock:		IN	STD_LOGIC;						--ϵͳʱ��
freq_input:	IN	STD_LOGIC;						--�����ź�����
dig:		OUT	STD_LOGIC_VECTOR(7 DOWNTO 0);	--�����ѡ���������
seg:		OUT STD_LOGIC_VECTOR(7 DOWNTO 0);	--����ܶ��������
test:		OUT STD_LOGIC_VECTOR(9 DOWNTO 0)	--���Ƶ���źţ����ڲ���
);
END;

ARCHITECTURE one OF freqtest IS
---------------------------------<<����10���Ƽ�����ģ����������ʾ��ģ��
COMPONENT cnt10 
PORT(
clk:	IN		STD_LOGIC;					--����ʱ��
rst:	IN		STD_LOGIC;					--��λ�ź�
cin:	IN  	STD_LOGIC;					--��λ����
cout:	BUFFER	STD_LOGIC;					--��λ���
dout:	OUT 	STD_LOGIC_VECTOR(3 DOWNTO 0)--�������
);
END COMPONENT;

COMPONENT scan_led 
PORT(
clk_1k:	IN	STD_LOGIC;
d:		IN	STD_LOGIC_VECTOR(31 DOWNTO 0);		--����Ҫ��ʾ������
dig:	OUT	STD_LOGIC_VECTOR(7 	DOWNTO 0);		--�����ѡ���������
seg:	OUT STD_LOGIC_VECTOR(7 	DOWNTO 0)		--����ܶ��������
);
END COMPONENT;
------------------------------------->>����10���Ƽ�����ģ����������ʾ��ģ��
SIGNAL 	counter :	STD_LOGIC_VECTOR(25 DOWNTO 0);		--ʱ�ӷ�Ƶ������
SIGNAL 	freq_result:	STD_LOGIC_VECTOR(31 DOWNTO 0);	--Ƶ�ʲ�������Ĵ���
SIGNAL 	pre_freq:	STD_LOGIC_VECTOR(31 DOWNTO 0);			--��������Ĵ���
SIGNAL	divide_clk:	STD_LOGIC;			--1Hzբ���ź�
SIGNAL	clk_scan:	STD_LOGIC;			--�����ɨ����ʾʱ��
SIGNAL  cout1,cout2,cout3,cout4,cout5,cout6,cout7:STD_LOGIC;
SIGNAL  rst:		STD_LOGIC;------NEW_2006_9_21

BEGIN
clk_scan<=counter(15);	--��̬ɨ��ʱ��
test<=counter(9 DOWNTO 0);		--���Ƶ���źţ����ڲ���

PROCESS(clock)		--ʱ�ӷ�Ƶ���̣��ֳ�1Hz��׼�ź�
BEGIN
	IF	RISING_EDGE(clock) THEN 
		IF divide_clk='1' THEN
			counter<=B"00_0000_0000_0000_0000_0000_0000";
		ELSE
			counter<=counter+1;
		END IF;
	END IF;
END PROCESS;
divide_clk<='1' WHEN (counter>=48000000) ELSE '0';
--<<�������ֵ����.
PROCESS(clock)
BEGIN
	IF	RISING_EDGE(clock) THEN 
		IF divide_clk='1'  THEN
			freq_result<=pre_freq;	
		END IF;		
	END IF;
END PROCESS;

PROCESS(clock)
BEGIN
	IF	RISING_EDGE(clock) THEN 
		IF divide_clk='1' THEN
			rst<='1';
		ELSE
			rst<='0';
		END IF;		
	END IF;
END PROCESS;

--8λʮ���Ƽ���ģ��:��8��ʮ���Ƽ���ģ�鹹��
U1:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>'1',  cout=>cout1,dout=>pre_freq(3 DOWNTO 0));
U2:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout1,cout=>cout2,dout=>pre_freq(7  DOWNTO 4));
U3:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout2,cout=>cout3,dout=>pre_freq(11 DOWNTO 8));
U4:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout3,cout=>cout4,dout=>pre_freq(15 DOWNTO 12));
U5:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout4,cout=>cout5,dout=>pre_freq(19 DOWNTO 16));
U6:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout5,cout=>cout6,dout=>pre_freq(23 DOWNTO 20));
U7:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout6,cout=>cout7,dout=>pre_freq(27 DOWNTO 24));
U8:cnt10	PORT	MAP(clk=>freq_input,rst=>rst,cin=>cout7,			dout=>pre_freq(31 DOWNTO 28));

U9:	scan_led PORT	MAP(clk_1k=>clk_scan,d=>freq_result,dig=>dig,seg=>seg);
END;

