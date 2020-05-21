LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY pwm_logic IS
PORT(
clock_48M:		IN	STD_LOGIC;	--系统输入时钟
duty_cycle:	IN  STD_LOGIC_VECTOR(3 DOWNTO 0);
pwm_en:		IN  STD_LOGIC;	--PWM使能.
pwm_out:	OUT STD_LOGIC	--PWM输出
);
END;

ARCHITECTURE one OF pwm_logic 	IS
SIGNAL pwm_out_io:	STD_LOGIC;			--PWM输出
SIGNAL count:		STD_LOGIC_VECTOR(15 DOWNTO 0);--PWM内部计数器
BEGIN
pwm_out<=pwm_out_io;

PROCESS(clock_48M)
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF	pwm_en ='1' THEN
			count<=count+1;
		END IF;
	END IF;
END PROCESS;

PROCESS(clock_48M)
BEGIN
	IF RISING_EDGE(clock_48M) THEN
		IF	pwm_en ='1' AND count(15 DOWNTO 12)<=duty_cycle THEN
			pwm_out_io<='1';
		ELSE
			pwm_out_io<='0';
		END IF;
	END IF;
END PROCESS;


END ;


