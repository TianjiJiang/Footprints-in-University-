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
		IF	in_bit ='1'	THEN	--一旦出现高电平即复位计数器
			cnt	<=X"00000";		--清0计数器
			out_bit_r <='1';	--输出置1
		ELSE
			IF cnt>=9600	THEN	--clk=48M 约为200us
				out_bit_r<='0';	--低电平宽度大于200us时输出低电平.
			ELSE				--低电平宽度小于200us时输出高电平.
				cnt<=cnt+1;		--计数器累加
				out_bit_r<='1';
			END IF;
		END IF;
	END IF;
END PROCESS;
END;