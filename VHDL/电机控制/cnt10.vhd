LIBRARY IEEE;                      
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_Arith.ALL;
USE IEEE.STD_LOGIC_Unsigned.ALL;

ENTITY cnt10 IS
PORT(
clk:	IN		STD_LOGIC;					--计数时钟
rst:	IN		STD_LOGIC;					--复位信号
cin:	IN  	STD_LOGIC;					--进位输入
cout:	BUFFER	STD_LOGIC;					--进位输出
dout:	OUT 	STD_LOGIC_VECTOR(3 DOWNTO 0)--计数输出
);
END;

ARCHITECTURE one OF cnt10 IS
SIGNAL	counter:	STD_LOGIC_VECTOR(3 DOWNTO 0);
BEGIN
dout<=counter;
cout<='1' WHEN (cin='1' AND counter>=9) ELSE '0';
PROCESS(clk,rst,cin)
BEGIN
	IF rst='1' THEN				--计数器复位
		counter<="0000";
	ELSIF cin='1' THEN
		IF	RISING_EDGE(clk) THEN 
			IF cout='1' THEN
				counter<="0000";
			ELSE
				counter<=counter +1;
			END IF;
		END IF;
	END IF;
END PROCESS;
END;