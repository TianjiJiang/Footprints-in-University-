LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY moto_test IS
PORT(
clock_48M:		IN 	STD_LOGIC;	--ϵͳʱ��(48MHz)
key:		IN 	STD_LOGIC_VECTOR(3 DOWNTO 0);--��������(key1~key3)
pwm_in:		IN  STD_LOGIC;		--������PWM������
pwm_en:		OUT STD_LOGIC;		--PWM����ʹ�ܶ�
duty_cycle:	OUT	STD_LOGIC_VECTOR(3 DOWNTO 0);--PWMռ�ձȿ�������
motoa,motob:OUT STD_LOGIC;		--PWM������
led:		OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
);
END;

ARCHITECTURE one OF moto_test IS
SIGNAL duty_cycle_io:	STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL pwm_en_io:		STD_LOGIC;
SIGNAL count:			STD_LOGIC_VECTOR(16 DOWNTO 0);--ʱ�ӷ�Ƶ������
SIGNAL dout1,dout2,dout3:STD_LOGIC_VECTOR(3 DOWNTO 0);--�����Ĵ���
SIGNAL moto_dir:		STD_LOGIC;--��������ת
SIGNAL k_debounce:		STD_LOGIC_VECTOR(3  DOWNTO 0);--������������
SIGNAL clk:				STD_LOGIC;--��Ƶʱ��
SIGNAL key_edge:		STD_LOGIC_VECTOR(3  DOWNTO 0);
SIGNAL updown:				STD_LOGIC;--��Ƶʱ��

BEGIN
led(4 DOWNTO 0)<=NOT (pwm_en_io & duty_cycle_io);--LED����״ָ̬ʾ
pwm_en <= pwm_en_io;
duty_cycle <= duty_cycle_io;

PROCESS(clock_48M)
BEGIN
	IF RISING_EDGE(clock_48m) THEN
		IF count<120000 THEN	
			count<=count+1;
			clk<='0';
		ELSE
			count<=B"0_0000_0000_0000_0000";
			clk<='1';
		END IF;
	END IF;
END PROCESS;
	-------------------------------------------<<������������
PROCESS (clock_48m)
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF clk='1' THEN
			dout1<=key;
			dout2<=dout1;
			dout3<=dout2;
		END IF;
	END IF;
END PROCESS;



PROCESS (clock_48M)
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		k_debounce<=dout1 OR dout2 OR dout3;--������������.
	END IF;
END PROCESS;
key_edge<=NOT (dout1 OR dout2 OR dout3) AND k_debounce;



PROCESS(clock_48M)--����1 ���Ƶ綯���ٶ�
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF key_edge(0)='1' THEN
			duty_cycle_io<=duty_cycle_io+1;
			IF updown = '1' THEN
				duty_cycle_io<=duty_cycle_io-2;
			END IF;
		END IF;
	END IF;
END PROCESS;



PROCESS(clock_48M)--����2�����Ƶ綯�����ֹͣ 
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF key_edge(1)='1' THEN
			pwm_en_io<=NOT pwm_en_io;
		END IF;
	END IF;
END PROCESS;



PROCESS(clock_48M)--����3�����Ƶ綯����/��ת
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF key_edge(2)='1' THEN
			moto_dir <=NOT moto_dir;
		END IF;
	END IF;
END PROCESS;
led(5) <= moto_dir;
motoa<=pwm_in WHEN moto_dir='1' ELSE '0';
motob<='0' WHEN moto_dir='1' ELSE pwm_in;



PROCESS(clock_48M)--ZHENG FAN ZHUAN
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF key_edge(3)='1' THEN
			updown <=NOT updown;
		END IF;
	END IF;
END PROCESS;
led(7) <= updown;
END;